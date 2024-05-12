#include "loader.h"

size_t getCode(char* path, uint8_t* toWrite)
{
	FILE* f = fopen(path, "rb");

	if (f == NULL)
	{
		fprintf(stderr, "Could not read file.\n");
		exit(1);
	}

	fseek(f, 0, SEEK_END);
	size_t codeLen = ftell(f);
	fseek(f, 0, SEEK_SET);

	fread(toWrite, sizeof(uint8_t), codeLen, f);

	fclose(f);

	return codeLen;
}
