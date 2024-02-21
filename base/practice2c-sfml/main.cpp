// TUTORIALS
// Getting started   SFML with the CMake Project Template   https://www.sfml-dev.org/tutorials/2.6/start-cmake.php
// Window module     Opening and managing a SFML window     https://www.sfml-dev.org/tutorials/2.6/window-window.php
// Window module     Events explained                       https://www.sfml-dev.org/tutorials/2.6/window-events.php
// Window module     Keyboard, mouse and joystick           https://www.sfml-dev.org/tutorials/2.6/window-inputs.php
// System module     Handling time                          https://www.sfml-dev.org/tutorials/2.6/system-time.php
// Graphics module   Drawing 2D stuff                       https://www.sfml-dev.org/tutorials/2.6/graphics-draw.php
// Graphics module   Shapes                                 https://www.sfml-dev.org/tutorials/2.6/graphics-shape.php
// Graphics module   Text and fonts                         https://www.sfml-dev.org/tutorials/2.6/graphics-text.php

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

using namespace std;

int main() {
  sf::RenderWindow window(sf::VideoMode(600u, 400u), "Practice 2C: SFML");
  window.setFramerateLimit(30);

  vector<sf::Color> colors;
  colors.push_back(sf::Color::Red);
  colors.push_back(sf::Color::Blue);

  vector<sf::CircleShape> circles;
  sf::VertexArray lines(sf::PrimitiveType::LineStrip);

  sf::Clock clock;

  while (window.isOpen()) {
    sf::Event e;
    while (window.pollEvent(e)) {
      switch (e.type) {
      case sf::Event::Closed:
        window.close();
        break;
      case sf::Event::MouseButtonPressed:
        auto pos = sf::Vector2f(e.mouseButton.x, e.mouseButton.y);

        auto color_idx = static_cast<int>(clock.getElapsedTime().asSeconds()) % colors.size();
        auto color = colors[color_idx];

        sf::CircleShape circle(10);
        circle.setPosition(pos - sf::Vector2f(10, 10));
        circle.setFillColor(color);
        circles.push_back(circle);

        lines.append(sf::Vertex(pos, sf::Color::Black));

        break;
      }
    }

    window.clear(sf::Color::White);

    for (size_t i = 0; i < circles.size(); ++i) {
      window.draw(circles[i]);
    }

    window.draw(lines);

    window.display();
  }
}
