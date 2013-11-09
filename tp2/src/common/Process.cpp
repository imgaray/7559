#include "Process.h"
#include "Utilitario.h"
#include <iostream>

Process::Process(std::string file): id(0), exitStatus(0), file(file) {
	startProcess();
}

Process::Process(char* file): id(0), exitStatus(0), file(std::string(file)) {
	startProcess();
}

Process::Process(const Process& proc): id(0), exitStatus(0), file(proc.file) {
	startProcess();
}

Process::Process(std::string file, int arg): id(0), exitStatus(0), file(file) {
	int tmpid = fork();
	Utilitario u;
	char* argumentos[] = {(char*) file.c_str(), (char*)u.convertirAString(arg).c_str(), (char*)NULL};
	if (tmpid == 0) {
		int ret = execv(file.c_str(), argumentos);
		if (ret == -1) throw("process error, could not replace process image");
	} else if(tmpid > 0) {
		id = tmpid;
	} else {
		throw("process error, could not fork child process");
	}
}
bool Process::isRunning() {
	return kill(id, 0) == 0;
}

pid_t Process::getId() {
	if (!isRunning()) throw("process not running");
	return id;
}

int Process::getExitStatus() {
	if (isRunning()) throw("process running");
	return exitStatus;
}

void Process::wait() {
	if (isRunning()) {
		if (waitpid(id, &exitStatus, 0) == -1) {
			throw("process error, could not wait for child process");
		}
	} else throw("process error, process not running");
}

void Process::killProcess() {
	if (!isRunning()) throw("process not running");
	if (kill(id, SIGKILL) == -1) throw("process error, could not kill process");
	id = 0;
	exitStatus = -1;
}	

void Process::startProcess() {
	int tmpid = fork();
	if (tmpid == 0) {
		int ret = execl(file.c_str(), file.c_str(), NULL);
		if (ret == -1) throw("process error, could not replace process image");
	} else if(tmpid > 0) {
		id = tmpid;
	} else {
		throw("process error, could not fork child process");
	}
}

Process::~Process() {
	if (isRunning())
		this->wait();
}
