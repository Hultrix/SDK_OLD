// g++ -o process_manager main.cpp -std=c++11

#include <iostream>
#include <ostream>
#include <stdexcept>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <map>

namespace Ht {

enum class ProcessType {
    Daemon,
    Normal
};

class HProcessManager {
public:
    HProcessManager(ProcessType type);

    pid_t start(const std::string& command);
    void stop(pid_t pid);
    void pause(pid_t pid);
    void resume(pid_t pid);
    pid_t restart(pid_t pid);

private:
    ProcessType type;
    std::map<pid_t, std::string> processes;
};

HProcessManager::HProcessManager(ProcessType type) : type(type) {}

pid_t HProcessManager::start(const std::string& command) {
    pid_t pid = fork();
    if (pid == -1) {
        throw std::runtime_error("Failed to fork.");
    } else if (pid == 0) {
        if (type == ProcessType::Daemon) {
            setsid(); // Detach from the controlling terminal
            close(STDIN_FILENO); // Close standard input
            close(STDOUT_FILENO); // Close standard output
            close(STDERR_FILENO); // Close standard error
        }
        execl("/bin/sh", "sh", "-c", command.c_str(), nullptr);
        exit(EXIT_FAILURE); // If exec fails
    }
    processes[pid] = command;
    return pid;
}

void HProcessManager::stop(pid_t pid) {
    if (processes.find(pid) != processes.end()) {
        kill(pid, SIGTERM);
        waitpid(pid, nullptr, 0);
        processes.erase(pid);
    }
}

void HProcessManager::pause(pid_t pid) {
    if (processes.find(pid) != processes.end()) {
        kill(pid, SIGSTOP);
    }
}

void HProcessManager::resume(pid_t pid) {
    if (processes.find(pid) != processes.end()) {
        kill(pid, SIGCONT);
    }
}

pid_t HProcessManager::restart(pid_t pid) {
    if (processes.find(pid) != processes.end()) {
        std::string command = processes[pid];
        stop(pid);
        return start(command);
    } else {
        std::cerr << "Failed to restart: No such process found." << std::endl;
        return -1;
    }
}

} // namespace Ht

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

