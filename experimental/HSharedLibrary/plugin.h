// plugin.h
#ifndef PLUGIN_H
#define PLUGIN_H

class Plugin {
public:
    virtual ~Plugin() {}
    virtual void doSomething() = 0;
};

// Function to create the plugin instance
extern "C" Plugin* createPlugin();

#endif // PLUGIN_H

