/*
 * OrderTest.cpp
 *
 *  Created on: 26/10/2018
 *      Author: jamil
 */



#include "TestSuit.h"
#include "../exchange/InstrumentLedger.h"
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

TEST_SUIT(OrderQueueTest)
	TEST_CASE_BEGIN(test_long_order_queue)

		LongOrderQueue longQueue;

		//all long orders for same symbols
		vector<string> test_vector = {
				"A:GBPUSD:100:1.66",
				"B:GBPUSD:100:1.11",
				"C:GBPUSD:50:1.1",
				"D:GBPUSD:10:1.5",
				"E:GBPUSD:20:1.6",
				"F:GBPUSD:20:1.7",
				"G:GBPUSD:100:1.11",
		};

		//expected result of queuing
		vector<string> result_vector = {
				"F:GBPUSD:20:1.7",
				"A:GBPUSD:100:1.66",
				"E:GBPUSD:20:1.6",
				"D:GBPUSD:10:1.5",
				"B:GBPUSD:100:1.11",
				"G:GBPUSD:100:1.11",
				"C:GBPUSD:50:1.1",
		};


		for_each(test_vector.begin(), test_vector.end(), [&](string order_str){
			Order order;
			stringstream stream(order_str);
			stream>>order;
			longQueue.push(order);
		});

		for_each(result_vector.begin(), result_vector.end(), [&](string order_str){
			Order expected;
			stringstream stream(order_str);
			stream>>expected;
			Order actual;
			if ( !longQueue.empty() ) actual = longQueue.top();
			TEST_EQUAL(actual, expected, "long order queue invalid");
			longQueue.pop();
		});


		TEST_EQUAL(longQueue.size(), 0, "long order queue should be empty");

	TEST_CASE_END


	TEST_CASE_BEGIN(test_short_order_queue)

		ShortOrderQueue shortQueue;

		//all long orders for same symbols
		vector<string> test_vector = {
				"A:GBPUSD:-100:1.66",
				"B:GBPUSD:-100:1.11",
				"C:GBPUSD:-50:1.1",
				"D:GBPUSD:-10:1.5",
				"E:GBPUSD:-20:1.6",
				"F:GBPUSD:-20:1.7",
				"G:GBPUSD:-100:1.11",
		};

		//expected result of queuing
		vector<string> result_vector = {
				"C:GBPUSD:-50:1.1",
				"B:GBPUSD:-100:1.11",
				"G:GBPUSD:-100:1.11",
				"D:GBPUSD:-10:1.5",
				"E:GBPUSD:-20:1.6",
				"A:GBPUSD:-100:1.66",
				"F:GBPUSD:-20:1.7",
		};


		for_each(test_vector.begin(), test_vector.end(), [&](string order_str){
			Order order;
			stringstream stream(order_str);
			stream>>order;
			shortQueue.push(order);
		});

		for_each(result_vector.begin(), result_vector.end(), [&](string order_str){
			Order expected;
			stringstream stream(order_str);
			stream>>expected;
			Order actual;
			if ( !shortQueue.empty() ) actual = shortQueue.top();
			TEST_EQUAL(actual, expected, "short order queue invalid");
			shortQueue.pop();
		});


		TEST_EQUAL(shortQueue.size(), 0, "short order queue should be empty");


	TEST_CASE_END

TEST_SUIT_END
