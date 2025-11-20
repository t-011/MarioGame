#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Platform.h"
#include "Player.h"
#include "MapLoader.h"
#include "Enemy.h"

static constexpr sf::Vector2u STARTING_WINDOW_SIZE({1400, 700});

void resizeView(const sf::Window& window, sf::View& view);

int main()
{
    sf::RenderWindow window(sf::VideoMode(STARTING_WINDOW_SIZE), "Platformer", sf::Style::Close | sf::Style::Titlebar);
    TextureManager textureManager{};

    sf::View bgView(sf::FloatRect({0, 0}, {STARTING_WINDOW_SIZE.x, STARTING_WINDOW_SIZE.y}));

    sf::RectangleShape background;
    background.setTexture(&textureManager.getTexture(TextureManager::TextureId::BG));

    sf::View view(sf::Vector2f(), sf::Vector2f({STARTING_WINDOW_SIZE.x / 2, STARTING_WINDOW_SIZE.y / 2}));

    LevelData level = MapLoader::loadLevel(textureManager);

    constexpr float FRAME_SWITCH_TIME = 0.3f;
    constexpr float PLAYER_SPEED = 80.f;
    Player player(textureManager, FRAME_SWITCH_TIME, PLAYER_SPEED, 200);
    player.setPosition(level.playerSpawnPos);

    std::vector<Enemy> enemies;
    enemies.reserve(level.enemiesSpawnPos.size());
    for (size_t i = 0; i < level.enemiesSpawnPos.size(); ++i) {
        constexpr float enemySpeed = 50.f;
        enemies.emplace_back(textureManager, enemySpeed);
        enemies.back().setPosition(level.enemiesSpawnPos[i]);
    }

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
        for (auto& enemy : enemies) { enemy.update(deltaTime); }

        for (auto& platform : level.collisionPlatforms) {
            if (!player.isDead) {
                if (auto res = player.getCollider().resolveCollision(platform.getCollider(), 1.f))
                    player.onCollision(res.value());
            }
            for (auto& enemy : enemies) {
                if (!enemy.isDead) {
                    if (auto res = enemy.getCollider().resolveCollision(platform.getCollider(), 1.f))
                        enemy.onCollision(res.value());
                }

            }
        }

        for (auto& enemy : enemies) {

            if (auto res = player.getCollider().resolveCollision(enemy.getCollider(), 1.f)) {
                player.onCollision(res.value());

                Collider::CollisionResult enemyRes = res.value();
                enemyRes.normal = -enemyRes.normal;
                enemyRes.object = Collider::CollidingObject::PLAYER;
                enemy.onCollision(enemyRes);
            }
            if (player.isDead) {
                //linear interpolation
                sf::Vector2f currentCenter = view.getCenter();
                sf::Vector2f targetCenter = enemy.getPosition();
                float smoothFactor = 5.0f; // Higher = faster, lower = smoother

                sf::Vector2f newCenter = currentCenter + (targetCenter - currentCenter) * smoothFactor * deltaTime;
                view.setCenter(newCenter);
            }
        }

        if (!player.isDead) view.setCenter(player.getPosition());
        window.clear(sf::Color(150, 150, 150));

        // window.setView(bgView);

        window.setView(view);
        // window.draw(background);

        window.draw(level.tileVertices, level.tileTexture);
        player.draw(window);
        for (auto& enemy : enemies) { enemy.draw(window); }

        window.display();
    }

}

void resizeView(const sf::Window& window, sf::View& view) {
    view.setSize(sf::Vector2f(static_cast<float>(window.getSize().x),
        static_cast<float>(window.getSize().y)));
}