#include <dlfcn.h>
#include <iostream>

typedef void (*throwFuncPtr)(void);
typedef void (*catchFuncPtr)(const throwFuncPtr);

static constexpr int dlopenFlags = RTLD_NOW;

int main(int, const char **)
{
    auto pluginCatch = dlopen("./libplugin-catch.so", dlopenFlags);
    if (!pluginCatch)
    {
        std::cerr << "Can't load libplugin-catch.so: " << dlerror() << std::endl;
        return 1;
    }

    auto pluginThrow = dlopen("./libplugin-throw.so", dlopenFlags);
    if (!pluginThrow)
    {
        std::cerr << "Can't load libplugin-throw.so: " << dlerror() << std::endl;

        if (dlclose(pluginCatch) != 0)
            std::cerr << "Can't close pluginCatch: " << dlerror() << std::endl;

        return 2;
    }

    auto funcCatch = reinterpret_cast<catchFuncPtr>(dlsym(pluginCatch, "FunctionCatch"));
    if (!funcCatch)
    {
        std::cerr << "Can't load FunctionCatch: " << dlerror() << std::endl;

        if (dlclose(pluginCatch) != 0)
            std::cerr << "Can't close pluginCatch: " << dlerror() << std::endl;

        if (dlclose(pluginThrow) != 0)
            std::cerr << "Can't close pluginThrow: " << dlerror() << std::endl;

        return 3;
    }

    auto funcThrow = reinterpret_cast<throwFuncPtr>(dlsym(pluginThrow, "FunctionThrow"));
    if (!funcThrow)
    {
        std::cerr << "Can't load FunctionThrow: " << dlerror() << std::endl;

        if (dlclose(pluginCatch) != 0)
            std::cerr << "Can't close pluginCatch: " << dlerror() << std::endl;

        if (dlclose(pluginThrow) != 0)
            std::cerr << "Can't close pluginThrow: " << dlerror() << std::endl;

        return 4;
    }

    // Let's do it finally!
    (*funcCatch)(funcThrow);

    if (dlclose(pluginCatch) != 0)
    {
        std::cerr << "Can't close pluginCatch: " << dlerror() << std::endl;
        return 5;
    }

    if (dlclose(pluginThrow) != 0)
    {
        std::cerr << "Can't close pluginThrow: " << dlerror() << std::endl;
        return 6;
    }

    return 0;
}
