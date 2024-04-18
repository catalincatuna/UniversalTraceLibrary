#include "AsyncLogger.h"



AsyncLogger::AsyncLogger() : stopLogging(false) {
    // Create threads
    for (int i = 0; i < std::thread::hardware_concurrency(); ++i) {
        threads.emplace_back(&AsyncLogger::loggingThread, this);
    }
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

void AsyncLogger::log(const std::string& message, LogType type) {
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
        queueCondition.wait(lock, [this] { return !logQueue.empty() || stopLogging; });
        if (stopLogging && logQueue.empty()) {
            // Exit the thread if logging is stopped and the queue is empty
            break;
        }
        logMessage = logQueue.front();
        logQueue.pop();


        std::cout << logMessage.first << std::endl;

    }
}

//void AsyncLogger::log(const std::string& message, LogType type) {


//    AsyncLogger::printType(type);
//    std::cout << message << std::endl;
//}

//void AsyncLogger::log(int value, LogType type) {

//    AsyncLogger::printType(type);

//    std::cout << value << std::endl;

//}

//void AsyncLogger::log(const std::vector<int>& values, LogType type) {
//  
//    AsyncLogger::printType(type);

//    for (int value : values) {
//        std::cout << " " << value;
//    }
//    std::cout << std::endl;
//}

