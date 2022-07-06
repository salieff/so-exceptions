#include <exception>
#include <iostream>

typedef void (*throwFuncPtr)(void);
extern "C" void FunctionCatch(const throwFuncPtr f)
{
    try
    {
        (*f)();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Catch exception: " << e.what() << std::endl;
    }
}
