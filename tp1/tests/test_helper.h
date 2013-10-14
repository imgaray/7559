#ifndef TEST_HELPER_H
#define TEST_HELPER_H

#include <string>

class TestHelper {	
public:
	void eval_test(bool condition, const std::string& message);
	void eval_test(bool condition, const char* message);
	static TestHelper& instance();
	static void cerrar();
private:
	static TestHelper* helper;
	TestHelper();
	virtual ~TestHelper();
};
#endif
