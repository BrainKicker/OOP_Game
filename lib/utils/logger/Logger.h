#ifndef GAME_LOGGER_H
#define GAME_LOGGER_H

#include <iostream>
#include <fstream>
#include <memory>

#include "../../containers/vector/Vector.h"

class Observable; // pre-declaration

class Logger {
protected:

    class LoggerBase {
    public:
        virtual void update(const Observable& observable) = 0;
    };

    std::shared_ptr<LoggerBase> m_base;

    Logger(LoggerBase* base);
    Logger(std::shared_ptr<LoggerBase> base);

public:

    virtual ~Logger() = default;

    void update(const Observable& observable);
};

class StreamLogger : public Logger {
protected:

    class StreamLoggerBase : public LoggerBase {
    public:
        std::ostream m_out;

        StreamLoggerBase(const std::ostream& out);

        void update(const Observable& observable) override;
    };

public:

    StreamLogger(const std::ostream& out);
};

class FileLogger : public Logger {
protected:

    class FileLoggerBase : public LoggerBase {
    public:
        std::ofstream m_out;

        FileLoggerBase(const char* filename);

        void update(const Observable& observable) override;
    };

public:

    FileLogger(const char* filename);
};

class LoggerPool : public Logger {
protected:

    class LoggerPoolBase : public LoggerBase {
    public:
        Vector<std::shared_ptr<Logger>> m_loggers;

        LoggerPoolBase(const Vector<std::shared_ptr<Logger>>& loggers);

        void update(const Observable& observable) override;
    };

public:

    LoggerPool(const Vector<std::shared_ptr<Logger>>& loggers);

    Vector<std::shared_ptr<Logger>>& getLoggers();
    const Vector<std::shared_ptr<Logger>>& getLoggers() const;

    void addLogger(std::shared_ptr<Logger> logger);
    void removeLogger(int index);
};

#endif //GAME_LOGGER_H