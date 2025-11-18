//
// Created by tariq on 11/18/2025.
//

#ifndef MARIOGAME_PLATFORM_H
#define MARIOGAME_PLATFORM_H

#include <SFML/Graphics.hpp>

#include "Collider.h"

class Platform {
public:
    Platform(sf::Texture& texture, sf::Vector2f scale, sf::Vector2f position);

    void draw(sf::RenderWindow &window) const;

    Collider &getCollider() { return collider; }

private:
    sf::Sprite body;
    Collider collider;
};


#endif //MARIOGAME_PLATFORM_H