/*
 * ILogger.h
 *
 *  Created on: 26/10/2018
 *      Author: jamil
 */

#ifndef LOGGER_ILOGGER_H_
#define LOGGER_ILOGGER_H_

#include <string>
#include <stdlib.h>

#include "../utils/utility_functions.h"

enum SeverityLevel {
	TRACE,
	DEBUG,
	INFO,
	WARN,
	ERROR,
	FATAL
};


//helper macros for verbose log
#define MESSAGE_FORMAT(severity, msg) \
	"["+current_time()+"] ("+severity+") " \
	+" "+__FUNCTION__+"@"+__FILE__+"("+to_string(__LINE__)+"): "+msg

#define TRACE(logger, msg) logger->trace(MESSAGE_FORMAT("TRACE", msg))
#define DEBUG(logger, msg) logger->debug(MESSAGE_FORMAT("DEBUG", msg))
#define INFO(logger, msg) logger->info(MESSAGE_FORMAT("INFO", msg))
#define WARN(logger, msg) logger->warn(MESSAGE_FORMAT("WARN", msg))
#define ERROR(logger, msg) logger->error(MESSAGE_FORMAT("ERROR", msg))
#define FATAL(logger, msg) logger->fatal(MESSAGE_FORMAT("FATAL", msg))



class ILogger
{
public:

	ILogger()
		:severity_level(TRACE)
	{}

	ILogger(SeverityLevel level)
		:severity_level(level)
	{}

	virtual void trace(std::string msg) = 0;
	virtual void debug(std::string msg) = 0;
	virtual void info(std::string msg) = 0;
	virtual void warn(std::string msg) = 0;
	virtual void error(std::string msg) = 0;
	virtual void fatal(std::string msg) = 0;


	virtual ~ILogger() {};

protected:
	SeverityLevel severity_level;
};


#endif /* LOGGER_ILOGGER_H_ */
