#include "sfml_event_getter.h"

sfml_event_getter::sfml_event_getter(RenderWindow* window) : m_window(window) {}

RenderWindow* sfml_event_getter::get_window() {
    return m_window;
}

const RenderWindow* sfml_event_getter::get_window() const {
    return m_window;
}

void sfml_event_getter::set_window(RenderWindow* window) {
    m_window = window;
}

sf::Event sfml_event_getter::poll_event() {
    sf::Event event;
    if (m_window != nullptr)
        m_window->pollEvent(event);
    return event;
}

sf::Event sfml_event_getter::wait_event() {
    sf::Event event;
    if (m_window != nullptr)
        m_window->waitEvent(event);
    return event;
}