#ifndef _PROCESO_H
#define _PROCESO_H


#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <string>
class Process {
	public:
		Process(std::string file, int a);
		Process(const Process& proc);
		Process(std::string file);
		Process(char* file);
		pid_t getId();
		int getExitStatus();
		void wait();
		void killProcess();
		bool isRunning();
		virtual ~Process();
		
	private:
		void startProcess();
		pid_t id;
		int exitStatus;
		std::string file;
};

#endif
