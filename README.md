# About

For any x64 Windows C++ program, this project provides a means of making Visual Studio C++ compiler **automatically** insert code at the entry and exit of functions.

# Disclaimer

- This project only works on **Windows** with Visual Studio compiler.
- Only works with programs built with debug symbols (DEBUG/DEBUG_REL).

**NOTE**: For Linux, GCC has a switch *-finstrument-functions* and a few other switches to do similar things. Need to have a look at them later.

# How to execute the demo

- Compile the solution, *FunctionCounter.sln* in Visual Studio
- Run (Launch) the program
- For every function that was called, it will print the name, path, line and the call count

# Structure

This Visual Studio solution contains three projects,

| VC project          | Details                                                |
| ------------------- | ------------------------------------------------------ |
| **SymbolsLoader**   | Generates a static .lib that loads debugging symbols   |
| **FunctionCounter** | Generates a static .lib that counts the function calls |
| **DemoClient**      | A demo client program that uses the above libraries    |

# Usage

Build the solution *FunctionCounter.sln* so that you get *SymbolsLoader.lib* and *FunctionCounter.lib*.

1. Whichever files/modules in your client code you want MSVC to add hooks to, need to be compiled with */Gh* and */GH* compiler switches for *_penter* and *_pexit* hooks respectively.
2. Link the generated *.lib* files (should be in *x64/Debug* folder) namely, *FunctionCounter.lib* and *SymbolsLoader.lib* to your program
3. *FunctionCounter.h* contains all the publicly available functions that can be called.

# Credits

- This work derives heavily from [A Simple C++ Profiler on x64](https://www.codeproject.com/articles/800172/a-simple-cplusplus-profiler-on-x). Especially the code in the assembly file (*HooksImpl.asm*). 
- The stack manipulation performed in *HooksImpl.asm* file are in accordance with the [x64 calling convention](https://learn.microsoft.com/en-us/cpp/build/x64-calling-convention?view=msvc-170)

# References

- [A Simple C++ Profiler on x64](https://www.codeproject.com/articles/800172/a-simple-cplusplus-profiler-on-x)
- [/Gh (Enable _penter hook function)](https://learn.microsoft.com/en-us/cpp/build/reference/gh-enable-penter-hook-function?view=msvc-170)
- [x64 Architecture](https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/x64-architecture?redirectedfrom=MSDN)
- [x64 calling convention](https://learn.microsoft.com/en-us/cpp/build/x64-calling-convention?view=msvc-170)
- [x64 stack usage](https://learn.microsoft.com/en-us/cpp/build/stack-usage?view=msvc-170)
- [x64 ABI conventions](https://learn.microsoft.com/en-us/cpp/build/x64-software-conventions?view=msvc-170)
- [x64 Prolog and Epilog](https://learn.microsoft.com/en-us/cpp/build/prolog-and-epilog?view=msvc-170)
