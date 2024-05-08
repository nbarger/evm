#include "loader.h"

uint8_t* getCode(char* path)
{
	uint8_t* code;

	FILE* f = fopen(path, "rb");

	if (f == NULL)
	{
		fprintf(stderr, "Could not read file.\n");
		exit(1);
	}

	fseek(f, 0, SEEK_END);
	size_t codeLen = ftell(f);
	fseek(f, 0, SEEK_SET);

	code = malloc(codeLen);

	fread(code, sizeof(uint8_t), codeLen, f);

	fclose(f);

	return code;
}
