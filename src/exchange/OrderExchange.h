/*
 * OrderExchange.h
 *
 *  Created on: 27/10/2018
 *      Author: jamil
 */

#ifndef EXCHANGE_ORDEREXCHANGE_H_
#define EXCHANGE_ORDEREXCHANGE_H_

#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>



#include "../order/IOrderSubscriber.h"
#include "../logger/ILogger.h"
#include "../order/AbstractOrderPublisher.h"
#include "../trade/AbstractTradeConsole.h"
#include "InstrumentLedger.h"

using namespace std;


using InstrumentMap = unordered_map<string, InstrumentLedger>;
using Trades = vector<Trade>;

class OrderExchange:public IOrderSubscriber {

public:
	OrderExchange(ILogger *);
	void connect(shared_ptr<AbstractOrderPublisher>&);
	void connect(shared_ptr<AbstractTradeConsole>&);
	virtual void update(Order) override;
	Trades matchAndTrade(Order);
	void run();
	void exit();
	virtual ~OrderExchange();


private:
	vector<shared_ptr<AbstractOrderPublisher>> order_publishers;
	shared_ptr<AbstractTradeConsole> tradeConsole;
	ILogger* logger;
	InstrumentMap instrumentMap;
};

#endif /* EXCHANGE_ORDEREXCHANGE_H_ */
