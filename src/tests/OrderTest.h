/*
 * OrderTest.cpp
 *
 *  Created on: 26/10/2018
 *      Author: jamil
 */



#include "TestSuit.h"
#include "../order/Order.h"
#include <string>
#include <sstream>



TEST_SUIT(OrderTest)
	TEST_CASE_BEGIN(test_order_construction)

		Order order1("jimmy", "AUDUSD", 456, 45.5);
		Order order2("jimmy", "AUDUSD", "456", "45.5");
		Order order3("jimmy", "AUDUSD", "-456", "45.5");

		TEST_EQUAL(order1, order2, "simple construction test")
		TEST_INEQUAL(order1, order3, "simple construction with negative quantity")

	TEST_CASE_END


	TEST_CASE_BEGIN(test_order_iostream)
		Order order1("jimmy", "AUDUSD", 456, 45.5);
		Order order2("jimmy", "AUDUSD", "-456", "45.5");
		Order order3("jimmy", "AUDUSD", "456", "45.5");
		Order order4;

		stringstream strstream;

		{
			strstream << order1;	//out stream of order
			string str;
			strstream >> str;

			TEST_EQUAL(str, "jimmy:AUDUSD:456:45.5", "i/o stream for long order");
		}


		{
			strstream << order2;	//short order
			string str;
			strstream >> str;

			TEST_EQUAL(str, "jimmy:AUDUSD:-456:45.5", "i/o stream for short order");
		}

		//empty order
		{
			strstream << order4;	//empty order
			string str;
			strstream >> str;

			TEST_EQUAL(str, "::0:0", "streaming of empty order");
		}


	TEST_CASE_END
TEST_SUIT_END
