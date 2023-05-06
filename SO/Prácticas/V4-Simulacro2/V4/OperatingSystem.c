#include "Simulator.h"
#include "OperatingSystem.h"
#include "OperatingSystemBase.h"
#include "MMU.h"
#include "Processor.h"
#include "Buses.h"
#include "Heap.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

// Functions prototypes
void OperatingSystem_PCBInitialization(int, int, int, int, int);
void OperatingSystem_MoveToTheREADYState(int);
void MoveToTheBlockedState(int);
void OperatingSystem_Dispatch(int);
void OperatingSystem_RestoreContext(int);
void OperatingSystem_SaveContext(int);
void OperatingSystem_TerminateExecutingProcess();
int OperatingSystem_LongTermScheduler();
void OperatingSystem_PreemptRunningProcess();
int OperatingSystem_CreateProcess(int);
int OperatingSystem_ObtainMainMemory(int, int);
int OperatingSystem_ShortTermScheduler();
int OperatingSystem_ExtractFromReadyToRun();
int OperatingSystemExtractorFromBlocked();
void OperatingSystem_HandleException();
void OperatingSystem_HandleSystemCall();
void OperatingSystem_HandleClockInterrupt();
void checkPriority(); 
void changeProcess(int);
int OperatingSystem_GetExecutingProcessID();
int OperatingSystem_ObtainBiggestPartition();
void OperatingSystem_ReleaseMainMemory();
int OperatingSystem_FoundPartition(int);

int PROCESSTABLEMAXSIZE = 4;

heapItem *readyToRunQueue[NUMBEROFQUEUES];
int numberOfReadyToRunProcesses[NUMBEROFQUEUES]={0,0};

// In OperatingSystem.c Exercise 7-b of V2
// Heap with blocked processes sort by when to wakeup
heapItem *sleepingProcessesQueue;
int numberOfSleepingProcesses=0; 


// The process table
// PCB processTable[PROCESSTABLEMAXSIZE];
PCB * processTable;

// Address base for OS code in this version
int OS_address_base; // = PROCESSTABLEMAXSIZE * MAINMEMORYSECTIONSIZE;

// Identifier of the current executing process
int executingProcessID=NOPROCESS;

// Identifier of the System Idle Process
int sipID;

// Initial PID for assignation (Not assigned)
int initialPID=-1;

int numberOfPartitions = 0;
int biggestPartition = 0;

char * statesNames [5]={"NEW","READY","EXECUTING","BLOCKED","EXIT"};

char * exceptionNames [4] = {"division by zero", "invalid processor mode", "invalid address", "invalid instruction"};

// Begin indes for daemons in programList
// int baseDaemonsInProgramList; 

// Array that contains the identifiers of the READY processes
// heapItem readyToRunQueue[NUMBEROFQUEUES][PROCESSTABLEMAXSIZE];


// Variable containing the number of not terminated user processes
int numberOfNotTerminatedUserProcesses=0;

// char DAEMONS_PROGRAMS_FILE[MAXFILENAMELENGTH]="teachersDaemons";

int MAINMEMORYSECTIONSIZE = 60;

extern int MAINMEMORYSIZE;

int clockInterrupts = 0;

int lastPartitionAsigned = 0;

//Ej 15 readyToShutDown()

