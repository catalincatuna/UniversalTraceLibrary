#include "FileLogger.h"

FileLogger::FileLogger(const std::string& filename) : outputFile(filename)
{
}


FileLogger::~FileLogger()
{
}

void FileLogger::log(const std::string& message, LogType type) 
{
    // Process log message
    FileLogger::printType(type);

    outputFile << message << std::endl;
}

void FileLogger::printType(LogType type) {

    outputFile << Logger::getTimeString() << " ";

    switch (type) {
    case LogType::INFO:
        outputFile << "[INFO]: ";
        break;
    case LogType::WARNING:
        outputFile << "[WARNING]: ";
        break;
    case LogType::ERROR:
        outputFile << "[ERROR]: ";
        break;
    case LogType::SENSITIVE:
        outputFile << "[SENSITIVE]: ";
        break;
    }
}
