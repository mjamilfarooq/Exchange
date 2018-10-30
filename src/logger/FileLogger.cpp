/*
 * FileLogger.cpp
 *
 *  Created on: 28/10/2018
 *      Author: jamil
 */

#include "FileLogger.h"

string FileLogger::file_name = DEFAULT_LOG_FILE;
FileLogger* FileLogger::logger = nullptr;
mutex FileLogger::mtx;

FileLogger* FileLogger::getLogger(SeverityLevel severity, string file_name)
{
	lock_guard<mutex> lock(mtx);

	if (logger == nullptr)
	{
		FileLogger::file_name = file_name;
		logger = new FileLogger(severity);
		return logger;
	}
	else return logger;
}

FileLogger::FileLogger(SeverityLevel severity):
		ILogger(severity) {
	logFile.open(file_name);
	if (!logFile.is_open())
	{
		throw runtime_error("Failed to create/open file " + file_name);
	}
}

FileLogger::~FileLogger() {
	logFile.close();
}

void FileLogger::message(string msg)
{
	logFile<<msg<<endl;
}

void FileLogger::trace(string msg)
{
	if (severity_level<=SeverityLevel::TRACE)
		message(msg);
}

void FileLogger::debug(string msg)
{
	if (severity_level<=SeverityLevel::DEBUG)
		message(msg);
}

void FileLogger::info(string msg)
{
	if (severity_level<=SeverityLevel::INFO)
		message(msg);
}

void FileLogger::warn(string msg)
{
	if (severity_level<=SeverityLevel::WARN)
		message(msg);
}

void FileLogger::error(string msg)
{
	if (severity_level<=SeverityLevel::ERROR)
		message(msg);
}

void FileLogger::fatal(string msg)
{
	if (severity_level<=SeverityLevel::FATAL)
		message(msg);
}
