/*
 * FileOrders.h
 *
 *  Created on: 27/10/2018
 *      Author: jamil
 */

#ifndef FS_ORDERFILE_H_
#define FS_ORDERFILE_H_

#include <fstream>
#include <sstream>
#include <future>
#include "../order/AbstractOrderPublisher.h"

#include "../logger/ILogger.h"
#include "../order/AbstractOrderPublisher.h"

class OrderFile: public AbstractOrderPublisher {
public:
	OrderFile(ILogger*, std::string);
	void run() override;
	virtual ~OrderFile();
private:
	ILogger *logger;
	std::future<void> ft;
	std::ifstream orderFile;
};

#endif /* FS_ORDERFILE_H_ */
