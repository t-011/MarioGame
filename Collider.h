//
// Created by tariq on 11/18/2025.
//

#ifndef MARIOGAME_COLLIDER_H
#define MARIOGAME_COLLIDER_H
#include <SFML/Graphics.hpp>


class Collider {
public:
    enum class CollidingObject {TILE, PLAYER, ENEMY};

    struct CollisionResult {
        sf::Vector2f point;
        sf::Vector2f normal;
        CollidingObject object;
    };

    explicit Collider(sf::Sprite&  sprite, CollidingObject co);
    std::optional<CollisionResult> resolveCollision(Collider& other, float push = 1.f);

private:
    sf::Sprite& body;
    CollidingObject object;
};


#endif //MARIOGAME_COLLIDER_H