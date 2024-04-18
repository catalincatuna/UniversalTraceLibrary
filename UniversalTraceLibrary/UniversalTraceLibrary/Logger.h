
#ifndef Logger_H
#define Logger_H
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <ctime>
#include <iomanip>
#include <sstream>


// Define an enum for log types
enum class LogType {
	INFO,
	WARNING,
	ERROR,
	SENSITIVE
};



class Logger {

public:
	virtual void log(const std::string& message, LogType type = LogType::INFO) = 0;
	virtual ~Logger() {};
	virtual std::string getTimeString();
	virtual void printType(LogType type);

};


#endif