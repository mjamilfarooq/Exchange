//============================================================================
// Name        : Exchange.cpp
// Author      : Muhammad Jamil Farooq
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <thread>
#include <memory>

#include "order/Order.h"
#include "logger/FileLogger.h"
#include "utils/utility_functions.h"
#include "exchange/OrderExchange.h"
#include "console/OrderConsole.h"
#include "fs/OrderFile.h"
#include "fs/TradeFile.h"
#include "errors/messages.h"
#include "tests/AllTests.h"

using namespace std;




int main(int argc, char **argv) {
	auto logger = FileLogger::getLogger(SeverityLevel::TRACE);

#ifdef RUN_TESTS_ONLY
	run_all_tests();
	exit(0);
#endif

	string orderFileName;
	string tradeFileName;

	//processing command line arguments
	if (argc<2||argc>3)
	{
		FATAL(logger, "Invalid Arugments");
		exit(-1);
	}
	else if (argc==2)
	{
		tradeFileName = argv[1];
		INFO(logger, "trade file name " + tradeFileName);
	}
	else
	{
		orderFileName = argv[1];
		tradeFileName = argv[2];
		INFO(logger, "trade file name: " + tradeFileName + " order file name: " + orderFileName);
	}


	OrderExchange exchange(logger);

	//Initializing console order publisher
	shared_ptr<AbstractOrderPublisher> orderConsole = make_shared<OrderConsole>(logger);
	if (orderConsole==nullptr)
	{
		FATAL(logger, ORDER_CONSOLE_INIT_FAILURE);
		throw runtime_error(ORDER_CONSOLE_INIT_FAILURE);
	}

	//Initiating trade console window
	shared_ptr<AbstractTradeConsole> tradeConsole = make_shared<TradeFile>(logger, tradeFileName);
	if (tradeConsole==nullptr)
	{
		FATAL(logger, TRADE_CONSOLE_INIT_FAILURE);
		throw runtime_error(TRADE_CONSOLE_INIT_FAILURE);
	}


	//connecting order and trade console to exchange
	exchange.connect(orderConsole);
	orderConsole->enableNotify();
	exchange.connect(tradeConsole);


	//optionally connect exchange with order file if file is provided in command-line
	if (orderFileName!="")
	{
		shared_ptr<AbstractOrderPublisher> fileOrders(make_shared<OrderFile>(logger, orderFileName));
		if (fileOrders==nullptr)
		{
			FATAL(logger, FILE_ORDER_INIT_FAILURE);
			throw runtime_error(FILE_ORDER_INIT_FAILURE);
		}
		else
		{
			//connecting file orders console with exchange
			exchange.connect(fileOrders);
			fileOrders->enableNotify();
		}
	}

	//busy waiting...
	while(true) {
		this_thread::sleep_for(chrono::seconds(1));
	}

	return 0;
}
