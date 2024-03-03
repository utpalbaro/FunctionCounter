#include <Windows.h>
#include <imagehlp.h>
#include <intrin.h>
#include <strsafe.h>
#include "../../SymbolsManager.h"

class SymbolsManager
{
public:
    SymbolsManager(const SymbolsManager&) = delete;
    SymbolsManager(const SymbolsManager&&) = delete;
    SymbolsManager& operator = (const SymbolsManager&) = delete;
    SymbolsManager& operator = (const SymbolsManager&&) = delete;
    ~SymbolsManager();

    bool getFunctionInfo(const void* address, char* functionInfo, const unsigned int maxlen);

    inline static SymbolsManager& getInstance()
    {
        static SymbolsManager inst;
        return inst;
    }

private:
    SymbolsManager();

private:
    bool _symbolsInitialized;
};

// @TODO There are windows APIs which are not thread safe (as mentioned in MS docs)
// Go over them and try to make them thread safe

SymbolsManager::SymbolsManager() : _symbolsInitialized(false)
{
    // Options to control how symbols should appear
    SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS);

    // The SymInitialize function is used to initialize the symbol handler for a process [MSDN]
    // If fInvadeProcess is FALSE it will NOT call SymLoadModuleEx
    _symbolsInitialized = SymInitialize(GetCurrentProcess(), NULL, TRUE);
}

SymbolsManager::~SymbolsManager()
{
    if (!_symbolsInitialized)
        SymCleanup(GetCurrentProcess());
}

bool SymbolsManager::getFunctionInfo(const void* address, char* functionInfo, const unsigned int maxlen)
{
    if (!_symbolsInitialized)
        return false;

    DWORD64 displacement64 = 0;   // Won't use it, but needed just for passing to SymAddr

    // SYMBOL_INFO struct. Size calculation stated in MSDN
    TCHAR buffer[sizeof(SYMBOL_INFO) + (MAX_SYM_NAME - 1) * sizeof(TCHAR)];
    memset(&buffer, 0, sizeof(buffer));

    PSYMBOL_INFO pSymInfo = (PSYMBOL_INFO)buffer;
    pSymInfo->SizeOfStruct = sizeof(SYMBOL_INFO);   // MS mandates it to be set so
    pSymInfo->MaxNameLen = MAX_SYM_NAME;

    // This will fillup the SYMBOL_INFO struct with name and other details
    BOOL symResult = SymFromAddr(GetCurrentProcess(), (DWORD64)address, &displacement64, pSymInfo);

    // @TODO should print out the error
    if (!symResult)
        return false;

    // If we don't skip, it will show a lot of header only
    // (class/function templates), as they become part of the
    // translation unit they're used in
    if (strstr(pSymInfo->Name, "std::"))
        return false;

    DWORD displacement;
    IMAGEHLP_LINE64 line;
    line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
    BOOL lineRes = SymGetLineFromAddr64(GetCurrentProcess(), (DWORD64)address, &displacement, &line);

    if (!lineRes)
        return false;

    // Collect all the info
    int ret = sprintf_s(functionInfo, maxlen, "%s; %s; %u", pSymInfo->Name, line.FileName, line.LineNumber);

    return ret == -1 ? false : true;
}

bool sm::getFunctionInfo(const void* address, char* functionInfo, const unsigned int maxlen)
{
    return SymbolsManager::getInstance().getFunctionInfo(address, functionInfo, maxlen);
}
