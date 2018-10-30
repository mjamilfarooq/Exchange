/*
 * InstrumentLedger.h
 *
 *  Created on: 29/10/2018
 *      Author: jamil
 */

#ifndef EXCHANGE_INSTRUMENTLEDGER_H_
#define EXCHANGE_INSTRUMENTLEDGER_H_

#include <queue>
#include <mutex>



#include "../order/Order.h"
#include "../logger/ILogger.h"
#include "../trade/Trade.h"

using LongOrderQueue = std::priority_queue<Order, std::vector<Order>, std::less_equal<Order>>;
using ShortOrderQueue = std::priority_queue<Order, std::vector<Order>, std::greater_equal<Order>>;


using namespace std;

class InstrumentLedger {
public:
	InstrumentLedger(ILogger *);
	InstrumentLedger();
	InstrumentLedger(InstrumentLedger&& ledger);
	void setLogger(ILogger*);
	vector<Trade> update(Order);
	~InstrumentLedger();
private:
	ILogger* logger;
	LongOrderQueue longOrderQueue;
	ShortOrderQueue shortOrderQueue;
	std::mutex mtx;
};

#endif /* EXCHANGE_INSTRUMENTLEDGER_H_ */
