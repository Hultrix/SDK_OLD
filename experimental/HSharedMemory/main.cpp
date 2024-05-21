// g++ -o shared_memory main.cpp -std=c++20
#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>

namespace Ht {

class HSharedMemory {
public:
    HSharedMemory(const std::string& name);
    ~HSharedMemory();

    void write(const std::string& data);
    std::string read();
    void close();

private:
    std::string name;
    int fd;
};

HSharedMemory::HSharedMemory(const std::string& name) : name(name) {
    fd = shm_open(name.c_str(), O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        throw std::runtime_error("Error creating shared memory");
    }
}

HSharedMemory::~HSharedMemory() {
    close();
}

void HSharedMemory::write(const std::string& data) {
    size_t size = data.size();
    ftruncate(fd, size);
    void* ptr = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        throw std::runtime_error("Error mapping memory");
    }
    memcpy(ptr, data.data(), size);
    munmap(ptr, size);
}

std::string HSharedMemory::read() {
    struct stat stat;
    fstat(fd, &stat);
    size_t size = stat.st_size;
    void* ptr = mmap(nullptr, size, PROT_READ, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        throw std::runtime_error("Error mapping memory");
    }
    std::string data(static_cast<char*>(ptr), size);
    munmap(ptr, size);
    return data;
}

void HSharedMemory::close() {
    ::close(fd);
}

} // namespace Ht

int main() {
    Ht::HSharedMemory writer("/my_shared_memory");
    writer.write("Hello from writer program");

    Ht::HSharedMemory reader("/my_shared_memory");
    std::string data = reader.read();
    std::cout << "Data read from shared memory: " << data << std::endl;

    return 0;
}

