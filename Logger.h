/*
	Логирование всех действий игры в консоль и с возможностью записи в файл сохарняемый в ./log/~
	Логирование имеет 2 уровня: Debug & Error, где Error важно и всегда красным принтом, дебаг - обычная инфа о программе и её работе
	Логирование включается и отключается conf::LOG_ENABLED переменной в системных настройках
	Логирование внутри игры имеет собственную консоль с UI, который пишется на ImGui
	Логирование сохраняет последние 8128 символов в консоли
	Логирование вызывается через LOGGER_API.метод
	Логирование = синглтоновый паттерн
*/

#ifndef LOGGER_HPP
#define LOGGER_HPP

#ifndef LOGGER_API
#define LOGGER_API				Logger::getInstance()
#endif

class Logger;

#include "System.h"

class LoggerDestroyer
{
private:
	Logger* instance;
public:
	~LoggerDestroyer();
	void initialize(Logger* instance);
};

class Logger
{
private:
	static Logger* instance;
	static LoggerDestroyer destroyer;

protected:
	Logger() {}
	Logger(const Logger&);
	Logger& operator=(Logger&);
	~Logger() {}
	friend class LoggerDestroyer;

public:
	static Logger& getInstance();
	/* Запись в файл, для пользователя отключена */
	void writeToFile();
	/* Уведомление во внутриигровую консоль */
	void print(LogLevel level, CString vars...);
};

#endif // !LOGGER_HPP