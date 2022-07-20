#include <dlfcn.h>
#include <iostream>
#include <memory>
#include <functional>
#include <stdexcept>


using throwFuncPtr = void (*)(void);
using catchFuncPtr = void (*)(const throwFuncPtr);

static constexpr int dlopenFlags = RTLD_NOW;


auto OpenPlugin(const std::string &pluginName)
{
    auto pluginPtr = dlopen(pluginName.c_str(), dlopenFlags);
    if (!pluginPtr)
        throw std::runtime_error("Can't load plugin " + pluginName + ": " + dlerror());

    std::cout << "Plugin " << pluginName << " successfully opened" << std::endl;

    auto dlDeleter = [pluginName](void *ptr) {
        if (ptr && dlclose(ptr) != 0)
            std::cerr << "Can't close plugin " << pluginName << ": " << dlerror() << std::endl;

        std::cout << "Plugin " << pluginName << " successfully closed" << std::endl;
    };

    return std::shared_ptr<void>(pluginPtr, dlDeleter);
}

template<typename T>
auto OpenSymbol(std::shared_ptr<void> pluginPtr, const std::string &symbolName)
{
    auto funcPtr = reinterpret_cast<T>(dlsym(pluginPtr.get(), symbolName.c_str()));
    if (!funcPtr)
        throw std::runtime_error("Can't load symbol " + symbolName + ": " + dlerror());

    std::cout << "Symbol " << symbolName << " successfully loaded" << std::endl;
    return funcPtr;
}


int main(int, const char **)
{
    try
    {
        auto pluginCatch = OpenPlugin("./libplugin-catch.so");
        auto pluginThrow = OpenPlugin("./libplugin-throw.so");
        auto funcCatch = OpenSymbol<catchFuncPtr>(pluginCatch, "FunctionCatch");
        auto funcThrow = OpenSymbol<throwFuncPtr>(pluginThrow, "FunctionThrow");
        (*funcCatch)(funcThrow);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception catch: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
