#include "Time.h"
#include <iostream>
#include <ctime>
#include <utility>
#include <unistd.h>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <format>

using namespace std;

const float PI = 3.141592653589793;

Time::Time() = default;

void Time::set_radius(float r) {
    radius = r;
}

void Time::draw_clock() {
    sf ::RenderWindow window(sf::VideoMode(1000, 800), "Clock");
    const sf::Vector2u size = window.getSize();
    center_x = size.x / 2.0;
    center_y = size.y / 2.0;
    window.clear(sf::Color::White);

    // Infinity loop for clock ticking...
    loop(window);
}

void Time::loop(sf::RenderWindow & window) {
    while (window.isOpen()) {
        // If pressed exit...
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update time...
        update_time();

        // Drawing clock parts...
        draw_clock_circle(window);
        draw_clock_numbers(window);
        draw_second_arrow(window);
        draw_minute_arrow(window);
        draw_hour_arrow(window);
        draw_little_dot(window);

        // Updating screen...
        window.display();

        sleep(1);
        window.clear(sf::Color::White);
    }
}

void Time::draw_clock_circle(sf::RenderWindow &window) const{
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::Cyan);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(3);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setPosition(center_x, center_y);

    window.draw(circle);
}

void Time::draw_clock_numbers(sf::RenderWindow & window) const {
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        cout << "Failed to load font!" << endl;
        return;
    }
    sf::Text text;
    text.setFont(font);
    text.setString("X");
    text.setCharacterSize(radius / 4);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0,
                   textRect.top + textRect.height / 2.0);

    // Drawing numbers...
    float curr_angle = PI / 3;

    for (int i = 1; i <= 12; ++i) {
        float curr_x = center_x + radius * 0.85 * cos(curr_angle);
        float curr_y = center_y - radius * 0.85 * sin(curr_angle);
        text.setPosition(curr_x, curr_y);
        text.setString(to_string(i));
        if (i >= 10) {
            text.setPosition(curr_x - textRect.width / 5.0, curr_y);
        }
        window.draw(text);
        curr_angle -= PI / 6;
    }

    string time = format("{:02}:{:02}:{:02}", get_current_hour(), get_current_minute(), get_current_second());
    text.setString(time);
    text.setCharacterSize(radius / 8);
    text.setPosition(center_x - center_x * 3 / 18.0, center_y + radius * 2 / 5.0);

    window.draw(text);
}

void Time::draw_second_arrow(sf::RenderWindow & window) const {
    sf::RectangleShape line(sf::Vector2f(radius * 3 / 5.0, 3));
    line.setFillColor(sf::Color::Black);
    line.setOrigin(0, 0);
    line.setPosition(center_x, center_y);
    line.setFillColor(sf::Color::Red);
    line.setRotation(get_second_arrow_direction());

    window.draw(line);
}

void Time::draw_minute_arrow(sf::RenderWindow & window) const {
    sf::RectangleShape line(sf::Vector2f(radius * 7 / 11.0, 5));
    line.setFillColor(sf::Color::Black);
    line.setOrigin(0, 0);
    line.setPosition(center_x, center_y);
    line.setRotation(get_minute_arrow_direction());

    window.draw(line);
}

void Time::draw_hour_arrow(sf::RenderWindow & window) const {
    sf::RectangleShape line(sf::Vector2f(radius * 4 / 11.0, 7));
    line.setFillColor(sf::Color::Black);
    line.setOrigin(0, 0);
    line.setPosition(center_x, center_y);
    line.setRotation(get_hour_arrow_direction());

    window.draw(line);
}

void Time::draw_little_dot(sf::RenderWindow & window) const {
    sf::CircleShape circle(8);
    circle.setFillColor(sf::Color::Black);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(3);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setPosition(center_x, center_y);

    window.draw(circle);
}

void Time::update_time() {
    time_t timestamp = time(nullptr);
    tm* localTime = localtime(&timestamp);

    hours = static_cast<short>(localTime->tm_hour);
    minutes = static_cast<short>(localTime->tm_min);
    seconds = static_cast<short>(localTime->tm_sec);
}

short Time::get_current_hour() const {
    return hours;
}

short Time::get_current_minute() const{
    return minutes;
}

short Time::get_current_second() const {
    return seconds;
}

float Time::get_hour_arrow_direction() const {
    return (3600.0 * get_current_hour() + 60 * get_current_minute() + get_current_second()) / 240.0 - 90;
}

float Time::get_minute_arrow_direction() const {
    return (60 * get_current_minute() + get_current_second()) / 10.0 - 90;
}

float Time::get_second_arrow_direction() const {
    return get_current_second() * 6 - 90;
}





