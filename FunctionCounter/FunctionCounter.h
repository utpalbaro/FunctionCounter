#ifndef FUNCTIONCOUNTER_H
#define FUNCTIONCOUNTER_H

#include <cstddef>

/**
* This file contains publicly available functions i.e. 
* functions that can be called from client programs.
*/
namespace fc
{
    struct FunctionData
    {
        const void* funcAddr;
        unsigned int count;
    };

    void startRecording();
    void stopRecording();
    void resetRecordingData();
    bool isRecording();
    size_t getDataSize();
    void getFunctionData(FunctionData* data, const size_t count);
}
#endif // !FUNCTIONCOUNTER_H