// Initial set of tasks of the OS
void OperatingSystem_Initialize(int programsFromFileIndex) {
	
	int i, selectedProcess;
	FILE *programFile; // For load Operating System Code
	
// In this version, with original configuration of memory size (300) and number of processes (4)
// every process occupies a 60 positions main memory chunk 
// and OS code and the system stack occupies 60 positions 

	MAINMEMORYSECTIONSIZE =(MAINMEMORYSIZE / (PROCESSTABLEMAXSIZE+1));
	OS_address_base = PROCESSTABLEMAXSIZE * MAINMEMORYSECTIONSIZE;

	if (initialPID<0) // if not assigned in options...
		initialPID=PROCESSTABLEMAXSIZE - 1; 
	
	// Space for the processTable
	processTable = (PCB *) malloc(PROCESSTABLEMAXSIZE*sizeof(PCB));
	
	// Space for the ready to run queues (one queue initially...)
	readyToRunQueue[USERPROCESSQUEUE] = (heapItem *) malloc(PROCESSTABLEMAXSIZE*sizeof(heapItem));
	readyToRunQueue[DAEMONSQUEUE] = (heapItem *) malloc(PROCESSTABLEMAXSIZE*sizeof(heapItem));

	sleepingProcessesQueue = (heapItem *) malloc(PROCESSTABLEMAXSIZE*sizeof(heapItem));

	programFile=fopen("OperatingSystemCode", "r");
	if (programFile==NULL){
		// Show red message "FATAL ERROR: Missing Operating System!\n"
		ComputerSystem_DebugMessage(99,SHUTDOWN,"FATAL ERROR: Missing Operating System!\n");
		exit(1);		
	}

	// Obtain the memory requirements of the program
	int processSize=OperatingSystem_ObtainProgramSize(programFile);

	// Load Operating System Code
	OperatingSystem_LoadProgram(programFile, OS_address_base, processSize);
	
	// Process table initialization (all entries are free)
	for (i=0; i<PROCESSTABLEMAXSIZE;i++){
		processTable[i].busy=0;
	}
	// Initialization of the interrupt vector table of the processor
	Processor_InitializeInterruptVectorTable(OS_address_base+2);
		
	// Include in program list all user or system daemon processes
	OperatingSystem_PrepareDaemons(programsFromFileIndex);
	
	// Create all user processes from the information given in the command line
	//OperatingSystem_LongTermScheduler();
	
	numberOfPartitions = OperatingSystem_InitializePartitionTable();
	// OperatingSystem_InitializePartitionTable();
//	Aquí V4-6d/i obtener máximo
	biggestPartition = OperatingSystem_ObtainBiggestPartition();
 
	ComputerSystem_FillInArrivalTimeQueue();
	
	OperatingSystem_PrintStatus();
	if (OperatingSystem_LongTermScheduler() <= 1 && numberOfProgramsInArrivalTimeQueue == 0){
		OperatingSystem_ReadyToShutdown();
		// finishing sipID, change PC to address of OS HALT instruction
		Processor_CopyInSystemStack(MAINMEMORYSIZE-1,OS_address_base+1);
		executingProcessID=NOPROCESS;
	}

	if (strcmp(programList[processTable[sipID].programListIndex]->executableName,"SystemIdleProcess")
		&& processTable[sipID].state==READY) {
		// Show red message "FATAL ERROR: Missing SIP program!\n"
		ComputerSystem_DebugMessage(99,SHUTDOWN,"FATAL ERROR: Missing SIP program!\n");
		exit(1);
	}

	// At least, one process has been created
	// Select the first process that is going to use the processor
	selectedProcess=OperatingSystem_ShortTermScheduler();

	// Assign the processor to the selected process
	OperatingSystem_Dispatch(selectedProcess);

	// Initial operation for Operating System
	Processor_SetPC(OS_address_base);
}

// The LTS is responsible of the admission of new processes in the system.
// Initially, it creates a process from each program specified in the 
// command line and daemons programs
int OperatingSystem_LongTermScheduler() {
  
	int PID, i,
		numberOfSuccessfullyCreatedProcesses=0;

	while(OperatingSystem_IsThereANewProgram() == YES){
//  for (i=0; programList[i]!=NULL && i<PROGRAMSMAXNUMBER ; i++) {
		i = Heap_poll(arrivalTimeQueue, QUEUE_ARRIVAL,
		&(numberOfProgramsInArrivalTimeQueue));
		PID=OperatingSystem_CreateProcess(i);
		if(PID == NOFREEENTRY){ 
			OperatingSystem_ShowTime(ERROR);
			ComputerSystem_DebugMessage(103, ERROR, programList[i] -> executableName);
		} else if (PID == PROGRAMNOTVALID){
			OperatingSystem_ShowTime(ERROR);
			ComputerSystem_DebugMessage(104, ERROR, programList[i] -> executableName, 
			"-- invalid priority or size --");
		} else if (PID == PROGRAMDOESNOTEXIST){
			OperatingSystem_ShowTime(ERROR);
			ComputerSystem_DebugMessage(104, ERROR, programList[i] -> executableName,
			"--- it does not exist ---");
		} else if (PID == TOOBIGPROCESS){
			OperatingSystem_ShowTime(ERROR); 
			ComputerSystem_DebugMessage(105, ERROR, programList[i] -> executableName);
		} else if(PID == MEMORYFULL){
			OperatingSystem_ShowTime(ERROR); 
			ComputerSystem_DebugMessage(144, ERROR, programList[i] -> executableName);
		} else{
			numberOfSuccessfullyCreatedProcesses++;
			if (programList[i]->type==USERPROGRAM) 
			numberOfNotTerminatedUserProcesses++;
			// Move process to the ready state
			OperatingSystem_MoveToTheREADYState(PID);
		}
	}
	if(numberOfSuccessfullyCreatedProcesses > 0){
		OperatingSystem_PrintStatus(); 
	}

	// Return the number of succesfully created processes
	return numberOfSuccessfullyCreatedProcesses;
}

