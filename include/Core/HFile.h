#pragma once
#include "HString.h"

namespace Ht {

class HFile {
public:
    // Constructor
    HFile(const HString& filename);

    // Check if the file exists
    bool exists() const;

    // Read the entire file into an HString
    HString read() const;

    // Write an HString to the file
    void write(const HString& content);

private:
    HString m_filename;
};

} // namespace Ht

