/*
 * InstrumentLedger.cpp
 *
 *  Created on: 29/10/2018
 *      Author: jamil
 */

#include "InstrumentLedger.h"

InstrumentLedger::InstrumentLedger(ILogger* logger):
	logger(logger){
}

InstrumentLedger::InstrumentLedger():
		logger(nullptr) {
}

InstrumentLedger::InstrumentLedger(InstrumentLedger&& ledger):
		logger(ledger.logger),
		longOrderQueue(std::move(ledger.longOrderQueue)),
		shortOrderQueue(std::move(ledger.shortOrderQueue))	{
		ledger.logger = nullptr;
}

//Injection of logger
void InstrumentLedger::setLogger(ILogger* logger) {
		this->logger = logger;
}

vector<Trade> InstrumentLedger::update(Order order) {
	lock_guard<mutex> lock(mtx);
	order.timestamp();
	TRACE(logger, "updating Instrument order ledger");

	vector<Trade> trades;
	if ( order.getQuantity() > 0 )
	{
		TRACE(logger, "order received is buy");


			while (!shortOrderQueue.empty() &&
					order.getLimitPrice()>=shortOrderQueue.top().getLimitPrice())
			{
				auto& sorder = shortOrderQueue.top();
				TRACE(logger, "buy price is >= least sell price");
				TRACE(logger, "trade should take place at sell price");
				auto trade_price = sorder.getLimitPrice();
				auto trade_quantity = order.getQuantity() + sorder.getQuantity();

				if (trade_quantity <= 0) //if current order size is less or equal to short order
				{
					DEBUG(logger, "both order with same size");
					trades.emplace_back(order.getID(),
									sorder.getID(),
									order.getInstrument(),
									order.getQuantity(),
									trade_price);
					order.setQuantity(0);
					if (trade_quantity<0) {
						TRACE(logger, "modify top order to new quantity " + to_string(trade_quantity));
						sorder.setQuantity(trade_quantity);

					}
					else shortOrderQueue.pop();	//delete top most sell order as executed
					break;
				}
				else if ( trade_quantity > 0 )  //if current order size is greater
				{
					DEBUG(logger, "current buy order size is greater than top sell order");
					trades.emplace_back(order.getID(),
									sorder.getID(),
									order.getInstrument(),
									abs(sorder.getQuantity()),
									trade_price);
					TRACE(logger, "modify coming order to new quantity " + to_string(trade_quantity));
					order.setQuantity(trade_quantity);
					shortOrderQueue.pop();
				}
			}

			if (order.getQuantity()) //if order is executed partially only enter
			{
				DEBUG(logger, "update partial/complete order is entered into ledger");
				longOrderQueue.push(order);
			}

	}

	//order is short
	else
	{
		while (!longOrderQueue.empty() &&
				order.getLimitPrice()<=longOrderQueue.top().getLimitPrice())
		{
			auto& lorder = longOrderQueue.top();
			TRACE(logger, "sell price is <= least buy price");
			TRACE(logger, "trade should take place at buy price");
			auto trade_price = lorder.getLimitPrice();
			auto trade_quantity = order.getQuantity() + lorder.getQuantity();

			if (trade_quantity >= 0) //complete execution of current order
			{
				DEBUG(logger, "sell order quantity is smaller than buy at queue ");
				trades.emplace_back(lorder.getID(),
								order.getID(),
								order.getInstrument(),
								abs(order.getQuantity()),
								trade_price);
				order.setQuantity(0);
				if (trade_quantity>0)
				{
					TRACE(logger, "modify top order to partial quantity");
					longOrderQueue.top().setQuantity(trade_quantity);
				}
				else longOrderQueue.pop();	//delete top most sell order as executed
				break;
			}
			else if ( trade_quantity < 0 )  //if current order size is greater
			{
				DEBUG(logger, "current sell order size is greater than top buy order");
				trades.emplace_back(lorder.getID(),
								order.getID(),
								order.getInstrument(),
								lorder.getQuantity(),
								trade_price);
				order.setQuantity(trade_quantity);
				longOrderQueue.pop();
			}
		}

		if (order.getQuantity()) //if order is executed partially only enter
		{
			DEBUG(logger, "update partial/complete order is entered into ledger");
			shortOrderQueue.push(order);
		}
	}

	return trades;
}

InstrumentLedger::~InstrumentLedger() {
}

