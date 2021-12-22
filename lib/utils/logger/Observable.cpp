#include "Observable.h"

void Observable::notify() const {
    if (m_logger != nullptr)
        m_logger->update(*this);
}

std::shared_ptr<Logger>& Observable::getLogger() {
    return m_logger;
}

const std::shared_ptr<Logger>& Observable::getLogger() const {
    return m_logger;
}

void Observable::setLogger(Logger* logger) {
    setLogger(std::shared_ptr<Logger>(logger));
}

void Observable::setLogger(std::shared_ptr<Logger> logger) {
    m_logger = logger;
}

void Observable::addLogger(Logger* logger) {
    addLogger(std::shared_ptr<Logger>(logger));
}

void Observable::addLogger(std::shared_ptr<Logger> logger) {
    if (m_logger == nullptr)
        m_logger = logger;
    else if (dynamic_cast<LoggerPool*>(&*m_logger))
        ((LoggerPool*) &*m_logger)->addLogger(logger);
    else
        m_logger = std::shared_ptr<LoggerPool>(new LoggerPool({ m_logger, logger }));
}

std::ostream& operator<<(std::ostream& out, const Observable& observable) {
    observable.print(out);
    return out;
}