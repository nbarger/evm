#ifndef LOADER_H
#define LOADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

size_t getCode(char* path, uint8_t* toWrite);

#endif
