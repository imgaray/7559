#include "SharedMemory.h"
#include "Key.h"
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>

namespace Utilities {
	
	SharedMemory::SharedMemory(std::string& filename, char asoc):
	repr(NULL), id(0) {
		Key key(filename, asoc);
		int tmp = shmget(key.getKey(), sizeof(T), 0x644);
		if (tmp == -1)
			throw("SharedMemory error, unable to create page");
		id = tmp;
		void* ptr = shmget(id, NULL, 0x644);
		if (ptr == (void*) -1) throw("SharedMemory error, unable to attach");
		repr = ptr;	
	}
				
	virtual SharedMemory::~SharedMemory() {
		int tmp = shmdt(repr);
		if (tmp == -1)
			std::err << "SharedMemory error, unable to detach" << std::endl;
		if (hasNoMoreRefs()) {
			if (shmclt(id, IPC_RMID, NULL) == -1)
				std::err << "SharedMemory error, unable to delete" << std::endl;
		}
	}
				
	void SharedMemory::put(T& elem) {
		*repr = elem;
	}
				
	T& SharedMemory::get() {
		return *repr;
	}

};
