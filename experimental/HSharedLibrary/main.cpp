#include "HSharedLibrary.h"
#include "plugin.h"
#include <iostream>

int main() {
    Ht::HSharedLibrary sharedLibrary("./libpluginA.so");

    if (!sharedLibrary.load()) {
        return 1;
    }

    typedef Plugin* (*create_t)();
    create_t createPlugin = (create_t)sharedLibrary.getSymbol("createPlugin");

    if (!createPlugin) {
        return 1;
    }

    Plugin* plugin = createPlugin();
    if (plugin) {
        plugin->doSomething();
        delete plugin;
    }

    sharedLibrary.unload();

    return 0;
}

