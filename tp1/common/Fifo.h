#ifndef __FIFO_H
#define __FIFO_H

#include <string>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

namespace Utilities {
	class Fifo {
		public:
			Fifo(std::string file);
			Fifo(const char* file);
			virtual ~Fifo();
			void close();
			void delete();
			void push(void* data, unsigned size);
			void* pull(unsigned size);
		private:
			void buildFifo(const char* file_name);
			int fd;
			std::string name;
			
	};
};

#endif
