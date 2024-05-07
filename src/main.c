
#include <stdio.h>

#include "evm.h"
#include "evmdefs.h"

int main()
{
    EVMInstance* mainInstance = evmNew();



    evmEnd(mainInstance);

    return 0;
}
