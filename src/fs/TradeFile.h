/*
 * TradeFile.h
 *
 *  Created on: 29/10/2018
 *      Author: jamil
 */

#ifndef FS_TRADEFILE_H_
#define FS_TRADEFILE_H_

#include <iostream>
#include <fstream>

#include "../trade/AbstractTradeConsole.h"
#include "../logger/ILogger.h"

class TradeFile: public AbstractTradeConsole {
public:
	TradeFile(ILogger*, std::string);
	void update(Trade) override;
	~TradeFile();
private:
	ILogger* logger;
	std::ofstream tradeFile;
};

#endif /* FS_TRADEFILE_H_ */
