/*
 * ConsoleClient.h
 *
 *  Created on: 28/10/2018
 *      Author: jamil
 */

#ifndef ORDERCONSOLE_H_
#define ORDERCONSOLE_H_


#include <future>

#include "../logger/ILogger.h"
#include "../order/AbstractOrderPublisher.h"

class OrderConsole: public AbstractOrderPublisher {
public:
	OrderConsole(ILogger*);
	void run() override;
	virtual ~OrderConsole();
private:
	ILogger *logger;
	future<void> ft;
};

#endif /* ORDERCONSOLE_H_ */
