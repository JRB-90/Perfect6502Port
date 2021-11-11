#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "perfect6502.h"
#include "ansi_colors.h"
#include "console_utils.h"

#define MAX_CYCLES 100
#define SETUP_ADDR 0x8000
#define INPUT_FILE_PATH "C:\\Development\\Test\\main.bin"
#define OUTPUT_FILE_PATH "C:\\Development\\Test\\cpu_out.csv"

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int BOOL;

extern uint8_t memory[65536];

FILE* file;

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

struct {
	BOOL crash;
	int length;
	int cycles;
	int addmode;
	BOOL zp;
	BOOL abs;
	BOOL zpx;
	BOOL absx;
	BOOL zpy;
	BOOL absy;
	BOOL izx;
	BOOL izy;
	BOOL reads;
	BOOL writes;
	BOOL inputa;
	BOOL inputx;
	BOOL inputy;
	BOOL inputs;
	BOOL inputp;
	BOOL outputa;
	BOOL outputx;
	BOOL outputy;
	BOOL outputs;
	BOOL outputp;
} data[256];

enum {
	ADDMODE_UNKNOWN,
	ADDMODE_IZY,
	ADDMODE_IZX,
	ADDMODE_ZPY,
	ADDMODE_ZPX,
	ADDMODE_ZP,
	ADDMODE_ABSY,
	ADDMODE_ABSX,
	ADDMODE_ABS,
};

uint16_t initial_s, initial_p, initial_a, initial_x, initial_y;
void* state;

void SetupMemoryManually();
void SetupMemoryFromBinFile(char* filePath);
struct cpu_state GetCurrentState(void* state);
void WriteStateToFile(int cycleNumber, struct cpu_state state);
void PrintStateHeader();
void PrintState(int cycleNumber, struct cpu_state state);

int main(int argc, char* argv[])
{
	state = initAndResetChip();
	//SetupMemoryManually();
	SetupMemoryFromBinFile(INPUT_FILE_PATH);

	file = fopen(OUTPUT_FILE_PATH, "w");

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

void SetupMemoryManually()
{
	memset(memory, 0, 65536);

	uint16_t addr = SETUP_ADDR;
	memory[0xFFFC] = SETUP_ADDR & 0xFF;
	memory[0xFFFD] = SETUP_ADDR >> 8;

	memory[addr++] = 0xEA; // NOP
	memory[addr++] = 0xEA; // NOP
	memory[addr++] = 0xEA; // NOP
	memory[addr++] = 0xEA; // NOP
	memory[addr++] = 0x4C; // JMP -> 0x8000
	memory[addr++] = 0x00;
	memory[addr++] = 0x80;
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
