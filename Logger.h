/*
	����������� ���� �������� ���� � ������� � � ������������ ������ � ���� ����������� � ./log/~
	����������� ����� 2 ������: Debug & Error, ��� Error ����� � ������ ������� �������, ����� - ������� ���� � ��������� � � ������
	����������� ���������� � ����������� conf::LOG_ENABLED ���������� � ��������� ����������
	����������� ������ ���� ����� ����������� ������� � UI, ������� ������� �� ImGui
	����������� ��������� ��������� 8128 �������� � �������
	����������� ���������� ����� LOGGER_API.�����
	����������� = ������������ �������
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
	/* ������ � ����, ��� ������������ ��������� */
	void writeToFile();
	/* ����������� �� ������������� ������� */
	void print(LogLevel level, CString vars...);
};

#endif // !LOGGER_HPP