// This function creates a process from an executable program
int OperatingSystem_CreateProcess(int indexOfExecutableProgram) {
  
	int PID;
	int processSize;
	int loadingPhysicalAddress;
	int priority;
	FILE *programFile;
	PROGRAMS_DATA *executableProgram=programList[indexOfExecutableProgram];

	// Obtain a process ID
	PID=OperatingSystem_ObtainAnEntryInTheProcessTable();
	if(PID == NOFREEENTRY){
		return NOFREEENTRY;
	}

	// Check if programFile exists
	programFile=fopen(executableProgram->executableName, "r");
	if(programFile == NULL){
		return PROGRAMDOESNOTEXIST;
	}
	// Obtain the memory requirements of the program
	processSize=OperatingSystem_ObtainProgramSize(programFile);
	if(processSize == PROGRAMNOTVALID ){
		return PROGRAMNOTVALID;
	}
	
	// Obtain the priority for the process
	priority=OperatingSystem_ObtainPriority(programFile);
	if(priority == PROGRAMNOTVALID ){
		return PROGRAMNOTVALID;
	}
	
	OperatingSystem_ShowTime(SYSMEM);
	ComputerSystem_DebugMessage(142, SYSMEM, PID, executableProgram->executableName, processSize);

//	OperatingSystem_ShowPartitionTable("before allocating memory");
	int partitionIndex = OperatingSystem_ObtainMainMemory(processSize, PID);
	if(partitionIndex == TOOBIGPROCESS || partitionIndex == MEMORYFULL){
		return partitionIndex;
	} 
	loadingPhysicalAddress = partitionsTable[partitionIndex].initAddress;
// 	loadingPhysicalAddress=OperatingSystem_ObtainMainMemory(processSize, PID);
	 
	// Load program in the allocated memory
	if(OperatingSystem_LoadProgram(programFile, loadingPhysicalAddress, processSize) == TOOBIGPROCESS){
		return TOOBIGPROCESS;
	} 
	
	// OperatingSystem_ShowPartitionTable("after allocating memory");

	// PCB initialization
	OperatingSystem_PCBInitialization(PID, loadingPhysicalAddress, processSize, priority, indexOfExecutableProgram);
	
	OperatingSystem_ShowPartitionTable("before allocating memory");
	// Asignar 
	partitionsTable[partitionIndex].PID = PID;
	OperatingSystem_ShowTime(SYSMEM);
	ComputerSystem_DebugMessage(143, SYSMEM, partitionIndex, loadingPhysicalAddress, 
	partitionsTable[partitionIndex].size, PID,
	executableProgram->executableName);

	OperatingSystem_ShowPartitionTable("after allocating memory");
	// Show message "Process [PID] created from program [executableName]\n"
	//OperatingSystem_ShowTime(INIT);
	//ComputerSystem_DebugMessage(70,INIT,PID,executableProgram->executableName);
	
	return PID;
}

