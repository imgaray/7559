#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <time.h>
#include "LockFile.h"

using namespace std;

#define NIVEL_GLOBAL LOG_DEBUG

#ifndef LOG_LEVEL
#define LOG_LEVEL

#define LOG_INFO 1
#define LOG_WARN 2
#define LOG_ERROR 4
#define LOG_FATAL 8
#define LOG_DEBUG 15

#endif /*LOG_LEVEL*/

class Logger {

private:
	Logger();
	static ofstream archivoLog;
	// nivel de log con el que logeamos. Por defecto, DEBUG.
	static int nivelDeLog;
	static void log(const string& tag, const string& msg, int level);
	static LockFile lock;
	
public:
	static void fatal(const string&, const string&);
	static void error(const string&, const string&);
	static void warn(const string&, const string&);
	static void debug(const string&, const string&);
	static void info(const string&, const string&);
	
	static void setLogLevel(int);
};

#endif /* LOGGER_H_ */
