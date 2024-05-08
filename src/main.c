
#include "evm.h"
#include "evmdefs.h"

int main()
{
	uint8_t* ex = malloc(128);
	ex[0] = 0x2;
	ex[1] = 0x0;
	ex[2] = 'h';
	ex[3] = 0x1;
	ex[4] = 0;

	EVMInstance* mainInstance = evmNew();

	evmLoadCode(mainInstance, 0, ex, 128);

	evmStart(mainInstance, 0);

	while (mainInstance->running)
	{
		evmMonitor(mainInstance);
		evmCycle(mainInstance);
	}

	evmMonitor(mainInstance);
	evmDataDump(mainInstance);

	evmEnd(mainInstance);

	free(ex);

	return 0;
}
