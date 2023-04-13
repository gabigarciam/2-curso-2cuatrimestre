#ifndef OPERATINGSYSTEM_H
#define OPERATINGSYSTEM_H

#include "ComputerSystem.h"
#include <stdio.h>


#define SUCCESS 1
#define PROGRAMDOESNOTEXIST -1
#define PROGRAMNOTVALID -2

#define NOFREEENTRY -3
#define TOOBIGPROCESS -4

#define NOPROCESS -1

// Number of queues of ready to run processes, initially one queue...
#define NUMBEROFQUEUES 2

#define SLEEPINGQUEUE

enum TypeOfReadyToRunProcessQueues { USERPROCESSQUEUE, DAEMONSQUEUE}; 

// Contains the possible type of programs
enum ProgramTypes { USERPROGRAM=100, DAEMONPROGRAM }; 

// Enumerated type containing all the possible process states
enum ProcessStates { NEW, READY, EXECUTING, BLOCKED, EXIT};

// Enumerated type containing the list of system calls and their numeric identifiers
enum SystemCallIdentifiers { SYSCALL_END=3, SYSCALL_YIELD=4 ,SYSCALL_PRINTEXECPID=5, SYSCALL_SLEEP = 7};

// A PCB contains all of the information about a process that is needed by the OS
typedef struct {
	int busy;
	int initialPhysicalAddress;
	int processSize;
	int copyOfSPRegister;
	int state;
	int priority;
	int copyOfPCRegister;
	unsigned int copyOfPSWRegister;
	int programListIndex;
	int queueID;
	int copyOfAccumulator;
	int whenToWakeUp;
} PCB;

// These "extern" declaration enables other source code files to gain access
// to the variable listed


// Functions prototypes
void OperatingSystem_Initialize();
void OperatingSystem_InterruptLogic(int);
int OperatingSystem_ShortTermScheduler();
void OperatingSystem_Dispatch(int);
#endif
