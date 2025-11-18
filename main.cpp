#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Platform.h"
#include "Player.h"
#include "MapLoader.h"

static constexpr sf::Vector2u STARTING_WINDOW_SIZE({1400, 700});

void resizeView(const sf::Window& window, sf::View& view);

int main()
{
    sf::RenderWindow window(sf::VideoMode(STARTING_WINDOW_SIZE), "Mario Game", sf::Style::Close | sf::Style::Titlebar);
    TextureManager textureManager{};

    sf::View bgView(sf::FloatRect({0, 0}, {STARTING_WINDOW_SIZE.x, STARTING_WINDOW_SIZE.y}));

    sf::RectangleShape background{sf::Vector2f(STARTING_WINDOW_SIZE)};
    background.setTexture(&textureManager.getTexture(TextureManager::TextureId::BG));

    sf::View view{window.getView()};

    LevelData level = MapLoader::loadLevel(textureManager);

    constexpr float FRAME_SWITCH_TIME = 0.3f;
    constexpr float PLAYER_SPEED = 50.f;
    Player player(textureManager, FRAME_SWITCH_TIME, PLAYER_SPEED, 200);
    player.setPosition(level.playerSpawnPos);

    float deltaTime{};
    sf::Clock clock;

    while (window.isOpen()) {

        deltaTime = std::min(clock.restart().asSeconds(), 1.f / 60.f);

        while (const std::optional event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (event->is<sf::Event::Resized>()) {
                resizeView(window, view);
            }
        }


        player.update(deltaTime);

        for (auto& platform : level.collisionPlatforms) {
            if (auto res = player.getCollider().resolveCollision(platform.getCollider(), 1.f)) {
                player.onCollision(res.value());
            }
        }

        view.setCenter(player.getPosition());
        window.clear();

        window.setView(bgView);
        window.draw(background);

        window.setView(view);

        window.draw(level.tileVertices, level.tileTexture);
        player.draw(window);

        window.display();
    }

}

void resizeView(const sf::Window& window, sf::View& view) {
    view.setSize(sf::Vector2f(static_cast<float>(window.getSize().x),
        static_cast<float>(window.getSize().y)));
}