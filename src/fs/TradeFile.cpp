/*
 * TradeFile.cpp
 *
 *  Created on: 29/10/2018
 *      Author: jamil
 */

#include "TradeFile.h"

using namespace std;

TradeFile::TradeFile(ILogger *logger, string file_name):
	logger(logger){

	if(logger==nullptr)
		throw runtime_error("logger not registered!!");

	tradeFile.open(file_name, ios_base::out | ios_base::ate);
	if (!tradeFile.is_open())
	{
		FATAL(logger, "unable to open trade file " + file_name);
		throw runtime_error("unable to open trade file " + file_name);
	}
}

void TradeFile::update(Trade trade)
{
	INFO(logger, "updating trade information on trade file console " + trade.to_string());
	tradeFile<<trade<<endl;
}

TradeFile::~TradeFile() {
}

