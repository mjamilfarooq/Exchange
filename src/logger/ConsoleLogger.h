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

class ConsoleLogger: public ILogger {
public:
	static ConsoleLogger* getLogger(SeverityLevel severity  = SeverityLevel::TRACE);

	void trace(std::string msg) override;
	void debug(std::string msg) override;
	void info(std::string msg) override;
	void warn(std::string msg) override;
	void error(std::string msg) override;
	void fatal(std::string msg) override;

	virtual ~ConsoleLogger();
private:
	static ConsoleLogger *logger;
	ConsoleLogger(SeverityLevel severity = SeverityLevel::TRACE);
	void message(std::string);
	static std::mutex mtx;
};

#endif /* LOGGER_CONSOLELOGGER_H_ */
