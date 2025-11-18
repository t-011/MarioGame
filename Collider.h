//
// Created by tariq on 11/18/2025.
//

#ifndef MARIOGAME_COLLIDER_H
#define MARIOGAME_COLLIDER_H
#include <SFML/Graphics.hpp>


class Collider {
public:
    explicit Collider(sf::Sprite&  sprite);
    bool resolveCollision(Collider& other, float push = 1.f);

private:
    sf::Sprite& body;
};


#endif //MARIOGAME_COLLIDER_H