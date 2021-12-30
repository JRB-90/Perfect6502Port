#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "perfect6502.h"
#include "ansi_colors.h"
#include "console_utils.h"

#define SETUP_ADDR 0x8000
#define MAX_CYCLES 2000
#define STARTUP_CYCLES 16
#define EXIT_INSTRUCTION 0x00

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int BOOL;

struct cpu_state {
	BOOL rw;
	uint8_t a;
	uint8_t x;
	uint8_t y;
	uint8_t ir;
	uint8_t p;
	uint8_t sp;
	uint16_t pc;
	uint16_t address;
	uint8_t data;
};

FILE* file;
void* state;
unsigned char* m;
bool isVerbose = false;

void SetupMemoryFromBinFile(char* filePath);
struct cpu_state GetCurrentState(void* state);
void WriteStateToFile(int cycleNumber, struct cpu_state state);
void WriteStateToFileAsHexString(int cycleNumber, struct cpu_state state);
void PrintStateHeader();
void PrintState(int cycleNumber, struct cpu_state state);

int main(int argc, char* argv[])
{
	m = GetMemory();
	state = initAndResetChip();

	if (argc == 3)
	{
		SetupMemoryFromBinFile(argv[1]);
		file = fopen(argv[2], "w");
	}
	else if (argc == 4)
	{
		if (argv[1] == "-V")
		{
			isVerbose = true;
		}
		else
		{
			printf("Unrecognised argument: %s\n", argv[1]);
			printf("Failed to create CSV\n");

			// TODO - Print usage here

			exit(1);
		}

		SetupMemoryFromBinFile(argv[2]);
		file = fopen(argv[3], "w");
	}
	else
	{
		/*printf(RED);
		printf("Incorrect number of arguments, 2 expected\n");
		printf("Usage: cpucheck input_file output_file\n");
		printf(RST);

		return 1;*/

		SetupMemoryFromBinFile("C:\\Development\\Sim6502\\tests\\main.bin");
		file = fopen("C:\\Development\\Sim6502\\tests\\cpu.csv", "w");
	}

	if (isVerbose)
	{
		PrintStateHeader();
	}

	for (int i = 0; i < (MAX_CYCLES + STARTUP_CYCLES); i++)
	{
		Step(state);

		if (i < STARTUP_CYCLES)
		{
			continue;
		}
		
		struct cpu_state currentState = GetCurrentState(state);

		if (i > STARTUP_CYCLES + 2 &&
			readIR(state) == EXIT_INSTRUCTION)
		{
			break;
		}

		if (isVerbose)
		{
			PrintState(i - STARTUP_CYCLES, currentState);
		}
		//WriteStateToFile(i, currentState);
		WriteStateToFileAsHexString(i - STARTUP_CYCLES, currentState);
	};

	fclose(file);
	DestroyChip(state);

	return 0;
}

void SetupMemoryFromBinFile(char* filePath)
{
	memset(m, 0, 65536);
	FILE* binFile = fopen(filePath, "rb");
	fread(m + 32768, 32768, 1, binFile);
	fclose(binFile);
}

struct cpu_state GetCurrentState(void* state)
{
	struct cpu_state currentState;

	currentState.rw = readRW(state);
	currentState.a = readA(state);
	currentState.x = readX(state);
	currentState.y = readY(state);
	currentState.ir = readIR(state);
	currentState.p = readP(state);
	currentState.sp = readSP(state);
	currentState.pc = readPC(state);
	currentState.address = readAddressBus(state);
	currentState.data = readDataBus(state);

	return currentState;
}

void WriteStateToFile(int cycleNumber, struct cpu_state state)
{
	fprintf(file, "%i,", cycleNumber);
	fprintf(file, "%i,", state.rw);
	fprintf(file, "%i,", state.a);
	fprintf(file, "%i,", state.x);
	fprintf(file, "%i,", state.y);
	fprintf(file, "%i,", state.ir);
	fprintf(file, "%i,", state.p);
	fprintf(file, "%i,", state.sp);
	fprintf(file, "%i,", state.pc);
	fprintf(file, "%i,", state.address);
	fprintf(file, "%i\n", state.data);
}

void WriteStateToFileAsHexString(int cycleNumber, struct cpu_state state)
{
	char hexStr[8];
	fprintf(file, "%i,", cycleNumber);
	fprintf(file, "%i,", state.rw);
	WriteHexStr(state.a, 2, hexStr);
	fprintf(file, "%s,", hexStr);
	WriteHexStr(state.x, 2, hexStr);
	fprintf(file, "%s,", hexStr);
	WriteHexStr(state.y, 2, hexStr);
	fprintf(file, "%s,", hexStr);
	WriteHexStr(state.ir, 2, hexStr);
	fprintf(file, "%s,", hexStr);
	WriteHexStr(state.p, 2, hexStr);
	fprintf(file, "%s,", hexStr);
	WriteHexStr(state.sp, 2, hexStr);
	fprintf(file, "%s,", hexStr);
	WriteHexStr(state.pc, 4, hexStr);
	fprintf(file, "%s,", hexStr);
	WriteHexStr(state.address, 4, hexStr);
	fprintf(file, "%s,", hexStr);
	WriteHexStr(state.data, 2, hexStr);
	fprintf(file, "%s\n", hexStr);
}

void PrintStateHeader()
{
	printf("Cycle\tRW\tA\tX\tY\tIR\tStatus\tSP\tPS\tAddr\tData\n\n");
}

void PrintState(int cycleNumber, struct cpu_state state)
{
	printf("%i\t", cycleNumber);
	printf("%i\t", state.rw);
	PrintHex(state.a, 2);
	printf("\t");
	PrintHex(state.x, 2);
	printf("\t");
	PrintHex(state.y, 2);
	printf("\t");
	PrintHex(state.ir, 2);
	printf("\t");
	PrintHex(state.p, 2);
	printf("\t");
	PrintHex(state.sp, 2);
	printf("\t");
	PrintHex(state.pc, 4);
	printf("\t");
	PrintHex(state.address, 4);
	printf("\t");
	PrintHex(state.data, 2);
	printf("\n");
}
