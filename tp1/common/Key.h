#ifndef __KEY_H
#define __KEY_H

#include <sys/types.h>

namespace Utilities {
	class Key {
		public:
			Key(std::string file_name, char id);
			Key(char* file_name, char id);
			key_t getKey();
			virtual ~Key();
		private:
			void buildKey(char* filename, char key);
			std::string filename;
			key_t key;
	};
};
#endif
