#include "Key.h"

#include <cstdlib>
#include <sys/stat.h>
#include <fcntl.h>


namespace Utilities {
	
	Key::Key() {
		std::string name = std::string("token") + std::string(rand());
		int fd = open(name.c_str(), O_CREAT | O_RDWR, S_IRWXU);
		close(fd);
		buildKey(name.c_str());
	}
	
	Key::Key(std::string file_name) {
		buildKey(file_name.c_str());
	}
	
	key::key(char* file_name) {
		buildKey(file_name);
	}
	
	key_t Key::getKey() {
		return key;
	}
	
	void buildKey(char* filename) {
		key = ftok(filename, rand());
	}
	
	Key::~Key() {
	
	}
};
