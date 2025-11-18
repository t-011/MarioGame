//
// Created by tariq on 11/18/2025.
//

#include "Platform.h"

Platform::Platform(sf::Texture& texture, sf::Vector2f scale, sf::Vector2f position)
    : body(texture), collider(body)
{
    body.setScale(scale);
    body.setPosition(position);

    sf::FloatRect bounds = body.getLocalBounds();
    body.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
}

void Platform::draw(sf::RenderWindow &window) const {
    window.draw(body);
}
