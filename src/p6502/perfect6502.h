#ifndef _PERFECT6502_H_
#define _PERFECT6502_H_

#ifndef INCLUDED_FROM_NETLIST_SIM_C
#define state_t void
#endif

extern state_t *initAndResetChip();
extern void DestroyChip(state_t *state);
extern void Step(state_t *state);
extern void ChipStatus(state_t *state);
extern unsigned short readPC(state_t *state);
extern unsigned char readA(state_t *state);
extern unsigned char readX(state_t *state);
extern unsigned char readY(state_t *state);
extern unsigned char readSP(state_t *state);
extern unsigned char readP(state_t *state);
extern unsigned int readRW(state_t *state);
extern unsigned short readAddressBus(state_t *state);
extern void writeDataBus(state_t *state, unsigned char);
extern unsigned char readDataBus(state_t *state);
extern unsigned char readIR(state_t *state);
extern void SetMemory(unsigned char* m);
extern unsigned char* GetMemory();

extern unsigned char memory[65536];
extern unsigned int cycle;
extern unsigned int transistors;

#endif
