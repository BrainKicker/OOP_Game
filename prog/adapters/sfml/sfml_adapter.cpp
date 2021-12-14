#include "sfml_adapter.h"

void __attribute__((constructor)) sfml_adapter::load_images() {
    wall.loadFromFile("../assets/images/Wall.png");
    grass.loadFromFile("../assets/images/Grass.png");
    player.loadFromFile("../assets/images/Player.png");
    zombie.loadFromFile("../assets/images/Zombie.png");
    skeleton.loadFromFile("../assets/images/Skeleton.png");
    trapdoor.loadFromFile("../assets/images/Trapdoor.png");
}

void sfml_adapter::create_window() {
    delete_window();
    m_window = new sf::RenderWindow(sf::VideoMode(m_window_width, m_window_height), window_name);
}

void sfml_adapter::delete_window() {
    delete m_window;
    m_window = nullptr;
}

void sfml_adapter::handle_event(const sf::Event& event) {
    switch (event.type) {
        case sf::Event::Closed:
            m_window->close();
            break;
        case sf::Event::Resized:
            m_window_width = m_window->getSize().x;
            m_window_height = m_window->getSize().y;
            ((sf::View*)&m_window->getView())->reset(sf::FloatRect(0, 0, m_window_width, m_window_height));
            break;
        case sf::Event::LostFocus:
        case sf::Event::GainedFocus:
        case sf::Event::TextEntered:
            break;
        case sf::Event::KeyPressed:
            switch (event.key.code) {
                case sf::Keyboard::W:
                case sf::Keyboard::Up:
                    m_field_p->send_sygnal(sygnal::UP);
                    break;
                case sf::Keyboard::S:
                case sf::Keyboard::Down:
                    m_field_p->send_sygnal(sygnal::DOWN);
                    break;
                case sf::Keyboard::A:
                case sf::Keyboard::Left:
                    m_field_p->send_sygnal(sygnal::LEFT);
                    break;
                case sf::Keyboard::D:
                case sf::Keyboard::Right:
                    m_field_p->send_sygnal(sygnal::RIGHT);
                    break;
                case sf::Keyboard::Space:
                case sf::Keyboard::Enter:
                    m_field_p->send_sygnal(sygnal::STEP);
                    break;
                case sf::Keyboard::F11:
                    if (m_fullscreen) {
                        m_window->create(sf::VideoMode(prev_size.first, prev_size.second), window_name);
                    } else {
                        prev_size = { m_window->getSize().x, m_window->getSize().y };
                        m_window->create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), window_name, sf::Style::Fullscreen);
                    }
                    m_fullscreen = !m_fullscreen;
                    break;
                default:
                    break;
            }
            break;
        case sf::Event::KeyReleased:
        case sf::Event::MouseWheelMoved:
        case sf::Event::MouseWheelScrolled:
        case sf::Event::MouseButtonPressed:
        case sf::Event::MouseButtonReleased:
        case sf::Event::MouseMoved:
        case sf::Event::MouseEntered:
        case sf::Event::MouseLeft:
        case sf::Event::JoystickButtonPressed:
        case sf::Event::JoystickButtonReleased:
        case sf::Event::JoystickMoved:
        case sf::Event::JoystickConnected:
        case sf::Event::JoystickDisconnected:
        case sf::Event::TouchBegan:
        case sf::Event::TouchMoved:
        case sf::Event::TouchEnded:
        case sf::Event::SensorChanged:
        case sf::Event::Count:
        default:
            break;
    }
}

void sfml_adapter::clear() {
    m_window->clear();
}

