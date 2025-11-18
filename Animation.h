#ifndef MARIOGAME_ANIMATION_H
#define MARIOGAME_ANIMATION_H

#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class Animation {
    using pTexture = TextureManager::TextureId;
public:
    Animation(const TextureManager&  textureManager, float switchTime);
    void update(pTexture texture, float deltaTime);

public:
    sf::IntRect rect{};

private:
    TextureManager textureManager;
    sf::Vector2u currPos;

    float totalTime{};
    float switchTime{};
};


#endif //MARIOGAME_ANIMATION_H