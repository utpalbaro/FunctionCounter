# About

For any x64 Windows/Linux C++ program, this project provides a means of making MSVC/GCC **automatically** insert code at the entry and exit of functions at compile time.

# Disclaimer

- This works with programs built with debug symbols (DEBUG/DEBUG_REL).
- For Windows, it uses */Gh* and */GH* MSVC compiler flags for entry and exit hooks
- For Windows, it uses *-finstrument-functions* GCC compiler flag for entry and exit hooks

# How to execute the demo

## Windows

- Compile the solution, *FunctionCounter.sln* in Visual Studio
- Run (Launch) the program
- For every function that was called, it will print the name, path, line and the call count

## Linux

- Run `make` inside the folder *DemoClientLinux*
- Run the file generated inside that folder on a command line,
  ```bash
  ./main.out
  ```
- For every function that was called, it will print the name and the call count of the function

# Structure

This project contains 4 subprojects,

| Project               | Details                                                         |
| --------------------- | --------------------------------------------------------------- |
| **SymbolsLoader**     | Generates a static .lib that loads debugging symbols            |
| **FunctionCounter**   | Generates a static .lib that counts the function calls          |
| **DemoClientWindows** | A demo client program for Windows that uses the above libraries |
| **DemoClientLinux**   | A demo client program for Linux that uses the above libraries   |

# Usage

## Windows

Build the solution *FunctionCounter.sln* so that you get *SymbolsLoader.lib* and *FunctionCounter.lib*.

1. Whichever files/modules in your client code you want MSVC to add hooks to, need to be compiled with */Gh* and */GH* compiler switches for *_penter* and *_pexit* hooks respectively.
2. Link the generated *.lib* files (should be in *x64/Debug* folder) namely, *FunctionCounter.lib* and *SymbolsLoader.lib* to your program
3. *FunctionCounter.h* contains all the publicly available functions that can be called.

## Linux

1. Whichever files/modules in your client code you want GCC to add hooks to, need to be compiled with *-finstrument-functions* compiler switch for both entry and exit hooks.
2. Build *SymbolsLoader* and *FunctionCounter* libraries in whatever way you please, be it *.o*, *.a* or *.so*. No makefile has been provided in this project (yet).

# Credits

- For the Windows implementation, this work derives heavily from [A Simple C++ Profiler on x64](https://www.codeproject.com/articles/800172/a-simple-cplusplus-profiler-on-x). Especially the code in the assembly file (*HooksImpl.asm*). 
- The stack manipulation performed in *HooksImpl.asm* file are in accordance with the [x64 calling convention](https://learn.microsoft.com/en-us/cpp/build/x64-calling-convention?view=msvc-170)

# References

- [A Simple C++ Profiler on x64](https://www.codeproject.com/articles/800172/a-simple-cplusplus-profiler-on-x)
- [/Gh (Enable _penter hook function)](https://learn.microsoft.com/en-us/cpp/build/reference/gh-enable-penter-hook-function?view=msvc-170)
- [x64 Architecture](https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/x64-architecture?redirectedfrom=MSDN)
- [x64 calling convention](https://learn.microsoft.com/en-us/cpp/build/x64-calling-convention?view=msvc-170)
- [x64 stack usage](https://learn.microsoft.com/en-us/cpp/build/stack-usage?view=msvc-170)
- [x64 ABI conventions](https://learn.microsoft.com/en-us/cpp/build/x64-software-conventions?view=msvc-170)
- [x64 Prolog and Epilog](https://learn.microsoft.com/en-us/cpp/build/prolog-and-epilog?view=msvc-170)
- [Instrumentation Options (Using the GNU Compiler Collection (GCC))](https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html)
- [dladdr(3)](https://www.man7.org/linux/man-pages/man3/dladdr.3.html)
