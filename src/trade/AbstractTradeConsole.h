/*
 * AbstractTradeConsole.h
 *
 *  Created on: 29/10/2018
 *      Author: jamil
 */

#ifndef TRADE_ABSTRACTTRADECONSOLE_H_
#define TRADE_ABSTRACTTRADECONSOLE_H_

#include "Trade.h"

class AbstractTradeConsole {
public:
	virtual void update(Trade) = 0;
	virtual ~AbstractTradeConsole() {}
};


#endif /* TRADE_ABSTRACTTRADECONSOLE_H_ */
