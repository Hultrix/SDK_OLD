#include "HProcessManager.h"

#include <iostream>
#include <stdexcept>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

namespace Ht {

HProcessManager::HProcessManager(ProcessType type) : type(type) {}

pid_t HProcessManager::start(const HString& command) {
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
        HString command = processes[pid];
        stop(pid);
        return start(command);
    } else {
        std::cerr << "Failed to restart: No such process found." << std::endl;
        return -1;
    }
}

} // namespace Ht

