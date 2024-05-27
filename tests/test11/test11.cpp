#include "HLogging.h"
#include "HString.h"
#include <iostream>

int main() {
    try {
        Ht::HLogging logger(Ht::HString("application.log"));

        logger.log(Ht::HLogging::Severity::INFO, Ht::HString("Application started"));
        logger.log(Ht::HLogging::Severity::WARNING, Ht::HString("This is a warning message"));
        logger.log(Ht::HLogging::Severity::ERROR, Ht::HString("An error has occurred"));

        logger.setSeverity(Ht::HLogging::Severity::WARNING);
        logger.log(Ht::HLogging::Severity::INFO, Ht::HString("This info message will not be logged because severity is set to WARNING"));
        logger.log(Ht::HLogging::Severity::WARNING, Ht::HString("This warning message will be logged"));

        std::cout << "Logging completed. Check application.log for log messages." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

