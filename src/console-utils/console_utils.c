#include "console_utils.h"

void PrintHex(int value, int length)
{
	char hexStr[8];
	WriteHexStr(value, length, hexStr);
	printf("%s", hexStr);
}

void WriteHexStr(int value, int length, const char* buf)
{
	int preceedingZeros;
	char hexStr[8];
	char hexChars[8];
	char baseStr[8];
	sprintf(hexChars, "%X", value);

	if (length == 2)
	{
		if (value > 15)
		{
			preceedingZeros = 0;
		}
		else
		{
			preceedingZeros = 1;
		}

		sprintf(baseStr, "%s", "0x00");
	}
	else if (length == 4)
	{
		preceedingZeros = 3;
		if (value > 15)
		{
			preceedingZeros = 2;
		}
		if (value > 255)
		{
			preceedingZeros = 1;
		}
		if (value > 4095)
		{
			preceedingZeros = 0;
		}

		sprintf(baseStr, "%s", "0x0000");
	}
	else
	{
		exit(1);
	}

	int numberHexChars = length - preceedingZeros;
	for (int i = 0; i < numberHexChars; i++)
	{
		baseStr[2 + preceedingZeros + i] = hexChars[i];
	}

	return memcpy(buf, baseStr, 8);
}
