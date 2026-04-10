#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>
#include <ctime>

enum class LogLevel { INFO, WARNING, ERROR, FATAL };

class Logger {
public:
  static Logger& getInstance() {
    static Logger instance;
    return instance;
  }
  void log(LogLevel level, const std::string& file, int line, const std::string& message) {
    std::cout << "[" << getCurrentTime() << "] "
              << "[" << levelToString(level) << "] "
              << "[" << file << ":" << line << "] "
              << message << std::endl;
  }

private:
  Logger() = default;

  std::string levelToString(LogLevel level) {
    switch (level) {
      case LogLevel::INFO:    return "INFO";
      case LogLevel::WARNING: return "WARN";
      case LogLevel::ERROR:   return "ERROR";
      case LogLevel::FATAL:   return "FATAL";
      default:                return "UNKNOWN";
    }
  }
  std::string getCurrentTime() {
    time_t now = time(0);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return buf;
  }
};

#define LOG_INFO(msg)  Logger::getInstance().log(LogLevel::INFO, __FILE__, __LINE__, msg)
#define LOG_WARN(msg)  Logger::getInstance().log(LogLevel::WARNING, __FILE__, __LINE__, msg)
#define LOG_ERROR(msg) Logger::getInstance().log(LogLevel::ERROR, __FILE__, __LINE__, msg)
#define LOG_FATAL(msg) Logger::getInstance().log(LogLevel::FATAL, __FILE__, __LINE__, msg)

#endif  // LOGGER_HPP