void OperatingSystem_PrintReadyToRunQueue(){
	OperatingSystem_ShowTime(SHORTTERMSCHEDULE);
	ComputerSystem_DebugMessage(106, SHORTTERMSCHEDULE,  "USER:");
	if(numberOfReadyToRunProcesses[0] == 0){
		ComputerSystem_DebugMessage(108, SHORTTERMSCHEDULE, " -EMPTY-");
	}
	for (int i = 0; i < numberOfReadyToRunProcesses[0]; i++)
	{
		if(i != 0){
			ComputerSystem_DebugMessage(108, SHORTTERMSCHEDULE, ", ");
		}
		int auxPid = readyToRunQueue[0][i].info;
		ComputerSystem_DebugMessage(107, SHORTTERMSCHEDULE, auxPid, 
		processTable[auxPid].priority);
	} 
	ComputerSystem_DebugMessage(108, SHORTTERMSCHEDULE, "\n");
	ComputerSystem_DebugMessage(108, SHORTTERMSCHEDULE, "\t");
	ComputerSystem_DebugMessage(108, SHORTTERMSCHEDULE, "DAEMONS:");
	if(numberOfReadyToRunProcesses[1] == 0){
		ComputerSystem_DebugMessage(108, SHORTTERMSCHEDULE, " -EMPTY-");
	}
	for (int i = 0; i < numberOfReadyToRunProcesses[1]; i++)
	{
		if(i != 0){
			ComputerSystem_DebugMessage(108, SHORTTERMSCHEDULE, ", ");
		}
		int auxPid = readyToRunQueue[1][i].info;
		ComputerSystem_DebugMessage(107, SHORTTERMSCHEDULE, auxPid, 
		processTable[auxPid].priority);
	}
	ComputerSystem_DebugMessage(108, SHORTTERMSCHEDULE, "\n");
}

// Main memory is assigned in chunks. All chunks are the same size. A process
// always obtains the chunk whose position in memory is equal to the processor identifier
int OperatingSystem_ObtainMainMemory(int processSize, int PID) {
	//Debe devolver el índice de la partición
	if(processSize > biggestPartition){
		return TOOBIGPROCESS;
	}
	int bestPartition = -1;
	if(lastPartitionAsigned == numberOfPartitions - 1){
		lastPartitionAsigned = 0;
	}
	for(int i = lastPartitionAsigned; i < numberOfPartitions; i++){
	// for(int i = 0; i < PARTITIONTABLEMAXSIZE; i++){
		if(partitionsTable[i].size >= processSize && partitionsTable[i].PID == NOPROCESS){
			bestPartition = i;
			lastPartitionAsigned = bestPartition;
			return bestPartition;
		}
	}
	return MEMORYFULL;
//	return PID*MAINMEMORYSECTIONSIZE;
}


// Assign initial values to all fields inside the PCB
void OperatingSystem_PCBInitialization(int PID, int initialPhysicalAddress, int processSize, int priority, int processPLIndex) {

	processTable[PID].busy=1;
	processTable[PID].initialPhysicalAddress=initialPhysicalAddress;
	processTable[PID].processSize=processSize;
	processTable[PID].copyOfSPRegister=initialPhysicalAddress+processSize;
	processTable[PID].state=NEW;
	processTable[PID].priority=priority;
	processTable[PID].programListIndex=processPLIndex;
	processTable[PID].copyOfAccumulator = 0;
	processTable[PID].whenToWakeUp = 0;
	// Daemons run in protected mode and MMU use real address
	if (programList[processPLIndex]->type == DAEMONPROGRAM) {
		processTable[PID].copyOfPCRegister=initialPhysicalAddress;
		processTable[PID].copyOfPSWRegister= ((unsigned int) 1) << EXECUTION_MODE_BIT;
		processTable[PID].queueID = DAEMONSQUEUE;
	} 
	else {
		processTable[PID].copyOfPCRegister=0;
		processTable[PID].copyOfPSWRegister=0; 
		processTable[PID].queueID = USERPROCESSQUEUE;
	}
	OperatingSystem_ShowTime(SYSPROC);
	ComputerSystem_DebugMessage(111, SYSPROC, PID, 
	programList[processTable[PID].programListIndex] -> executableName, statesNames[NEW]);
}


// Move a process to the READY state: it will be inserted, depending on its priority, in
// a queue of identifiers of READY processes
void OperatingSystem_MoveToTheREADYState(int PID) {
	int auxQueueID = processTable[PID].queueID;
	if (Heap_add(PID, readyToRunQueue[auxQueueID],QUEUE_PRIORITY,&(numberOfReadyToRunProcesses[auxQueueID]),
		PROCESSTABLEMAXSIZE)>=0) {
		int previousState = processTable[PID].state;
		processTable[PID].state=READY;
		OperatingSystem_ShowTime(SYSPROC);
		ComputerSystem_DebugMessage(110, SYSPROC, PID, 
			programList[processTable[PID].programListIndex] -> executableName, statesNames[previousState],
			statesNames[READY]);
		//OperatingSystem_PrintReadyToRunQueue();
		// if(previousState == NEW){
		// 	OperatingSystem_PrintStatus();
		// }
		// OperatingSystem_PrintStatus();
	} 
}


