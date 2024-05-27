#include "HFile.h"
#include <fstream>
#include <stdexcept>

namespace Ht {

HFile::HFile(const HString& filename) : m_filename(filename) {}

bool HFile::exists() const {
    std::ifstream file(m_filename.c_str());
    return file.good();
}

HString HFile::read() const {
    std::ifstream file(m_filename.c_str());
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for reading: " + m_filename.data());
    }

    HString content;
    std::string line;
    while (std::getline(file, line)) {
        content.append(line + "\n");
    }
    file.close();
    return content;
}

void HFile::write(const HString& content) {
    std::ofstream file(m_filename.c_str());
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing: " + m_filename.data());
    }

    file << content.c_str();
    file.close();
}

} // namespace Ht

