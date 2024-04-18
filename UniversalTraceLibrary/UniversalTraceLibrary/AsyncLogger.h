#ifndef AsyncLogger_H
#define AsyncLogger_H

#include "Logger.h"

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>



class AsyncLogger {
public:

	// Constructor
	AsyncLogger(Logger* logger);

	// Destructor
	~AsyncLogger();

	void asyncLog(const std::string& message, LogType type = LogType::INFO);


private:
	std::queue<std::pair<std::string, LogType>> logQueue;
	std::mutex queueMutex;
	std::condition_variable queueCondition;
	bool stopLogging;
	std::vector<std::thread> threads;
	Logger* logger;

	void loggingThread();
};
#endif