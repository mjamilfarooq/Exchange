/*
 * ConsoleClient.cpp.
 *
 *  Created on: 28/10/2018
 *      Author: jamil
 */

#include "OrderConsole.h"

OrderConsole::OrderConsole(ILogger *logger):
	logger(logger) {
	TRACE(logger, "Initialization of Order Console");

	ft = async(std::launch::async, &OrderConsole::run, this);
}

void OrderConsole::run() {
	TRACE(logger, "Start capturing orders from console");
	while(true) {
		Order order;
		try
		{
			cin>>order;
		}
		catch(exception &ex)
		{
			TRACE(logger, ex.what());
			continue;
		}
		TRACE(logger, "new order " + order.to_string());
		if (order.isValid())
		{
			DEBUG(logger, "new order is valid " + order.to_string());
			publish(order);
		}
		else WARN(logger, "new order is invalid " + order.to_string());
	}
	TRACE(logger, "End Consle orders capturing");
}

OrderConsole::~OrderConsole() {
	TRACE(logger, "Exiting Order Console");
}

