#include "Clock.h"
#include "Processor.h"
#include "ComputerSystemBase.h"

int Clock_GetTime();

int tics=0;

void Clock_Update() {
	tics++;
	if(tics%intervalBetweenInterrupts == 0){
		Processor_RaiseInterrupt(CLOCKINT_BIT);
	}
    // ComputerSystem_DebugMessage(97,CLOCK,tics); // Coment in V2-StudentsCode
}


int Clock_GetTime() {
	return tics;
}
