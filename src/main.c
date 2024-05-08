
#include "evm.h"
#include "evmdefs.h"
#include "loader.h"

int main(int argc, char** argv)
{
	if (argc < 1)
	{
		fprintf(stderr, "Please pass a file name.");
		return 1;
	}
	
	uint8_t* code = getCode(argv[1]);

	EVMInstance* mainInstance = evmNew();

	evmLoadCode(mainInstance, 0, code, 128);

	evmStart(mainInstance, 0);

	while (mainInstance->running)
	{
		evmMonitor(mainInstance);
		evmCycle(mainInstance);
	}

	evmMonitor(mainInstance);
	evmDataDump(mainInstance);

	printf("%x\n", mainInstance->dataStack[0]);

	evmEnd(mainInstance);

	free(code);

	return 0;
}
