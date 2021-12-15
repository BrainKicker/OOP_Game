#ifndef GAME_RENDERWINDOW_H
#define GAME_RENDERWINDOW_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "../../../geometry/geo.h"

class RenderWindow : public sf::RenderWindow {

    bool m_fullscreen;
    geo::i_point m_prev_size;
    sf::String m_name;

public:

    RenderWindow(int width, int height, const sf::String& name, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());

    bool isFullscreen();
    void setFullscreen(bool fullscreen);
    void switchFullscreen();
};

#endif //GAME_RENDERWINDOW_H