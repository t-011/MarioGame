#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Platform.h"
#include "Player.h"

static constexpr sf::Vector2u STARTING_WINDOW_SIZE({512, 512});

void resizeView(const sf::Window& window, sf::View& view);

int main()
{
    sf::RenderWindow window(sf::VideoMode(STARTING_WINDOW_SIZE), "Mario Game");
    TextureManager textureManager{};

    sf::View view{window.getView()};

    sf::Sprite background(textureManager.getTexture(TextureManager::TextureId::BG));


    constexpr float FRAME_SWITCH_TIME = 0.3f;
    constexpr float PLAYER_SPEED = 50.f;
    Player player(textureManager, FRAME_SWITCH_TIME, PLAYER_SPEED);

    Platform platform1(textureManager.getTexture(TextureManager::TextureId::IDLE), {1.f, 1.f}, {500, 200});
    Platform platform2(textureManager.getTexture(TextureManager::TextureId::IDLE), {1.f, 1.f}, {500, 0});

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

        player.getCollider().resolveCollision(platform1.getCollider(), 1.f);
        player.getCollider().resolveCollision(platform2.getCollider(), 0.f);

        view.setCenter(player.getPosition());
        window.clear();

        window.setView(window.getDefaultView());
        window.draw(background);

        window.setView(view);


        player.draw(window);
        platform1.draw(window);
        platform2.draw(window);
        window.display();
    }

}

void resizeView(const sf::Window& window, sf::View& view) {
    view.setSize(sf::Vector2f(static_cast<float>(window.getSize().x),
        static_cast<float>(window.getSize().y)));
}