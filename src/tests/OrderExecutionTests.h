/*
 * OrderTest.cpp
 *
 *  Created on: 26/10/2018
 *      Author: jamil
 */



#include "TestSuit.h"
#include "../exchange/InstrumentLedger.h"
#include "../logger/FileLogger.h"
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

TEST_SUIT(OrderExecutionTests)


	TEST_CASE_BEGIN(test_match_buy_order_first)

	std::vector<std::string> test_vector = {
					"A:GBPUSD:100:1.66",
//					"B:EURUSD:-100:1.11",
//					"F:EURUSD:-50:1.1",
					"C:GBPUSD:-10:1.5",
					"C:GBPUSD:-20:1.6",
					"C:GBPUSD:-20:1.7",
//					"D:EURUSD:100:1.11",
			};

std::vector<std::string> result_vector = {
					"A:C:GBPUSD:10:1.66",
					"A:C:GBPUSD:20:1.66",
//					"D:F:EURUSD:50:1.1",
//					"D:B:EURUSD:50:1.11",
			};

			InstrumentLedger ledger(FileLogger::getLogger());
			std::vector<Trade> trades;
			std::for_each(test_vector.begin(), test_vector.end(), [&](string order_str){
				Order order;
				std::stringstream stream(order_str);
				stream>>order;

//				cout<<order;
				auto temp = ledger.update(order);
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

	TEST_CASE_BEGIN(test_match_sell_order_first)

	std::vector<std::string> test_vector = {
					"B:EURUSD:-100:1.11",
					"F:EURUSD:-50:1.1",
					"D:EURUSD:100:1.11",
		};

	std::vector<std::string> result_vector = {
					"D:F:EURUSD:50:1.1",
					"D:B:EURUSD:50:1.11",
		};

		InstrumentLedger ledger(FileLogger::getLogger());
		std::vector<Trade> trades;
		std::for_each(test_vector.begin(), test_vector.end(), [&](string order_str){
			Order order;
			std::stringstream stream(order_str);
			stream>>order;

//			cout<<order;
			auto temp = ledger.update(order);
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
