#ifndef HSHAREDLIBRARY_H
#define HSHAREDLIBRARY_H

#include <string>
#include <dlfcn.h> // For Unix-like systems
#include <iostream>

namespace Ht {

class HSharedLibrary {
public:
    HSharedLibrary(const std::string& libraryPath);
    ~HSharedLibrary();

    bool load();
    void unload();
    void* getSymbol(const std::string& symbolName);

private:
    std::string libraryPath;
    void* handle;
};

} // namespace Ht

#endif // HSHAREDLIBRARY_H

