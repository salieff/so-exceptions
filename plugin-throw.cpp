#include <stdexcept>

extern "C" void FunctionThrow(void)
{
    throw std::runtime_error("I come from another plugin!");
}
