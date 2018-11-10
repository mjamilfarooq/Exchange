/*
 * OrderTest.cpp
 *
 *  Created on: 26/10/2018
 *      Author: jamil
 */



#include "TestSuit.h"
#include "../exchange/OrderExchange.h"
#include "../logger/FileLogger.h"
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>


TEST_SUIT(OrderExchangeTests)
	TEST_CASE_BEGIN(test_order_exchange)

	std::vector<std::string> test_vector = {
					"A:GBPUSD:100:1.66",
					"B:EURUSD:-100:1.11",
					"F:EURUSD:-50:1.1",
					"C:GBPUSD:-10:1.5",
					"C:GBPUSD:-20:1.6",
					"C:GBPUSD:-20:1.7",
					"D:EURUSD:100:1.11",
			};

std::vector<std::string> result_vector = {
					"A:C:GBPUSD:10:1.66",
					"A:C:GBPUSD:20:1.66",
					"D:F:EURUSD:50:1.1",
					"D:B:EURUSD:50:1.11",
			};

			OrderExchange exchange(FileLogger::getLogger());
			std::vector<Trade> trades;
			std::for_each(test_vector.begin(), test_vector.end(), [&](string order_str){
				Order order;
				std::stringstream stream(order_str);
				stream>>order;
				auto temp = exchange.matchAndTrade(order);
				if (temp.size())
				trades.insert(trades.end(), temp.begin(), temp.end());
			});


			std::for_each(result_vector.begin(), result_vector.end(), [&](string trade_str){

				auto actual  = *trades.begin();
				trades.erase(trades.begin());

				Trade expected;
				std::stringstream stream(trade_str);
				stream>>expected;

				TEST_EQUAL(actual, expected, "trade vector failed");

			});


	TEST_CASE_END

	TEST_CASE_BEGIN(test_exchange_same_buyer)

	std::vector<std::string> test_vector = {
					"A:AUDUSD:100:1.47",
					"B:AUDUSD:-50:1.45",
					"A:AUDUSD:-50:1.42",
			};

	std::vector<std::string> result_vector = {
					"A:B:AUDUSD:50:1.470000",
					"A:A:AUDUSD:50:1.470000",
			};

			OrderExchange exchange(FileLogger::getLogger());
			std::vector<Trade> trades;
			std::for_each(test_vector.begin(), test_vector.end(), [&](string order_str){
				Order order;
				std::stringstream stream(order_str);
				stream>>order;
				auto temp = exchange.matchAndTrade(order);
				if (temp.size())
				trades.insert(trades.end(), temp.begin(), temp.end());
			});


			std::for_each(result_vector.begin(), result_vector.end(), [&](string trade_str){

				auto actual  = *trades.begin();
				trades.erase(trades.begin());

				Trade expected;
				std::stringstream stream(trade_str);
				stream>>expected;

				TEST_EQUAL(actual, expected, "trade vector failed");

			});


	TEST_CASE_END

TEST_SUIT_END
