//
// Created by tariq on 11/16/2025.
//

#include "TextureManager.h"
#include "TextureManager.h"
#include <iostream>


TextureManager::TextureManager()
{
    textureVec.reserve(10); // Needed to avoid realloc

    textureVec.emplace_back("Pink_Monster_Idle.png", sf::Vector2u{4, 1});
    textureVec.emplace_back("Pink_Monster_Run.png", sf::Vector2u{6, 1});
    textureVec.emplace_back("Pink_Monster_Jump.png", sf::Vector2u{8, 1});
    textureVec.emplace_back("landscape.png", sf::Vector2u{16, 1});
    textureVec.emplace_back("vantablack.jpg", sf::Vector2u{1, 1});
}

sf::Texture& TextureManager::getTexture(TextureId texture) {
    return textureVec[static_cast<size_t>(texture)].texture;
}

sf::Vector2u TextureManager::getTextureSize(TextureId texture) {
    return textureVec[static_cast<size_t>(texture)].size;
}