// The STS is responsible of deciding which process to execute when specific events occur.
// It uses processes priorities to make the decission. Given that the READY queue is ordered
// depending on processes priority, the STS just selects the process in front of the READY queue
int OperatingSystem_ShortTermScheduler() {
	
	int selectedProcess;

	selectedProcess=OperatingSystem_ExtractFromReadyToRun(USERPROCESSQUEUE);
	if(selectedProcess == NOPROCESS){
		selectedProcess=OperatingSystem_ExtractFromReadyToRun(DAEMONSQUEUE);
	}
	return selectedProcess;
}


// Return PID of more priority process in the READY queue
int OperatingSystem_ExtractFromReadyToRun(int queueID) {
  
	int selectedProcess=NOPROCESS;

	selectedProcess=Heap_poll(readyToRunQueue[queueID],QUEUE_PRIORITY ,&(numberOfReadyToRunProcesses[queueID]));
	
	// Return most priority process or NOPROCESS if empty queue
	return selectedProcess; 
}


// Function that assigns the processor to a process
void OperatingSystem_Dispatch(int PID) {

	// The process identified by PID becomes the current executing process
	executingProcessID=PID;

	int previousState = processTable[PID].state;
	// Change the process' state
	processTable[PID].state=EXECUTING;
	OperatingSystem_ShowTime(SYSPROC);
	ComputerSystem_DebugMessage(110, SYSPROC, PID, 
		programList[processTable[PID].programListIndex] -> executableName, statesNames[previousState],
			statesNames[EXECUTING]);

	// Modify hardware registers with appropriate values for the process identified by PID
	OperatingSystem_RestoreContext(PID);
}


// Modify hardware registers with appropriate values for the process identified by PID
void OperatingSystem_RestoreContext(int PID) {
  
	// New values for the CPU registers are obtained from the PCB
	Processor_CopyInSystemStack(MAINMEMORYSIZE-1,processTable[PID].copyOfPCRegister);
	Processor_CopyInSystemStack(MAINMEMORYSIZE-2,processTable[PID].copyOfPSWRegister);
	Processor_SetRegisterSP(processTable[PID].copyOfSPRegister);
	//Hacer lo mismo con el acumulator
	Processor_SetAccumulator(processTable[PID].copyOfAccumulator);
	// Same thing for the MMU registers
	MMU_SetBase(processTable[PID].initialPhysicalAddress);
	MMU_SetLimit(processTable[PID].processSize);
}


// Function invoked when the executing process leaves the CPU 
void OperatingSystem_PreemptRunningProcess() {

	// Save in the process' PCB essential values stored in hardware registers and the system stack
	OperatingSystem_SaveContext(executingProcessID);
	// Change the process' state
	OperatingSystem_MoveToTheREADYState(executingProcessID);
	// The processor is not assigned until the OS selects another process
	executingProcessID=NOPROCESS;
}

void OperatingSystem_PreemptBlockedProcess(){
	// Save in the process' PCB essential values stored in hardware registers and the system stack
	OperatingSystem_SaveContext(executingProcessID);
	// The processor is not assigned until the OS selects another process
	executingProcessID=NOPROCESS;
}


// Save in the process' PCB essential values stored in hardware registers and the system stack
void OperatingSystem_SaveContext(int PID) {
	
	// Load PC saved for interrupt manager
	processTable[PID].copyOfPCRegister=Processor_CopyFromSystemStack(MAINMEMORYSIZE-1);
	
	// Load PSW saved for interrupt manager
	processTable[PID].copyOfPSWRegister=Processor_CopyFromSystemStack(MAINMEMORYSIZE-2);
	
	processTable[PID].copyOfAccumulator=Processor_GetAccumulator(); 

	processTable[PID].copyOfSPRegister=Processor_GetRegisterSP();
}


// Exception management routine
void OperatingSystem_HandleException() {
  
	// Show message "Process [executingProcessID] has generated an exception and is terminating\n"
//	OperatingSystem_ShowTime(SYSPROC);
//	ComputerSystem_DebugMessage(71,SYSPROC,executingProcessID,programList[processTable[executingProcessID].programListIndex]->executableName);

	OperatingSystem_ShowTime(INTERRUPT);
	ComputerSystem_DebugMessage(140, INTERRUPT, executingProcessID,
	programList[processTable[executingProcessID].programListIndex]->executableName,
	exceptionNames[Processor_GetRegisterD()]);

	OperatingSystem_TerminateExecutingProcess();
	OperatingSystem_PrintStatus();

}

