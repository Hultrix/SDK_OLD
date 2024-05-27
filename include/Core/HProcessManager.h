#pragma once

#include "HString.h"
#include <map>
#include <sys/types.h>

namespace Ht {

enum class ProcessType {
    Daemon,
    Normal
};

class HProcessManager {
public:
    HProcessManager(ProcessType type);

    pid_t start(const HString& command);
    void stop(pid_t pid);
    void pause(pid_t pid);
    void resume(pid_t pid);
    pid_t restart(pid_t pid);

private:
    ProcessType type;
    std::map<pid_t, HString> processes;
};

} // namespace Ht

