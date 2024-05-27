#pragma once

#include "HString.h"
#include <string>
#include <stdexcept>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstring>

namespace Ht {

class HSharedMemory {
public:
    HSharedMemory(const std::string& name);
    ~HSharedMemory();

    void write(const HString& data);
    HString read();
    void close();

private:
    std::string name;
    int fd;
};

} // namespace Ht

