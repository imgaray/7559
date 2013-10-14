#include "test_helper.h"
#include <iostream>

TestHelper* TestHelper::helper = NULL;

TestHelper::TestHelper() {
	
}

TestHelper::~TestHelper() {
}

void TestHelper::eval_test(bool condition, const char* message) {
	std::cout << message << " : " << (condition? "OK" : "FAIL") << std::endl;
}

void TestHelper::eval_test(bool condition, const std::string& message) {
	std::cout << message << " : " << (condition? "OK" : "FAIL") << std::endl;
}

TestHelper& TestHelper::instance() {
	if (!helper)
		helper = new TestHelper();
	return *helper;
}

void TestHelper::cerrar() {
	if (helper)
		delete helper;
	helper = NULL;
}
