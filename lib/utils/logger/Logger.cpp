#include "Logger.h"

#include "Observable.h"

Logger::Logger(Logger::LoggerBase* base) : m_base(base) {}

Logger::Logger(std::shared_ptr<LoggerBase> base) : m_base(base) {}

void Logger::update(const Observable& observable) {
    m_base->update(observable);
}

StreamLogger::StreamLoggerBase::StreamLoggerBase(const std::ostream& out) : m_out(out.rdbuf()) {}

void StreamLogger::StreamLoggerBase::update(const Observable& observable) {
    m_out << observable << std::endl;
}

StreamLogger::StreamLogger(const std::ostream& out) : Logger(new StreamLoggerBase(out)) {}

FileLogger::FileLoggerBase::FileLoggerBase(const char* filename) : m_out(filename) {}

void FileLogger::FileLoggerBase::update(const Observable& observable) {
    m_out << observable << std::endl;
}

FileLogger::FileLogger(const char* filename) : Logger(new FileLoggerBase(filename)) {}

LoggerPool::LoggerPoolBase::LoggerPoolBase(const Vector<std::shared_ptr<Logger>>& loggers) : m_loggers(loggers) {}

void LoggerPool::LoggerPoolBase::update(const Observable& observable) {
    for (auto logger : m_loggers)
        logger->update(observable);
}

LoggerPool::LoggerPool(const Vector<std::shared_ptr<Logger>>& loggers) : Logger(new LoggerPoolBase(loggers)) {}

Vector<std::shared_ptr<Logger>>& LoggerPool::getLoggers() {
    return ((LoggerPoolBase&) *m_base).m_loggers;
}

const Vector<std::shared_ptr<Logger>>& LoggerPool::getLoggers() const {
    return ((LoggerPoolBase&) *m_base).m_loggers;
}

void LoggerPool::addLogger(std::shared_ptr<Logger> logger) {
    ((LoggerPoolBase&) *m_base).m_loggers.add(logger);
}

void LoggerPool::removeLogger(int index) {
    ((LoggerPoolBase&) *m_base).m_loggers.remove(index);
}