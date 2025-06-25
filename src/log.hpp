#pragma once

#include <iostream>
#include <format>

class Log
{
public:
	static void Error(const char* msg) { std::cout << "\033[31m[ ERROR ]: " << msg << "\033[0m" << std::endl; }
	static void Warn(const char* msg) { std::cout << "\033[33m[WARNING]: " << msg << "\033[0m" << std::endl; }
	static void Success(const char* msg) { std::cout << "\033[32m[SUCCESS]: " << msg << "\033[0m" << std::endl; }
	static void Message(const char* msg) { std::cout << "[MESSAGE]: " << msg << std::endl; }

private:
	Log& operator=(const Log&) = delete;
	Log(const Log&) = delete;
	Log() = delete;
	~Log() = delete;
};
