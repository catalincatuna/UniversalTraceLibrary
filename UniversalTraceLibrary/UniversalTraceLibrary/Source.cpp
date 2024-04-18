#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <list>
#include <thread>
#include "ConsoleLogger.h"
#include "FileLogger.h"
#include "AsyncLogger.h"


//#include <openssl/evp.h>
//#include <openssl/rand.h>


int main() {


    ConsoleLogger consoleLogger;

    FileLogger fileLogger("log.txt");

    AsyncLogger asyncConsoleLogger(&consoleLogger);
    AsyncLogger asyncFileLogger(&fileLogger);


    for (auto i = 0; i < 10; i++) {
    asyncConsoleLogger.asyncLog("this is a message");
    asyncConsoleLogger.asyncLog("this is a message 2");

    }
  
    for (auto i = 0; i < 10; i++) {
        asyncFileLogger.asyncLog("this is a message");
        asyncFileLogger.asyncLog("this is a message 2");
    }
    // Add more log messages as needed


    for (auto i = 0; i < 1000; i++) {
        std::cout << "main thread:" << i;
    }


    return 1;
}