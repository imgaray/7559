#include "Process.h"

namespace Utilities {

	Process::Process(std::string file): id(0), exitStatus(0), file(file) {

	}

	Process::Process(char* file): id(0), exitStatus(0), file(std::string(file)) {

	}

	bool Process::isRunning() {
		return kill(id, 0) == 0;
	}

	pid_t Process::getId() {
		if (!isRunning()) throw("process not running");
		return id;
	}

	int Process::getExitStatus() {
		if (!isRunning()) throw("process not running");
		return exitStatus;
	}

	void Process::start() {
		if (isRunning()) throw("process already running");
		id = fork();
		if (id == 0) {
			execl(file.c_str(), file.c_str(), NULL);
		}
	}

	void Process::killProcess() {
		if (!isRunning()) throw("process not running");
		kill(id, SIGKILL);
		id = 0;
		exitStatus = -1;
	}	

	Process::~Process() {
		if (isRunning())
			id = waitpid(id, &exitStatus, 0);
	}

};
