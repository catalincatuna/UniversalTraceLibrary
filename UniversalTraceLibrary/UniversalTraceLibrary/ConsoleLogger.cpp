#include "ConsoleLogger.h"



    ConsoleLogger::ConsoleLogger() : stopLogging(false) {

    }

    ConsoleLogger::~ConsoleLogger() {

    }

    void ConsoleLogger::log(const std::string& message, LogType type) {
        // Enqueue log message
       
        Logger::printType(type);
        std::cout << message << std::endl;
    }



