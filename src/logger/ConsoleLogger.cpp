/*
 * ConsoleLogger.cpp
 *
 *  Created on: 26/10/2018
 *      Author: jamil
 */

#include "ConsoleLogger.h"
using namespace std;

ConsoleLogger* ConsoleLogger::logger = nullptr;
mutex ConsoleLogger::mtx;

ConsoleLogger* ConsoleLogger::getLogger(SeverityLevel severity)
{
	lock_guard<mutex> lock(mtx);

	if (logger == nullptr)
	{
		logger = new ConsoleLogger(severity);
		return logger;
	}
	else return logger;
}

ConsoleLogger::ConsoleLogger(SeverityLevel severity):
		ILogger(severity) {
}

ConsoleLogger::~ConsoleLogger() {
	// TODO Auto-generated destructor stub
}

void ConsoleLogger::message(string msg)
{
	cout<<msg<<endl;
}

void ConsoleLogger::trace(string msg)
{
	if (severity_level<=SeverityLevel::TRACE)
		message(msg);
}

void ConsoleLogger::debug(string msg)
{
	if (severity_level<=SeverityLevel::DEBUG)
		message(msg);
}

void ConsoleLogger::info(string msg)
{
	if (severity_level<=SeverityLevel::INFO)
		message(msg);
}

void ConsoleLogger::warn(string msg)
{
	if (severity_level<=SeverityLevel::WARN)
		message(msg);
}

void ConsoleLogger::error(string msg)
{
	if (severity_level<=SeverityLevel::ERROR)
		cerr<<msg;
}

void ConsoleLogger::fatal(string msg)
{
	if (severity_level<=SeverityLevel::FATAL)
		cerr<<msg;
}




