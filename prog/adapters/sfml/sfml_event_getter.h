#ifndef GAME_SFML_EVENT_GETTER_H
#define GAME_SFML_EVENT_GETTER_H

#include <SFML/Window/Event.hpp>

#include "../../events/abstract_event_getter.h"
#include "window/RenderWindow.h"

class sfml_event_getter : public abstract_event_getter<sf::Event> {
    RenderWindow* m_window;
public:
    sfml_event_getter(RenderWindow* window);
    RenderWindow* get_window();
    const RenderWindow* get_window() const;
    void set_window(RenderWindow* window);
    sf::Event poll_event() override;
    sf::Event wait_event() override;
};

#endif //GAME_SFML_EVENT_GETTER_H