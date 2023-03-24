
Ejercicio 0: Modificaciones de la instrucción MEMADD

Processor.c

void Processor_DecodeAndExecuteInstruction() {
	...
	case MEMADD_INST:
		registerMAR_CPU = operand2;
		Buses_write_AddressBus_From_To(CPU, MMU);
			
		registerCTRL_CPU=CTRLREAD;
		Buses_write_ControlBus_From_To(CPU, MMU);
			
		registerAccumulator_CPU= operand1 + registerMBR_CPU.cell;
		registerPC_CPU++;
		break;
	...
}

También se ha añadido la siguiente línea al fichero Instructions.def:
	INST(MEMADD)  // 17   0x11

====================================================================================================

Ejercicio 1: Función PrintProgramList()

ComputerSystem.c

void ComputerSystem_PrintProgramList() {

	ComputerSystem_DebugMessage(101,INIT);

	for (int i = 1; i < PROGRAMSMAXNUMBER; i++) {
		if(programList[i]!=NULL) ComputerSystem_DebugMessage(102,INIT,programList[i]->executableName,programList[i]->arrivalTime);
	}
}

====================================================================================================

Ejercicio 2: Llamada a la función PrintProgramList() en la función PowerOn()

void ComputerSystem_PowerOn(int argc, char *argv[], int paramIndex) {
	...
	ComputerSystem_PrintProgramList();
	...
}

====================================================================================================

Ejercicio 3: Creación del programa prog-V1-E3

Al ejecutar "./Simulator --debugSections=HD programVerySimple programVerySimple", el programa no se ejecuta dos veces
debido a la instrucción HALT que detiene el procesador y provoca el final lógico de la simulación.
Para solucionar esto, basta con añadir una instrucción TRAP antes del HALT como en el programa siguiente:

prog-V1-E3

30
5
NOP
TRAP 5
ADD 10 -13
WRITE 15
TRAP 3
HALT

====================================================================================================

Ejercicio 4: Error al ejecutar el simulador con un número de programas que supere la capacidad de la tabla de procesos

Para recoger este error modificamos las funciones CreateProcess() y LongTermScheduler() de OperatingSystem.c

OperatingSystem.c

int OperatingSystem_CreateProcess(int indexOfExecutableProgram) {
	...
	PID=OperatingSystem_ObtainAnEntryInTheProcessTable();

	if (PID == NOFREEENTRY) return PID;
	...
}

int OperatingSystem_LongTermScheduler() {
	...
	switch (PID){

		case NOFREEENTRY:
			ComputerSystem_DebugMessage(103,ERROR,programList[i]->executableName);
			break;
		...
	}
}

====================================================================================================

Ejercicio 5: Error al ejecutar el simulador usando un programa no existente o con una prioridad o tamaño no válidos

Para recoger este error modificamos las funciones CreateProcess() y LongTermScheduler() de OperatingSystem.c

OperatingSystem.c

int OperatingSystem_CreateProcess(int indexOfExecutableProgram) {
	...
	processSize=OperatingSystem_ObtainProgramSize(programFile);	

	if (processSize == PROGRAMNOTVALID) return PROGRAMNOTVALID;

	priority=OperatingSystem_ObtainPriority(programFile);
	
	if (priority == PROGRAMNOTVALID) return PROGRAMNOTVALID;
	...
}

int OperatingSystem_LongTermScheduler() {
	...
	switch (PID){
		...
		case PROGRAMDOESNOTEXIST:
			ComputerSystem_DebugMessage(104,ERROR,programList[i]->executableName, "it does not exist");
			break;

		case PROGRAMNOTVALID:
			ComputerSystem_DebugMessage(104,ERROR,programList[i]->executableName, "invalid priority or size");
			break;
		...
	}
}

====================================================================================================

Ejercicio 6: Error al ejecutar el simulador usando un programa con un tamaño de proceso superior al máximo

Para recoger este error modificamos las funciones CreateProcess() y LongTermScheduler() de OperatingSystem.c

OperatingSystem.c

int OperatingSystem_CreateProcess(int indexOfExecutableProgram) {
	...
	loadingPhysicalAddress=OperatingSystem_ObtainMainMemory(processSize, PID);

	if (loadingPhysicalAddress == TOOBIGPROCESS) return TOOBIGPROCESS;	
	...
}

int OperatingSystem_LongTermScheduler() {
	...
	switch (PID){
		...
		case TOOBIGPROCESS:
			ComputerSystem_DebugMessage(105,ERROR,programList[i]->executableName);
			break;
		...
	}
}