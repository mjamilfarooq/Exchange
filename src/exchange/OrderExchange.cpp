/*
 * OrderExchange.cpp
 *
 *  Created on: 27/10/2018
 *      Author: jamil
 */

#include "OrderExchange.h"

using namespace std;

OrderExchange::OrderExchange(ILogger *logger):
	logger(logger) {
	TRACE(logger, "Initializing order Exchange");

}

void OrderExchange::connect(shared_ptr<AbstractOrderPublisher>& publisher) {
	TRACE(logger, "adding publisher");
	if (publisher!=nullptr) {
		order_publishers.push_back(publisher);
		publisher->subscribe(this);
		INFO(logger, "publisher registered!!");
	}
	else {
		WARN(logger, "Invalid publisher");
	}
}

void OrderExchange::connect(shared_ptr<AbstractTradeConsole>& tradeConsole) {
	TRACE(logger, "connecting to trade console!!");
	this->tradeConsole = tradeConsole;
}

void OrderExchange::update(Order order)
{
	TRACE(logger, "updating instruments position and matching for trades");
	auto trades = matchAndTrade(order);
	for (auto trade : trades)
	{
		tradeConsole->update(trade);
	}
}

Trades OrderExchange::matchAndTrade(Order order)
{
	Trades trades;
	TRACE(logger, "new order update "+ order.to_string());

	mtx.lock();
	auto isexist = instrumentMap.find(order.getInstrument());
	mtx.unlock();

	if (isexist == instrumentMap.end())
	{
		TRACE(logger, "new entry for instrument");
		mtx.lock();
		auto entry = instrumentMap.emplace(order.getInstrument(), logger);
		mtx.unlock();
		if (!entry.second)
		{
			FATAL(logger, "Can't create Instrument ledger");
			throw runtime_error("Can't create Instrument ledger");
		}

		TRACE(logger, "entry agaist new instrument is registered!!");
		trades = entry.first->second.update(order);
	}
	else
	{
		TRACE(logger, "symbol is already registered...updating instrument ledger");
		trades = isexist->second.update(order);
	}

	TRACE(logger, "new order updated!!");
	return trades;
}

void OrderExchange::run() {
	INFO(logger, "Exchange is running");
}

void OrderExchange::exit() {
	INFO(logger, "Exchange exiting!!");
	for_each(order_publishers.begin(), order_publishers.end(),
			[this](decltype(order_publishers)::value_type publisher){
		if(publisher!=nullptr)
			publisher->unsubscribe(this);
	});
}


OrderExchange::~OrderExchange() {
	TRACE(logger, "OrderExchange destructing!!");
}

