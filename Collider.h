//
// Created by tariq on 11/18/2025.
//

#ifndef MARIOGAME_COLLIDER_H
#define MARIOGAME_COLLIDER_H
#include <SFML/Graphics.hpp>


class Collider {
public:
    struct CollisionResult {
        sf::Vector2f point;
        sf::Vector2f normal;
    };

    explicit Collider(sf::Sprite&  sprite);
    std::optional<CollisionResult> resolveCollision(Collider& other, float push = 1.f);

private:
    sf::Sprite& body;
};


#endif //MARIOGAME_COLLIDER_H