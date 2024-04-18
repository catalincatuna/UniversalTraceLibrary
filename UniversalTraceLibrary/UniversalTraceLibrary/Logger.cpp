#include "Logger.h"

std::string Logger::getTimeString()
{
    // Get current time
    std::time_t currentTime;
    std::time(&currentTime);

    // Convert time to local time
    std::tm localTime;
    localtime_s(&localTime, &currentTime);

    // Format time as string
    std::stringstream ss;
    ss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}



void Logger::printType(LogType type) {

    std::cout << Logger::getTimeString() << " ";

    switch (type) {
    case LogType::INFO:
        std::cout << "[INFO]: ";
        break;
    case LogType::WARNING:
        std::cout << "[WARNING]: ";
        break;
    case LogType::ERROR:
        std::cout << "[ERROR]: ";
        break;
    case LogType::SENSITIVE:
        std::cout << "[SENSITIVE]: ";
        break;
    }
}
