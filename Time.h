#ifndef TIME_H
#define TIME_H

#include <utility>
#include <SFML/Graphics/RenderWindow.hpp>

using namespace std;

class Time {
private:
    short hours{};
    short minutes{};
    short seconds{};
    float radius{};
    float center_x{};
    float center_y{};

public:
    Time();

    void set_radius(float radius);

    void update_time();

    void draw_second_arrow(sf::RenderWindow & window) const;

    void draw_minute_arrow(sf::RenderWindow & window) const;

    void draw_hour_arrow(sf::RenderWindow & window) const;

    void draw_little_dot(sf::RenderWindow & window) const;

    void draw_clock_circle(sf::RenderWindow & window) const;

    void draw_clock_numbers(sf::RenderWindow & window) const;

    void loop(sf::RenderWindow & window);

    void draw_clock();

    short get_current_hour() const;

    short get_current_minute() const;

    short get_current_second() const;

    float get_hour_arrow_direction() const;

    float get_minute_arrow_direction() const;

    float get_second_arrow_direction() const;
};

#endif //TIME_H
