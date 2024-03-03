#include "../HooksCallback.h"

// Forward declaring as these two aren't exposed
// in FunctionCounter.h file
namespace fc {
    void entryHandler(const void* funcAddr);
    void exitHandler(const void* funcAddr);
}

void onFunctionEnter(const void* funcAddr)
{
    fc::entryHandler(funcAddr);
}

void onFunctionExit(const void* funcAddr)
{
    fc::exitHandler(funcAddr);
}