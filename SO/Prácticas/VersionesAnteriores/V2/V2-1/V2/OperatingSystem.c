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
void OperatingSystem_HandleException();
void OperatingSystem_HandleSystemCall();
void OperatingSystem_HandleClockInterrupt(); 

int PROCESSTABLEMAXSIZE = 4;

heapItem *readyToRunQueue[NUMBEROFQUEUES];
int numberOfReadyToRunProcesses[NUMBEROFQUEUES]={0,0};
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

char * statesNames [5]={"NEW","READY","EXECUTING","BLOCKED","EXIT"};

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
	readyToRunQueue[0] = (heapItem *) malloc(PROCESSTABLEMAXSIZE*sizeof(heapItem));
	readyToRunQueue[1] = (heapItem *) malloc(PROCESSTABLEMAXSIZE*sizeof(heapItem));

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
	if (OperatingSystem_LongTermScheduler() <= 1){
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
// 			command line and daemons programs
int OperatingSystem_LongTermScheduler() {
  
	int PID, i,
		numberOfSuccessfullyCreatedProcesses=0;
	
	for (i=0; programList[i]!=NULL && i<PROGRAMSMAXNUMBER ; i++) {
		PID=OperatingSystem_CreateProcess(i);
		if(PID == NOFREEENTRY){
			//Mensaje de error
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
	
	// Obtain enough memory space
 	loadingPhysicalAddress=OperatingSystem_ObtainMainMemory(processSize, PID);
	if(loadingPhysicalAddress == TOOBIGPROCESS){
		return TOOBIGPROCESS;
	}

	// Load program in the allocated memory
	if(OperatingSystem_LoadProgram(programFile, loadingPhysicalAddress, processSize) == TOOBIGPROCESS){
		return TOOBIGPROCESS;
	}
	
	// PCB initialization
	OperatingSystem_PCBInitialization(PID, loadingPhysicalAddress, processSize, priority, indexOfExecutableProgram);
	
	// Show message "Process [PID] created from program [executableName]\n"
	OperatingSystem_ShowTime(INIT);
	ComputerSystem_DebugMessage(70,INIT,PID,executableProgram->executableName);
	
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

 	if (processSize>MAINMEMORYSECTIONSIZE)
		return TOOBIGPROCESS;
	
 	return PID*MAINMEMORYSECTIONSIZE;
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
//		OperatingSystem_PrintReadyToRunQueue();
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
	OperatingSystem_ShowTime(SYSPROC);
	ComputerSystem_DebugMessage(71,SYSPROC,executingProcessID,programList[processTable[executingProcessID].programListIndex]->executableName);
	
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


	if (programList[processTable[executingProcessID].programListIndex]->type==USERPROGRAM) 
		// One more user process that has terminated
		numberOfNotTerminatedUserProcesses--;
	
	if (numberOfNotTerminatedUserProcesses==0) {
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

	// Register A contains the identifier of the issued system call
	systemCallID=Processor_GetRegisterA();
	
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
				OperatingSystem_PreemptRunningProcess();
				OperatingSystem_Dispatch(OperatingSystem_ShortTermScheduler());
				OperatingSystem_PrintStatus();
				break;
			} else {
				OperatingSystem_ShowTime(SHORTTERMSCHEDULE);
				ComputerSystem_DebugMessage(117, SHORTTERMSCHEDULE, executingProcessID, 
				programList[processTable[executingProcessID].programListIndex]->executableName);
			}
	}
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

// In OperatingSystem.c Exercise 2-b of V2
void OperatingSystem_HandleClockInterrupt(){ 
	clockInterrupts++;
	OperatingSystem_ShowTime(INTERRUPT);
	ComputerSystem_DebugMessage(120, INTERRUPT, clockInterrupts);
	return; 
} 

