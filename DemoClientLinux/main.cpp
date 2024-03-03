#include <iostream>
#include <memory>
#include "../FunctionCounter/FunctionCounter.h"
#include "../SymbolsLoader/SymbolsManager.h"

int add(int a, int b)
{
    return a + b;
}

int sub(int a, int b)
{
    return a - b;
}

int main()
{
    fc::startRecording();

    for (int i = 0; i < 20; ++i)
        sub(i, i + 10);

    for (int i = 0; i < 10; ++i)
        add(i, i + 1);

    fc::stopRecording();
    std::cout << "Hello\n";

    auto num = fc::getDataSize();
    auto data = std::make_unique<fc::FunctionData[]>(num);

    fc::getFunctionData(data.get(), num);

    const int MAX_INFO = 2048;
    char fInfo[MAX_INFO];

    for (size_t i = 0; i < num; ++i)
    {
        std::cout << data[i].funcAddr << "; " << data[i].count << "\n";

        // if (!sm::getFunctionInfo(data[i].funcAddr, fInfo, MAX_INFO))
        //     continue;

        // std::cout << fInfo << "\n";
    }
    std::cout << "World\n";

    return 0;
}