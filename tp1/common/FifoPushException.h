#ifnded __FIFOPUSHEXCEPTION_H
#define __FIFOPUSHEXCEPTION_H

#include <exception>

namespace Utilities {
	
	class FifoPushException: public exception {
		virtual const char* what() const throw() {
			return "Fifo push exception";
		}
	
	};

};

#endif
