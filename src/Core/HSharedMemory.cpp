#include "HSharedMemory.h"

namespace Ht {

HSharedMemory::HSharedMemory(const std::string& name) : name(name) {
    fd = shm_open(name.c_str(), O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        throw std::runtime_error("Error creating shared memory");
    }
}

HSharedMemory::~HSharedMemory() {
    close();
}

void HSharedMemory::write(const HString& data) {
    size_t size = data.data().size();
    ftruncate(fd, size);
    void* ptr = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        throw std::runtime_error("Error mapping memory");
    }
    memcpy(ptr, data.c_str(), size);
    munmap(ptr, size);
}

HString HSharedMemory::read() {
    struct stat stat;
    fstat(fd, &stat);
    size_t size = stat.st_size;
    void* ptr = mmap(nullptr, size, PROT_READ, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        throw std::runtime_error("Error mapping memory");
    }
    std::string data(static_cast<char*>(ptr), size);
    munmap(ptr, size);
    return HString(data.c_str());
}

void HSharedMemory::close() {
    ::close(fd);
}

} // namespace Ht

