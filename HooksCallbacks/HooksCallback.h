#ifndef HOOKSCALLBACK_H
#define HOOKSCALLBACK_H

extern "C" void onFunctionEnter(const void* funcAddr);
extern "C" void onFunctionExit(const void* funcAddr);

#endif // !HOOKSCALLBACK_H

