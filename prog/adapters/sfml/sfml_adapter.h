#ifndef GAME_SFML_ADAPTER_H
#define GAME_SFML_ADAPTER_H

#include <memory>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "../../field/field.h"
#include "window/RenderWindow.h"

class sfml_adapter {

public:

    using field_s_ptr = std::shared_ptr<field>;

private:

    inline static const int s_min_border_width = 5;
    inline static const int s_max_border_width = 30;
    inline static const float s_border_ratio = 0.05;
    inline static const sf::Color s_border_color = sf::Color( 17, 37, 26);

    inline static sf::Texture wall {};
    inline static sf::Texture grass {};
    inline static sf::Texture player {};
    inline static sf::Texture zombie {};
    inline static sf::Texture skeleton {};
    inline static sf::Texture trapdoor {};
    inline static sf::Texture protein {};
    inline static sf::Texture apple {};
    inline static sf::Texture golden_apple {};
    inline static sf::Texture knife {};

    static void __attribute__((constructor)) load_images();

    inline static const char* const window_name = "Game";

    inline static const int
            default_window_width = 900,
            default_window_height = 900;

    int m_window_width, m_window_height;

    int m_field_id;
    field_s_ptr m_field_p;

    RenderWindow* m_window;

    void create_field();

    void create_window();
    void delete_window();

    void handle_event(const sf::Event& event);

    void clear();
    void draw();
    void display();
    void refresh();

    sf::Color health_color(float percentage);

public:

    sfml_adapter(
            int field_id,
            int window_width = default_window_width,
            int window_height = default_window_height);

    ~sfml_adapter();

    field_s_ptr get_field();
    void set_field(field_s_ptr field_p);

    void start();
};

#endif //GAME_SFML_ADAPTER_H