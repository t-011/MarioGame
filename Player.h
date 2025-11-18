//
// Created by tariq on 11/16/2025.
//

#ifndef MARIOGAME_PLAYER_H
#define MARIOGAME_PLAYER_H

#include  <SFML/Graphics.hpp>
#include  "Animation.h"
#include "Collider.h"

class Player {
    using pTexture = TextureManager::TextureId;
public:
    Player(TextureManager& textureManager, float switchTime, float speed);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition() const;
    Collider& getCollider() { return collider; }

private:
    pTexture currTexture;
    sf::Sprite body;
    Animation animation;
    float speed;
    TextureManager& textureManager;
    Collider collider;
};


#endif //MARIOGAME_PLAYER_H