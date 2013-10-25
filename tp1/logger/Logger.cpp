#include "Logger.h"
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


Logger* Logger::logger_instance = NULL;

Logger::Logger(): nivelDeLog(LOG_DEBUG) {
	string timeStamp = "output.log";
	struct stat buffer;
	if (stat(timeStamp.c_str(), &buffer)) {
		archivoLog.open( timeStamp.c_str() );
		archivoLog << "  Fecha y  hora\t\t" << " Tipo\t\t" << "Lugar del mensaje\t\t\t" << "Mensaje" << endl ;
	} else {
		archivoLog.open(timeStamp.c_str(), std::ofstream::app);
	}
	lock = new LockFile(timeStamp.c_str());
}

Logger& Logger::instance() {
	if (!logger_instance) {
		logger_instance = new Logger();
	}
	return *logger_instance;
}

void Logger::close() {
	if (logger_instance)
		delete logger_instance;
	logger_instance = NULL;
}

Logger::~Logger() {
	delete lock;
}

void Logger::warn(const string& tag, const string& msg){
	if ((nivelDeLog & LOG_WARN) == 0)
		return;

	log(tag, msg, LOG_WARN);
}

void Logger::error(const string& tag, const string& msg) {
	if ((nivelDeLog & LOG_ERROR) == 0)
		return;

	log(tag, msg, LOG_ERROR);
}

void Logger::debug(const string& tag, const string& msg) {
	if (nivelDeLog != LOG_DEBUG)
		return;
	log(tag, msg, LOG_DEBUG);
}

void Logger::info(const string& tag, const string& msg) {
	if ((nivelDeLog & LOG_INFO) == 0)
		return;	
	
	log(tag, msg, LOG_INFO);
}


void Logger::fatal(const string& tag, const string& msg) {
	if ((nivelDeLog & LOG_FATAL) == 0)
		return;
	log(tag, msg, LOG_FATAL);
}

void Logger::log(const string& tag, const string& msg, int level) {
	lock->tomarLock();
	struct tm *p_local_t;
	time_t t = time(NULL);
	p_local_t = localtime(&t);

	string sNivel("[INFO]\t");
	switch (level) {
	case LOG_FATAL:
		sNivel = "[FATAL]\t";
		break;
	case LOG_ERROR:
		sNivel = "[ERROR]\t";
		break;
	case LOG_WARN:
		sNivel = "[WARN]\t";
		break;
	case LOG_INFO:
		sNivel = "[INFO]\t";
		break;
	case LOG_DEBUG:
		sNivel = "[DEBUG]\t";
		break;
	default:
		break;
	}

	string sep;
	if (tag.size() >= 16)
		sep = "\t";
	else if (tag.size() >= 12)
		sep = "\t\t";
	else if (tag.size() >= 8)
		sep = "\t\t\t";
	else sep = "\t\t\t\t";

	//FORMATO: d-m-yyyy HH:mm:ss objeto mensaje
	archivoLog << "[" << p_local_t->tm_mday << "-" << 1 + p_local_t->tm_mon 
			<< "-" << 1900 + p_local_t->tm_year << " " 
			<< p_local_t->tm_hour << ":" << p_local_t->tm_min 
			<< ":" << p_local_t->tm_sec << "]" << "\t" << sNivel << "\t" << tag << sep << msg
			<< endl;
	archivoLog.flush();
	lock->liberarLock();
}

void Logger::clear() {
	lock->tomarLock();
	string timeStamp = "output.log";
	archivoLog.close();
	archivoLog.open(timeStamp.c_str());
	archivoLog << "  Fecha y  hora\t\t" << " Tipo\t\t" << "Lugar del mensaje\t\t\t" << "Mensaje" << endl ;
	lock->liberarLock();
}

void Logger::setLogLevel(int nivelLog){
	lock->tomarLock();
	nivelDeLog = nivelLog;
	lock->liberarLock();
}