// All tasks regarding the removal of the executing process
void OperatingSystem_TerminateExecutingProcess() {

	int previousState = processTable[executingProcessID].state;
	processTable[executingProcessID].state=EXIT;
	OperatingSystem_ShowTime(SYSPROC);
	ComputerSystem_DebugMessage(110, SYSPROC, executingProcessID, 
	programList[processTable[executingProcessID].programListIndex] -> executableName, statesNames[previousState],
			statesNames[EXIT]);

	//V4-8 Llamar a la función de liberar memoria
	OperatingSystem_ReleaseMainMemory();
	//Buscar la partición que tenga el mismo PID
	//En ella asignar el PID de la partición a NOPROCESS

	// OperatingSystem_ShowPartitionTable("after releasing memory");
	
	if (programList[processTable[executingProcessID].programListIndex]->type==USERPROGRAM) 
		// One more user process that has terminated
		numberOfNotTerminatedUserProcesses--;
	
	if (numberOfNotTerminatedUserProcesses==0 && numberOfProgramsInArrivalTimeQueue == 0) {
		// Simulation must finish, telling sipID to finish
		OperatingSystem_ReadyToShutdown();
		if (executingProcessID==sipID) {
			// finishing sipID, change PC to address of OS HALT instruction
			Processor_CopyInSystemStack(MAINMEMORYSIZE-1,OS_address_base+1);
			executingProcessID=NOPROCESS;
			OperatingSystem_ShowTime(SHUTDOWN);
			ComputerSystem_DebugMessage(99,SHUTDOWN,"The system will shut down now...\n");
			return; // Don't dispatch any process
		}
	}

	// Select the next process to execute (sipID if no more user processes)
	int selectedProcess=OperatingSystem_ShortTermScheduler();

	// Assign the processor to that process
	OperatingSystem_Dispatch(selectedProcess);
}

// System call management routine
void OperatingSystem_HandleSystemCall() {
  
	int systemCallID;
	int auxQueue;
	int auxPriority;
	int operand2 = Processor_GetRegisterD();

	// Register C contains the identifier of the issued system call
	systemCallID=Processor_GetRegisterC();
	
	switch (systemCallID) {
		case SYSCALL_PRINTEXECPID:
			// Show message: "Process [executingProcessID] has the processor assigned\n"
			OperatingSystem_ShowTime(SYSPROC);
			ComputerSystem_DebugMessage(72,SYSPROC,executingProcessID,programList[processTable[executingProcessID].programListIndex]->executableName,Processor_GetRegisterA(),Processor_GetRegisterB());
			break;

		case SYSCALL_END:
			OperatingSystem_ShowTime(SYSPROC);
			// Show message: "Process [executingProcessID] has requested to terminate\n"
			ComputerSystem_DebugMessage(73,SYSPROC,executingProcessID,programList[processTable[executingProcessID].programListIndex]->executableName);
			OperatingSystem_TerminateExecutingProcess();
			OperatingSystem_PrintStatus();
			break;

		case SYSCALL_YIELD:
			auxQueue = processTable[executingProcessID].queueID;
			auxPriority = processTable[executingProcessID].priority;
			if(numberOfReadyToRunProcesses[auxQueue] > 0 && 
			processTable[readyToRunQueue[auxQueue][0].info].priority == auxPriority){
				int oldId = executingProcessID;
				int newId = readyToRunQueue[auxQueue][0].info;
				OperatingSystem_ShowTime(SHORTTERMSCHEDULE);
				ComputerSystem_DebugMessage(116, SHORTTERMSCHEDULE, oldId,
				programList[processTable[oldId].programListIndex]->executableName, 
				newId, programList[processTable[newId].programListIndex]->executableName);
				//El shortTermScheduler devuelve el primer proceso user de la cola de listos. En caso de no haberlo,
				//el primer daemon de la cola de listos. El dispatch asigna el procesador al proceso que se le pasa.
				OperatingSystem_PreemptRunningProcess();
				OperatingSystem_Dispatch(OperatingSystem_ShortTermScheduler());
				OperatingSystem_PrintStatus();
				break;
			} else {
				OperatingSystem_ShowTime(SHORTTERMSCHEDULE);
				ComputerSystem_DebugMessage(117, SHORTTERMSCHEDULE, executingProcessID, 
				programList[processTable[executingProcessID].programListIndex]->executableName);
				break;
			}
			break;
		
		case SYSCALL_SLEEP:
			OperatingSystem_SaveContext(executingProcessID);
			processTable[executingProcessID].whenToWakeUp = clockInterrupts + 1;
			if(operand2 > 0){
				processTable[executingProcessID].whenToWakeUp += operand2;
			} else {
				processTable[executingProcessID].whenToWakeUp += abs(Processor_GetAccumulator()); 
			}
			MoveToTheBlockedState(executingProcessID);
			break;
		default :
			//Ejercicio 4 V4
			OperatingSystem_ShowTime(INTERRUPT);
			ComputerSystem_DebugMessage(141, INTERRUPT, executingProcessID, 
				programList[processTable[executingProcessID].programListIndex]->executableName,
				systemCallID);
			OperatingSystem_TerminateExecutingProcess();
			OperatingSystem_PrintStatus();
			break;
	}
}