void sfml_adapter::draw() {

    float border_width = (m_window_width + m_window_height) / 2 * s_border_ratio;
    border_width = std::max((float) s_min_border_width, border_width);
    border_width = std::min((float) s_max_border_width, border_width);

    float field_ratio = ((float) m_field_p->width()) / ((float) m_field_p->height());
    float window_ratio = (m_window_width - 2*border_width) / (m_window_height - 2*border_width);

    float image_width, image_height;

    if (field_ratio < window_ratio) {
        image_height = m_window_height - 2*border_width;
        image_width = image_height * field_ratio;
    } else if (field_ratio > window_ratio) {
        image_width = m_window_width - 2*border_width;
        image_height = image_width / field_ratio;
    } else {
        image_width = m_window_width - 2*border_width;
        image_height = m_window_height - 2*border_width;
    }

    sf::RenderTexture texture;
    texture.create(image_width + 2*border_width, image_height + 2*border_width);

    sf::RectangleShape rect;
    rect.setFillColor(s_border_color);
    rect.setPosition(0, 0);
    rect.setSize({ (float) texture.getSize().x, border_width });
    texture.draw(rect);
    rect.setSize({ border_width, (float) texture.getSize().y });
    texture.draw(rect);
    rect.setPosition(texture.getSize().x - border_width, 0);
    rect.setSize({ border_width, (float) texture.getSize().y });
    texture.draw(rect);
    rect.setPosition(0, texture.getSize().y - border_width);
    rect.setSize({ (float) texture.getSize().x, border_width });
    texture.draw(rect);

    float cell_width = image_width / m_field_p->width();
    float cell_height = image_height / m_field_p->height();

    // draw cells
    for (int i = 0; i < m_field_p->width(); ++i) {
        for (int j = 0; j < m_field_p->height(); ++j) {
            sf::Sprite im_cell;
            switch (m_field_p->get_cell_type(i, j)) {
                case cell::GROUND:
                    im_cell.setTexture(grass);
                    break;
                case cell::WALL:
                    im_cell.setTexture(wall);
                    break;
            }
            im_cell.setPosition(border_width + i * cell_width, border_width + j * cell_height);
            im_cell.setScale(cell_width / im_cell.getLocalBounds().width, cell_height / im_cell.getLocalBounds().height);
            texture.draw(im_cell);
        }
    }

    // draw exit
    {
        sf::Sprite im_exit;
        im_exit.setTexture(trapdoor);
        im_exit.setPosition(border_width + m_field_p->get_exit_coords().first * cell_width, border_width + m_field_p->get_exit_coords().second * cell_height);
        im_exit.setScale(cell_width / im_exit.getLocalBounds().width, cell_height / im_exit.getLocalBounds().height);
        texture.draw(im_exit);
    }

    // draw enemies
    for (const enemy* en : m_field_p->get_enemies()) {
        sf::Sprite im_enemy;
        switch (en->type()) {
            case enemy::ZOMBIE:
                im_enemy.setTexture(zombie);
                break;
            case enemy::SKELETON:
                im_enemy.setTexture(skeleton);
                break;
        }
        im_enemy.setPosition(border_width + en->coords().first * cell_width, border_width + en->coords().second * cell_height);
        im_enemy.setScale(cell_width / im_enemy.getLocalBounds().width, cell_height / im_enemy.getLocalBounds().height);
        texture.draw(im_enemy);
    }

    // draw player
    {
        sf::Sprite im_player;
        im_player.setTexture(player);
        im_player.setPosition(border_width + m_field_p->get_player().coords().first * cell_width, border_width + m_field_p->get_player().coords().second * cell_height);
        im_player.setScale(cell_width / im_player.getLocalBounds().width, cell_height / im_player.getLocalBounds().height);
        texture.draw(im_player);
    }

    texture.display();

    sf::Sprite sprite;
    sprite.setTexture(texture.getTexture());

    sprite.setPosition((m_window_width - sprite.getLocalBounds().width) / 2, (m_window_height - sprite.getLocalBounds().height) / 2);

    m_window->draw(sprite);

//    sf::Sprite sprite;
//    sprite.setTexture(wall);
//    sprite.setTextureRect({0, 0, (int) wall.getSize().x, (int) wall.getSize().y});
//    sprite.setScale(m_window_width / sprite.getLocalBounds().width, m_window_height / sprite.getLocalBounds().height);
//    m_window->draw(sprite);
}

void sfml_adapter::display() {
    m_window->display();
}

void sfml_adapter::refresh() {
    clear();
    draw();
    display();
}

sfml_adapter::sfml_adapter(
        sfml_adapter::field_s_ptr field_p,
        int window_width,
        int window_height
) : m_field_p(field_p), m_window_width(window_width), m_window_height(window_height), m_window(nullptr) {}

sfml_adapter::~sfml_adapter() {
    delete_window();
}

sfml_adapter::field_s_ptr sfml_adapter::get_field() {
    return m_field_p;
}

void sfml_adapter::set_field(sfml_adapter::field_s_ptr field_p) {
    m_field_p = field_p;
    refresh();
}

void sfml_adapter::start() {
    create_window();
    sf::Event event;
    while (m_window->isOpen()) {
        while (m_window->waitEvent(event)) {
            handle_event(event);
            refresh();
        }
    }
}