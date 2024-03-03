#include "../../SymbolsManager.h"
#include <cstring>
#include <cstdlib>
#include <dlfcn.h>
#include <iostream>
#include <cxxabi.h>

bool sm::getFunctionInfo(const void* address, char* functionInfo, const size_t maxlen)
{
    Dl_info info;

    // It will fill info struct
    dladdr(address, &info);

    // This char* is malloced inside this function, need to clear it
    char* fName = abi::__cxa_demangle(info.dli_sname, NULL, NULL, NULL);

    if (fName == nullptr)
        return false;

    strncpy(functionInfo, fName, maxlen);

    // free the malloc'ed fInfo
    free(fName);

    return true;
}