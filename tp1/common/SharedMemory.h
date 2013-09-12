#ifndef __SHAREDMEMORY_H
#define __SHAREDMEMORY_H

#include <string>

namespace Utilities {
	template <class T>
	class SharedMemory {
		public:
			
			SharedMemory(std::string& filename, char asoc);
			
			virtual ~SharedMemory();
			
			void put(T& elem);

			T& get();
			
		private:
			T* repr;
			int id;
	};

};

#endif
