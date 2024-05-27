#include "HSharedLibrary.h"

namespace Ht {

HSharedLibrary::HSharedLibrary(const std::string& libraryPath)
    : libraryPath(libraryPath), handle(nullptr) {}

HSharedLibrary::~HSharedLibrary() {
    unload();
}

bool HSharedLibrary::load() {
    handle = dlopen(libraryPath.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "Cannot load library: " << dlerror() << std::endl;
        return false;
    }
    dlerror(); // Clear any existing error
    return true;
}

void HSharedLibrary::unload() {
    if (handle) {
        dlclose(handle);
        handle = nullptr;
    }
}

void* HSharedLibrary::getSymbol(const std::string& symbolName) {
    if (!handle) {
        std::cerr << "Library not loaded" << std::endl;
        return nullptr;
    }
    void* symbol = dlsym(handle, symbolName.c_str());
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol " << symbolName << ": " << dlsym_error << std::endl;
        return nullptr;
    }
    return symbol;
}

} // namespace Ht

