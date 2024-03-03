#include "../FunctionCounter.h"
#include "BSTMap.h"
#include <unordered_map>

namespace fc 
{
    static BSTMap<const void*, unsigned int> gFunctionData;
    static bool gRecording = false;

    void entryHandler(const void* funcAddr);
    void exitHandler(const void* funcAddr);
}

void fc::startRecording()
{
    gRecording = true;
}

void fc::stopRecording()
{
    gRecording = false;
}

void fc::resetRecordingData()
{
    gFunctionData.clear();
}

bool fc::isRecording()
{
    return gRecording;
}

size_t fc::getDataSize()
{
    return gFunctionData.size();
}

// Why am I not sending data via a map or even a vector?
// Because, those template types can be trouble in this case
// where the compiler will be inserting _penter/_pexit hooks in
// the client template instantiations but not in this FunctionCounter
// module. Had a weird behavior because of this where program would
// just get stuck. Even debugging was weird with no indication 
// of what's wrong
void fc::getFunctionData(fc::FunctionData* data, const size_t count)
{
    gFunctionData.getData(data, count);
}

void fc::entryHandler(const void* funcAddr)
{
    if (gRecording)
        ++gFunctionData[funcAddr];
}

void fc::exitHandler(const void* funcAddr)
{
    // Not doing anything currently
    return;
}
