//
// Created by tariq on 11/18/2025.
//

#include "Platform.h"

Tile::Tile(const sf::Texture& texture, sf::Vector2f scale, sf::Vector2f position)
    : body(texture), collider(body)
{
    body.setScale(scale);
    body.setPosition(position);
}

void Tile::draw(sf::RenderWindow &window) const {
    window.draw(body);
}
