// pluginA.cpp
#include "plugin.h"
#include <iostream>

class PluginA : public Plugin {
public:
    void doSomething() override {
        std::cout << "Hultrix PluginA doing something!" << std::endl;
    }
};

extern "C" Plugin* createPlugin() {
    return new PluginA();
}

