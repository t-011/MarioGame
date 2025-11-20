//
// Created by tariq on 11/20/2025.
//

#ifndef MARIOGAME_ENEMY_H
#define MARIOGAME_ENEMY_H

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"

class Enemy {
    enum class Direction {FACE_RIGHT, FACE_LEFT};
    using enum Direction;
    using pTexture = TextureManager::TextureId;
public:
    Enemy(TextureManager& textureManager, float speed);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    void onCollision(Collider::CollisionResult& cr);

    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition() const { return body.getPosition(); }
    Collider& getCollider() { return collider; }

public:
    bool isDead = false;

private:
    sf::Sprite body;
    float speed;
    Collider collider;

    Direction direction = FACE_RIGHT;
    sf::Vector2f velocity{};
};


#endif //MARIOGAME_ENEMY_H