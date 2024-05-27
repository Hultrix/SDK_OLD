#include "HSharedMemory.h"
#include "HString.h"
#include <iostream>

int main() {
    try {
        Ht::HSharedMemory writer("/my_shared_memory");
        Ht::HString message("Hello from writer program");
        writer.write(message);

        Ht::HSharedMemory reader("/my_shared_memory");
        Ht::HString data = reader.read();
        std::cout << "Data read from shared memory: " << data << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

