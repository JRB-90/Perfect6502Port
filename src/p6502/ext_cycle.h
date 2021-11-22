#pragma once

#include "exported.h"

EXPORTED int SetupChipAndMemory(const char* path);

EXPORTED int DestroyChipAndMemory();

EXPORTED int StepCpu();

EXPORTED int GetRW();

EXPORTED int GetA();

EXPORTED int GetX();

EXPORTED int GetY();

EXPORTED int GetIR();

EXPORTED int GetP();

EXPORTED int GetSP();

EXPORTED int GetPC();

EXPORTED int GetAddress();

EXPORTED int GetData();