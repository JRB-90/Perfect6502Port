#include "console_utils.h"

void PrintHex(int value, int length)
{
	int preceedingZeros;

	if (length == 2)
	{
		preceedingZeros = 1;
		if (value > 15)
		{
			preceedingZeros = 0;
		}
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
	}
	else
	{
		exit(1);
	}

	int i;
	char prefix[] = "0x";
	printf("%s", prefix);
	char hexStr[32];
	sprintf(hexStr, "%X", value);

	for (i = 0; i < preceedingZeros; i++)
	{
		printf("0");
	}

	printf("%s", hexStr);
}