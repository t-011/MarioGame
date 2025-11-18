//
// Created by tariq on 11/18/2025.
//

#ifndef MARIOGAME_TILE_H
#define MARIOGAME_TILE_H

#include <SFML/Graphics.hpp>

#include "Collider.h"

class Tile {
public:
    Tile(const sf::Texture& texture, sf::Vector2f scale, sf::Vector2f position);

    void draw(sf::RenderWindow &window) const;

    const sf::Sprite& getBody() const { return body; }

    Collider &getCollider() { return collider; }

private:
    sf::Sprite body;
    Collider collider;
};


#endif //MARIOGAME_TILE_H