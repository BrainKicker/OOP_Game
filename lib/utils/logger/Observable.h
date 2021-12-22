#ifndef GAME_OBSERVABLE_H
#define GAME_OBSERVABLE_H

#include <iostream>
#include <memory>

#include "Logger.h"

class Observable {

protected:

    std::shared_ptr<Logger> m_logger;

    virtual void print(std::ostream& out) const = 0;

    void notify() const;

public:

    virtual ~Observable() = default;

    std::shared_ptr<Logger>& getLogger();
    const std::shared_ptr<Logger>& getLogger() const;

    void setLogger(Logger* logger);
    void setLogger(std::shared_ptr<Logger> logger);

    void addLogger(Logger* logger);
    void addLogger(std::shared_ptr<Logger> logger);

    friend std::ostream& operator<<(std::ostream& out, const Observable& observable);
};

#endif //GAME_OBSERVABLE_H