void MoveToTheBlockedState(int PID){
	//Si se puede añadir el proceso a la cola de dormidos, entonces se muestra el mensaje y se le asigna 
	//el estado blocked
	if(Heap_add(PID, sleepingProcessesQueue, QUEUE_WAKEUP,
	&(numberOfSleepingProcesses), PROCESSTABLEMAXSIZE) >= 0){
		OperatingSystem_ShowTime(SYSPROC);
		ComputerSystem_DebugMessage(110, SYSPROC, executingProcessID, 
		programList[processTable[PID].programListIndex] -> executableName, 
		statesNames[processTable[PID].state], statesNames[BLOCKED]);
		processTable[PID].state = BLOCKED;
	}
	//El shortTermScheduler devuelve el primer proceso user de la cola de listos. En caso de no haberlo, 
	//el primer daemon de la cola de listos. El dispatch asigna el procesador al proceso que se le pasa.
	OperatingSystem_Dispatch(OperatingSystem_ShortTermScheduler());
	OperatingSystem_PrintStatus();
}

//	Implement interrupt logic calling appropriate interrupt handle
void OperatingSystem_InterruptLogic(int entryPoint){
	switch (entryPoint){
		case SYSCALL_BIT: // SYSCALL_BIT=2
			OperatingSystem_HandleSystemCall();
			break;
		case EXCEPTION_BIT: // EXCEPTION_BIT=6
			OperatingSystem_HandleException();
			break;
		case CLOCKINT_BIT: // CLOCKINT_BIT=9
			OperatingSystem_HandleClockInterrupt();
			break;
	}
}

int OperatingSystem_GetExecutingProcessID(){
	return executingProcessID;
}

// In OperatingSystem.c Exercise 2-b of V2
void OperatingSystem_HandleClockInterrupt(){ 
	//Ejercicio 5 apartado b

	clockInterrupts++;
	OperatingSystem_ShowTime(INTERRUPT);
	ComputerSystem_DebugMessage(120, INTERRUPT, clockInterrupts);
	int unlocked = 0;
	int process = NOPROCESS;
	//Mientras que haya procesos dormidos y whenToWakeUp sea igual a clock interrupts 
	while (numberOfSleepingProcesses > 0 && 
	processTable[(Heap_getFirst(sleepingProcessesQueue, numberOfSleepingProcesses))].whenToWakeUp == clockInterrupts)
	{
		//Extraemos el proceso de los blocked y lo movemos al estado ready 
		process = OperatingSystemExtractorFromBlocked();	
		unlocked++;
		OperatingSystem_MoveToTheREADYState(process);
		OperatingSystem_PrintStatus();
	}
	if(OperatingSystem_LongTermScheduler() >= 1 || unlocked >= 1){
		checkPriority();
	} 
	if (numberOfNotTerminatedUserProcesses == 0 && numberOfProgramsInArrivalTimeQueue == 0){
		OperatingSystem_ReadyToShutdown();
	}
	 if (numberOfReadyToRunProcesses[DAEMONSQUEUE] > 0){
		int mostPrioritaryDaemons = readyToRunQueue[DAEMONSQUEUE][0].info;
		if(processTable[executingProcessID].queueID == DAEMONSQUEUE &&    //Si el proceso actual es Daemon
		(processTable[executingProcessID].priority > processTable[mostPrioritaryDaemons].priority)){
			changeProcess(mostPrioritaryDaemons);
			//OperatingSystem_PrintStatus();
		}
	}
	return; 
}

