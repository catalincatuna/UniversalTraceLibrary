#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H

#include "Logger.h"

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>



class ConsoleLogger : public Logger {
public:

	// Constructor
	ConsoleLogger();

	// Destructor
	~ConsoleLogger();

	void log(const std::string& message, LogType type = LogType::INFO) override;

	void log(int value, LogType type = LogType::INFO) ;

	void log(const std::vector<int>& values, LogType type = LogType::INFO);

private:
	std::queue<std::pair<std::string, LogType>> logQueue;
	std::mutex queueMutex;
	std::condition_variable queueCondition;
	bool stopLogging;
	std::vector<std::thread> threads;

	void loggingThread();
};
#endif