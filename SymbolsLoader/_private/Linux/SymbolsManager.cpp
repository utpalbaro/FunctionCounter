#include "../../SymbolsManager.h"
#include <cstring>
#include <cstdlib>
#include <execinfo.h>
#include <iostream>

bool sm::getFunctionInfo(const void* address, char* functionInfo, const unsigned int maxlen)
{
    char **fInfo;   // It will be malloced inside
    void *array[1];

    // backtrace_symbols needs it like that
    memcpy(array, address, sizeof(void*));

    fInfo = backtrace_symbols (array, 1);

    strcpy(functionInfo, fInfo[0]);

    // free the malloc'ed fInfo
    free(fInfo);

    return true;
}