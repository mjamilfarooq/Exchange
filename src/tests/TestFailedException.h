/*
 * TestFailedException.h
 *
 *  Created on: 27/10/2018
 *      Author: jamil
 */

#ifndef TESTS_TESTFAILEDEXCEPTION_H_
#define TESTS_TESTFAILEDEXCEPTION_H_

#include <string>

using namespace std;

class TestFailedException: public exception {
public:
	TestFailedException(string file_name, uint32_t lineno, string function_name, string message)
	{
		this->message = "Test Failed: (" + file_name + "," + function_name + "," + to_string(lineno) + "," + message + ")";
	}

	virtual const char * what() const noexcept {
		return message.c_str();
	}

private:
	string message;
};

#define THROW_TEST_FAILED_EXCEPTION(message) \
	throw TestFailedException(__FILE__, __LINE__, __function_name__, message)


#endif /* TESTS_TESTFAILEDEXCEPTION_H_ */
