#include "HDir.h"


namespace Ht {

HDir::HDir(const HString& path) : m_path(path) {}

bool HDir::exists() const {
    struct stat info;
    if (stat(m_path.c_str(), &info) != 0) {
        return false; // Directory does not exist
    }
    return (info.st_mode & S_IFDIR) != 0; // Check if it's a directory
}

void HDir::create() const {
    if (mkdir(m_path.c_str(), 0777) != 0) {
        throw std::runtime_error("Could not create directory: " + m_path.data());
    }
}

std::vector<HString> HDir::listFiles() const {
    std::vector<HString> files;
    DIR* dir;
    struct dirent* entry;

    if ((dir = opendir(m_path.c_str())) == nullptr) {
        throw std::runtime_error("Could not open directory: " + m_path.data());
    }

    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_REG) { // Only include regular files
            files.emplace_back(entry->d_name);
        }
    }
    closedir(dir);
    return files;
}

void HDir::remove() const {
    if (rmdir(m_path.c_str()) != 0) {
        throw std::runtime_error("Could not remove directory: " + m_path.data());
    }
}

} // namespace Ht

