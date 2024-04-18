#include "AsyncLogger.h"



AsyncLogger::AsyncLogger(Logger* logger) : stopLogging(false) {
    // Create threads
    for (int i = 0; i < std::thread::hardware_concurrency() / 2; ++i) {
        threads.emplace_back(&AsyncLogger::loggingThread, this);
    }

    this->logger = logger;
}

AsyncLogger::~AsyncLogger() {
    // Signal to stop logging
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        stopLogging = true;
    }
    queueCondition.notify_all();

    // Join threads
    for (std::thread& thread : threads) {
        thread.join();
    }
}

void AsyncLogger::asyncLog(const std::string& message, LogType type) {
    // Enqueue log message

    std::lock_guard<std::mutex> lock(queueMutex);
    logQueue.emplace(message, type);

    // Notify a thread to process the log message
    queueCondition.notify_one();
}


void AsyncLogger::loggingThread() {
    while (true) {
        // Dequeue log message
        std::pair<std::string, LogType> logMessage;

        std::unique_lock<std::mutex> lock(queueMutex);
        queueCondition.wait_for(lock, std::chrono::seconds(2), [this] { return !logQueue.empty() || stopLogging; });
        if (stopLogging && logQueue.empty()) {
            // Exit the thread if logging is stopped and the queue is empty
            break;
        }
        logMessage = logQueue.front();
        logQueue.pop();



        // log the message using the custom logger method
        this->logger->log(logMessage.first, logMessage.second);

    }
}



