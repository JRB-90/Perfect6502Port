#include "ext_cycle.h"

#include "perfect6502.h"
#include <stdio.h>

unsigned char* m = NULL;
void* state = NULL;

int SetupChipAndMemory(const char* path)
{
	m = GetMemory();
	state = initAndResetChip();

	memset(m, 0, 65536);
	FILE* binFile = fopen(path, "rb");
	fread(m + 32768, 32768, 1, binFile);
	fclose(binFile);

	if (m == NULL)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

int DestroyChipAndMemory()
{
	if (state == NULL)
	{
		return -1;
	}
	else
	{
		DestroyChip(state);

		return 0;
	}
}

int StepCpu()
{
	if (state == NULL)
	{
		return -1;
	}
	else
	{
		Step(state);

		return 0;
	}
}

int GetRW()
{
	if (state == NULL)
	{
		return -1;
	}
	else
	{
		return (int)readRW(state);
	}
}

int GetA()
{
	if (state == NULL)
	{
		return -1;
	}
	else
	{
		return (int)readA(state);
	}
}

int GetX()
{
	if (state == NULL)
	{
		return -1;
	}
	else
	{
		return (int)readX(state);
	}
}

int GetY()
{
	if (state == NULL)
	{
		return -1;
	}
	else
	{
		return (int)readY(state);
	}
}

int GetIR()
{
	if (state == NULL)
	{
		return -1;
	}
	else
	{
		return (int)readIR(state);
	}
}

int GetP()
{
	if (state == NULL)
	{
		return -1;
	}
	else
	{
		return (int)readP(state);
	}
}

int GetSP()
{
	if (state == NULL)
	{
		return -1;
	}
	else
	{
		return (int)readSP(state);
	}
}

int GetPC()
{
	if (state == NULL)
	{
		return -1;
	}
	else
	{
		return (int)readPC(state);
	}
}

int GetAddress()
{
	if (state == NULL)
	{
		return -1;
	}
	else
	{
		return (int)readAddressBus(state);
	}
}

int GetData()
{
	if (state == NULL)
	{
		return -1;
	}
	else
	{
		return (int)readDataBus(state);
	}
}
