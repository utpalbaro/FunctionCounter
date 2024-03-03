#ifndef SYMBOLSMANAGER_H
#define SYMBOLSMANAGER_H
#include <cstddef>

namespace sm {
    bool getFunctionInfo(const void* address, char* functionInfo, const size_t maxlen);
}


#endif
