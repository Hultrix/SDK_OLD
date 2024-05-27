#include "HProcessManager.h"
#include "HString.h"

#include <iostream>
#include <unistd.h>

int main() {
    Ht::HProcessManager pm(Ht::ProcessType::Daemon);
    try {
        pid_t pid = pm.start("gnome-text-editor");
        std::cout << "Process started with PID: " << pid << std::endl;
        sleep(5); // Wait for a bit
        pm.pause(pid);
        std::cout << "Process paused." << std::endl;
        
        sleep(5);
        pm.resume(pid);
        std::cout << "Process resumed." << std::endl;
        
        sleep(5);
        pid = pm.restart(pid);
        std::cout << "Process restarted." << std::endl;
        
        sleep(5);
        pm.stop(pid);
        std::cout << "Process stopped." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}

