#pragma once

#include <vector>
#include <cstdint>

namespace Ht {

class HBuffer {
public:
    HBuffer(int width, int height);
    ~HBuffer();

    uint8_t* data();
    int width() const;
    int height() const;
    int size() const;

private:
    int m_width;
    int m_height;
    std::vector<uint8_t> m_data;
};

} // namespace Ht

