#include "evm.h"
#include "evmdefs.h"
#include "loader.h"

int main(int argc, char** argv)
{
	uint8_t* code;

	if (argc < 1)
	{
		fprintf(stderr, "Please pass a file name.");
		return 1;
	}
	
	code = malloc(sizeof(uint8_t)*CODE_MAX);

	size_t codeLen = getCode(argv[1], code);

	EVMInstance* mainInstance = evmNew();

	evmLoadCode(mainInstance, 0, code, codeLen);

	evmStart(mainInstance, 0);

	while (mainInstance->running)
	{
		//evmMonitor(mainInstance);
		evmCycle(mainInstance);
		//getchar();
	}

	//evmMonitor(mainInstance);
	//evmCodeDump(mainInstance);

	//printf("%x\n", mainInstance->dataStack[0]);

	evmEnd(mainInstance);

	free(code);

	return 0;
}
