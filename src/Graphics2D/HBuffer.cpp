#include "HBuffer.h"

namespace Ht {

HBuffer::HBuffer(int width, int height)
    : m_width(width), m_height(height), m_data(width * height * 4, 0) // Assuming 4 bytes per pixel (RGBA)
{}

HBuffer::~HBuffer() {}

uint8_t* HBuffer::data() {
    return m_data.data();
}

int HBuffer::width() const {
    return m_width;
}

int HBuffer::height() const {
    return m_height;
}

int HBuffer::size() const {
    return static_cast<int>(m_data.size());
}

} // namespace Ht

