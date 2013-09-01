#ifndef __KEY_H
#define __KEY_H

#include <sys/types.h>

namespace Utilities {
	class Key {
		public:
			Key();
			Key(std::string file_name);
			Key(char* file_name);
			key_t getKey();
			virtual ~Key();
		private:
			void buildKey(char* filename);
			std::string filename;
			key_t key;
	};
};
#endif
