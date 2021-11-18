#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "perfect6502.h"
#include "ansi_colors.h"
#include "console_utils.h"

#define MAX_CYCLES 100
#define SETUP_ADDR 0x8000

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

uint8_t memory[65536];

FILE* file;
void* state;

void SetupMemoryFromBinFile(char* filePath);
struct cpu_state GetCurrentState(void* state);
void WriteStateToFile(int cycleNumber, struct cpu_state state);
void PrintStateHeader();
void PrintState(int cycleNumber, struct cpu_state state);

int main(int argc, char* argv[])
{
	state = initAndResetChip();

	if (argc == 3)
	{
		SetupMemoryFromBinFile(argv[1]);
		file = fopen(argv[2], "w");
	}
	else
	{
		printf(RED);
		printf("Incorrect number of arguments, 2 expected\n");
		printf("Usage: cpucheck input_file output_file\n");
		printf(RST);

		return 1;
	}

	PrintStateHeader();

	for (int i = 0; i < MAX_CYCLES; i++)
	{
		Step(state);
		struct cpu_state currentState = GetCurrentState(state);
		PrintState(i, currentState);
		WriteStateToFile(i, currentState);
	};

	fclose(file);

	DestroyChip(state);

	return 0;
}

void SetupMemoryFromBinFile(char* filePath)
{
	memset(memory, 0, 65536);
	FILE* binFile = fopen(filePath, "rb");
	fread(memory + 32768, 32768, 1, binFile);
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
