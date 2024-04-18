#pragma once

#ifndef FILELOGGER_H
#define FILELOGGER_H

#include "Logger.h"

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <fstream>



class FileLogger : public Logger {
public:

	// Constructor
	FileLogger(const std::string& filename);

	// Destructor
	~FileLogger();

	void log(const std::string& message, LogType type = LogType::INFO) override;

	void printType(LogType type) override;

	//void log(int value, LogType type = LogType::INFO);

	//void log(const std::vector<int>& values, LogType type = LogType::INFO);

private:
	
	std::ofstream outputFile;

};
#endif
