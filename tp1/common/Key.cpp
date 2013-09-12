#include "Key.h"

#include <cstdlib>
#include <sys/stat.h>
#include <fcntl.h>


namespace Utilities {

	Key::Key(std::string file_name, char key) {
		buildKey(file_name.c_str(), key);
	}
	
	Key::Key(char* file_name, char key) {
		buildKey(file_name, key);
	}
	
	key_t Key::getKey() {
		return key;
	}
	
	void buildKey(char* filename, char key) {
		key = ftok(filename, key);
		
	}
	
	Key::~Key() {
	
	}
};
