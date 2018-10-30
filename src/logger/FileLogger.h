/*
 * FileLogger.h
 *
 *  Created on: 28/10/2018
 *      Author: jamil
 */

#ifndef LOGGER_FILELOGGER_H_
#define LOGGER_FILELOGGER_H_

#include <fstream>
#include <mutex>
#include "ILogger.h"

#define DEFAULT_LOG_FILE "logs/exchange.log"

class FileLogger: public ILogger {
public:

	static FileLogger* getLogger(SeverityLevel severity  = SeverityLevel::TRACE, string file_name = DEFAULT_LOG_FILE);

	void trace(string msg) override;
	void debug(string msg) override;
	void info(string msg) override;
	void warn(string msg) override;
	void error(string msg) override;
	void fatal(string msg) override;

	virtual ~FileLogger();

private:
	FileLogger(SeverityLevel severity = SeverityLevel::TRACE);
	static FileLogger *logger;
	void message(string);
	static mutex mtx;
	static string file_name;
	ofstream logFile;
};

#endif /* LOGGER_FILELOGGER_H_ */
