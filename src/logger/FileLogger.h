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

	static FileLogger* getLogger(SeverityLevel severity  = SeverityLevel::TRACE, std::string file_name = DEFAULT_LOG_FILE);

	void trace(std::string msg) override;
	void debug(std::string msg) override;
	void info(std::string msg) override;
	void warn(std::string msg) override;
	void error(std::string msg) override;
	void fatal(std::string msg) override;

	virtual ~FileLogger();

private:
	FileLogger(SeverityLevel severity = SeverityLevel::TRACE);
	static FileLogger *logger;
	void message(std::string);
	static std::mutex mtx;
	static std::string file_name;
	std::ofstream logFile;
};

#endif /* LOGGER_FILELOGGER_H_ */
