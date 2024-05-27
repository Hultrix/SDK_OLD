#pragma once
#include "HString.h"
#include <vector>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdexcept>
#include <cstdio>
#include <unistd.h>


namespace Ht {

class HDir {
public:
    // Constructor
    HDir(const HString& path);

    // Check if the directory exists
    bool exists() const;

    // Create the directory
    void create() const;

    // List files in the directory
    std::vector<HString> listFiles() const;

    // Remove the directory
    void remove() const;

private:
    HString m_path;
};

} // namespace Ht

