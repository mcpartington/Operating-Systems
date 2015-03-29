#include "random.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
	int i;
	long n = -2;
	/* generate 100 random CPU bursts and random numbers in (0, 1) */
	for (i = 0; i < 100; i++) {
		printf("Burst %d = %d, ", i, CPUBurstRandom(10));
		printf("random number %d = %f\n", i, ran1(&n));
	}

	return 0;
}