/**
 * Extrae el proceso más prioritario de la cola de sleeping
*/
int OperatingSystemExtractorFromBlocked(){
	int selectedProcess = NOPROCESS;

	selectedProcess = Heap_poll(sleepingProcessesQueue, QUEUE_WAKEUP, &(numberOfSleepingProcesses));

	return selectedProcess;
}

/**
 * Comprueba la prioridad del proceso en ejecución y lo cambia en caso de encontrar uno más prioritario
*/
void checkPriority(){
	int mostPrioritaryUser = readyToRunQueue[USERPROCESSQUEUE][0].info;	//Obtenemos el info del proceso más prioritario

	if(numberOfReadyToRunProcesses[USERPROCESSQUEUE] > 0 && 		//Si hay uno o más users ready
	processTable[executingProcessID].queueID == USERPROCESSQUEUE){ 	//y el proceso actual es user
		//Si la prioridad del proceso actual es mayor que la del proceso más prioritario de los ready, cambiamos 
		//el proceso
		if(processTable[executingProcessID].priority > processTable[mostPrioritaryUser].priority){
			changeProcess(mostPrioritaryUser);
		}
	//Si el proceso actual no es user y hay procesos user ready, cambiamos el proceso por el más prioritario de 
	//los users
	} else if (numberOfReadyToRunProcesses[USERPROCESSQUEUE] > 0){
		changeProcess(mostPrioritaryUser);
	}
}

/**
 * Cambia el proceso en ejecución 
 */
void changeProcess(int PID){
	OperatingSystem_ShowTime(SHORTTERMSCHEDULE);
	ComputerSystem_DebugMessage(121, SHORTTERMSCHEDULE, executingProcessID,
	programList[processTable[executingProcessID].programListIndex] -> executableName,
	PID, programList[processTable[PID].programListIndex] -> executableName);
	//El preempt extrae el proceso en ejecución del procesador, guardando los registros y moviendo el proceso 
	//al estado ready
	OperatingSystem_PreemptRunningProcess();
	//El shortTermScheduler devuelve el primer proceso user de la cola de listos. En caso de no haberlo, 
	//el primer daemon de la cola de listos. El dispatch asigna el procesador al proceso que se le pasa.
	OperatingSystem_Dispatch(OperatingSystem_ShortTermScheduler());
	OperatingSystem_PrintStatus();
}

int OperatingSystem_ObtainBiggestPartition(){
	int partitionSize = 0;
	for(int i = 0; i < numberOfPartitions; i++){
	// for(int i = 0; i < PARTITIONTABLEMAXSIZE; i++){
		if(partitionsTable[i].size > partitionSize){
			partitionSize = partitionsTable[i].size;
		}
	}
	return partitionSize;
}

//Buscar la partición que tenga el mismo PID
//En ella asignar el PID de la partición a NOPROCESS
void OperatingSystem_ReleaseMainMemory(){
	OperatingSystem_ShowPartitionTable("before releasing memory");
	//Llamar a método que busca la partición que tenga el mismo PID y devuelve el index
	int partitionIndex = OperatingSystem_FoundPartition(executingProcessID);
	OperatingSystem_ShowTime(SYSMEM);
	ComputerSystem_DebugMessage(145, SYSMEM, partitionIndex, partitionsTable[partitionIndex].initAddress,
	partitionsTable[partitionIndex].size, executingProcessID, 
	programList[processTable[executingProcessID].programListIndex] -> executableName);
	partitionsTable[partitionIndex].PID = NOPROCESS;
	OperatingSystem_ShowPartitionTable("after releasing memory");
}

int OperatingSystem_FoundPartition(int ProccesID){
	for(int i = 0; i < numberOfPartitions; i++){
	// for (int i = 0; i < PARTITIONTABLEMAXSIZE; i++){
		if(partitionsTable[i].PID == ProccesID){
			return i;
		}
	}
}
