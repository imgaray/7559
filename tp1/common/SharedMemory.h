#ifndef _SHAREDMEMORY_H
#define _SHAREDMEMORY_H

#include <cstdlib>
namespace Utilities {
	enum PERMISSIONS {
		READ = 0, WRITE, BOTH
	};


	class SharedMemory {
	public:
		SharedMemory(Key key, unsigned tam, PERMISSIONS permissions);
		SharedMemory(unsigned tam, PERMISSIONS permissions);
		virtual ~SharedMemory();
	
	private:
		Key* key;
		PERMISSIONS permissions;
		void* memory;
		unsigned size;
	};
};
#endif

