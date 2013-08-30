#ifndef _PROCESO_H
#define _PROCESO_H


#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <string>

namespace Utilities {
	class Process {
		public:
			Process(std::string file);
			Process(char* file);
			pid_t getId();
			int getExitStatus();
			void start();
			void wait();
			void killProcess();
			bool isRunning();
			virtual ~Process();
		private:
			pid_t id;
			int exitStatus;
			std::string file;
	};
}

#endif
