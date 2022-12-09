#include "Logger.h"

Logger* Logger::instance = 0;
LoggerDestroyer Logger::destroyer;

LoggerDestroyer::~LoggerDestroyer()
{
	delete instance;
}

void LoggerDestroyer::initialize(Logger* instance)
{
	this->instance = instance;
}

Logger::Logger(const Logger&)
{
}

Logger& Logger::operator=(Logger&)
{
}

Logger& Logger::getInstance()
{
	if (!instance) {
		instance = new Logger();
		destroyer.initialize(instance);
	}
	return *instance;
}

void Logger::print(LogLevel level, CString vars...)
{
	va_list args;
	va_start(args, vars);
	if (level == LogLevel::Debug) {

	}
	else if (level == LogLevel::Error) {
		
	}
	va_end(args);
}
