/*
 * FileOrders.cpp
 *
 *  Created on: 27/10/2018
 *      Author: jamil
 */

#include "OrderFile.h"

OrderFile::OrderFile(ILogger *logger, string file_name):
	logger(logger) {
	TRACE(logger, "Initialization of Order File " + file_name);
	orderFile.open(file_name);
	if (!orderFile.is_open())
	{
		FATAL(logger, "Failed to open file " + file_name);
		throw runtime_error("Failed to open file " + file_name);
	}
	ft = async(std::launch::async, &OrderFile::run, this);
}

void OrderFile::run() {
	TRACE(logger, "Start capturing orders from File");
	while(!orderFile.eof()) {
		Order order;
		try
		{
			orderFile>>order;
		}
		catch(exception &ex)
		{
			TRACE(logger, ex.what());
		}
		TRACE(logger, "new order " + order.to_string());
		if (order.isValid())
		{
			DEBUG(logger, "new order is valid " + order.to_string());
			publish(order);
		}
		else {
			WARN(logger, "new order is invalid " + order.to_string());
		}
	}
	TRACE(logger, "order file ending");
}

OrderFile::~OrderFile() {
	TRACE(logger, "Exiting Order File");
	orderFile.close();
}
