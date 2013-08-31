#ifndef _SHAREDMEMORY_H
#define _SHAREDMEMORY_H

#include <cstdlib>

enum PERMISSIONS {
	READ, WRITE, BOTH
};

class SharedMemory {
public:
	SharedMemory(unsigned tam, PERMISSIONS permissions);
	virtual ~SharedMemory();
private:
	void* memory;
	unsigned size;
};

#endif

