#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Player.h"

static constexpr sf::Vector2u STARTING_WINDOW_SIZE({800, 600});

void resizeView(const sf::Window& window, sf::View& view);

int main()
{
    sf::RenderWindow window(sf::VideoMode(STARTING_WINDOW_SIZE), "Mario Game");
    TextureManager textureManager{};

    sf::View view{window.getView()};

    constexpr float FRAME_SWITCH_TIME = 0.3f;
    constexpr float PLAYER_SPEED = 50.f;
    Player player(textureManager, FRAME_SWITCH_TIME, PLAYER_SPEED);
    player.setPosition(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f));

    float deltaTime{};
    sf::Clock clock;

    while (window.isOpen()) {

        deltaTime = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (event->is<sf::Event::Resized>()) {
                resizeView(window, view);
            }
        }
        player.update(deltaTime);
        view.setCenter(player.getPosition());
        window.clear();

        window.setView(view);


        player.draw(window);
        window.display();
    }

}

void resizeView(const sf::Window& window, sf::View& view) {
    view.setSize(sf::Vector2f(static_cast<float>(window.getSize().x),
        static_cast<float>(window.getSize().y)));
}