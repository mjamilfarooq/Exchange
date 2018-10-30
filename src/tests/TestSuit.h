/*
 * TestSuit.h
 *
 *  Created on: 27/10/2018
 *      Author: jamil
 */

#ifndef TESTS_TESTSUIT_H_
#define TESTS_TESTSUIT_H_

#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

#include "TestFailedException.h"

using namespace std;

#define TEST_EQUAL(actual, expected, message) \
	[&](){ \
		if ( actual != expected ) { \
			cout<<"actual: "<<actual<<" expected: "<<expected<<endl; \
			THROW_TEST_FAILED_EXCEPTION(message); \
		} \
	}();

#define TEST_INEQUAL(actual, expected, message) \
	[&](){ \
		if ( actual == expected ) \
			THROW_TEST_FAILED_EXCEPTION(message); \
	}();

#define TEST_CASE_BEGIN(function_name) \
	static void function_name() { \
		auto __function_name__ = __FUNCTION__; \
		try \
		{

#define TEST_CASE_END \
		} \
		catch(exception &ex) \
		{ \
			cerr<<ex.what()<<endl; \
		} \
	}

#define TEST_SUIT(test_suit_name) \
		class test_suit_name { \
		public:


#define TEST_SUIT_END };

class TestRegistry {
public:
	static void registerTestCase(function<void()> func)
	{
		function_list.push_back(func);
	}

	static void execute_all() {
		for_each(function_list.begin(),
				function_list.end(),
				[](function<void()> func){
			func();
		});
	}
private:
	static vector<function<void()>> function_list;
};

#define TEST_SUIT_INIT \
		vector<function<void()>> TestRegistry::function_list;

#endif /* TESTS_TESTSUIT_H_ */
