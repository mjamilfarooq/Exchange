/*
 * AllTests.cpp
 *
 *  Created on: 30/10/2018
 *      Author: jamil
 */




#include "OrderExchangeTests.h"
#include "OrderExecutionTests.h"
#include "OrderQueueTest.h"
#include "OrderTest.h"

void run_all_tests()
{
	OrderTest::test_order_construction();
	OrderTest::test_order_iostream();

	OrderQueueTest::test_long_order_queue();
	OrderQueueTest::test_short_order_queue();
	OrderQueueTest::test_long_all_same_price();
	OrderQueueTest::test_short_all_same_price();

	OrderExecutionTests::test_match_buy_order_first();
	OrderExecutionTests::test_match_sell_order_first();


	OrderExchangeTests::test_order_exchange();
	OrderExchangeTests::test_exchange_same_buyer();
}
