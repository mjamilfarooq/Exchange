/*
 * ConsoleLogger.h
 *
 *  Created on: 26/10/2018
 *      Author: jamil
 */

#ifndef LOGGER_CONSOLELOGGER_H_
#define LOGGER_CONSOLELOGGER_H_

#include "ILogger.h"
#include <mutex>
#include <iostream>

using namespace std;

class ConsoleLogger: public ILogger {
public:
	static ConsoleLogger* getLogger(SeverityLevel severity  = SeverityLevel::TRACE);

	void trace(string msg) override;
	void debug(string msg) override;
	void info(string msg) override;
	void warn(string msg) override;
	void error(string msg) override;
	void fatal(string msg) override;

	virtual ~ConsoleLogger();
private:
	static ConsoleLogger *logger;
	ConsoleLogger(SeverityLevel severity = SeverityLevel::TRACE);
	void message(string);
	static mutex mtx;
};

#endif /* LOGGER_CONSOLELOGGER_H_ */
