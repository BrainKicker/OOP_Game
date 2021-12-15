#include "RenderWindow.h"

RenderWindow::RenderWindow(int width, int height, const sf::String& name, sf::Uint32 style, const sf::ContextSettings& settings)
: sf::RenderWindow(sf::VideoMode(width, height), name, style, settings), m_name(name) {
    if (style == sf::Style::Fullscreen) {
        m_fullscreen = true;
        m_prev_size = { width, height };
    } else {
        m_fullscreen = false;
    }
}

bool RenderWindow::isFullscreen() {
    return m_fullscreen;
}

void RenderWindow::setFullscreen(bool fullscreen) {
    if (m_fullscreen == fullscreen)
        return;
    switchFullscreen();
}

void RenderWindow::switchFullscreen() {
    if (m_fullscreen) {
        create(sf::VideoMode(m_prev_size.first, m_prev_size.second), m_name);
    } else {
        m_prev_size = { getSize().x, getSize().y };
        create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), m_name, sf::Style::Fullscreen);
    }
    m_fullscreen = !m_fullscreen;
}