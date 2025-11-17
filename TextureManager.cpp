//
// Created by tariq on 11/16/2025.
//

#include "TextureManager.h"
#include "TextureManager.h"
#include <iostream>


TextureManager::TextureManager()
    : textureMap(std::unordered_map<PlayerTexture, TextureInfo>())
{
    sf::Texture textureIdleAnim;
    sf::Texture textureRunAnim;
    sf::Texture textureJumpAnim;
    if (!textureIdleAnim.loadFromFile("Pink_Monster_Idle.png") ||
        !textureRunAnim.loadFromFile("Pink_Monster_Run.png") ||
        !textureJumpAnim.loadFromFile("Pink_Monster_Jump.png")) {
        std::cout << "Failed to load texture!\n";
        exit(1);
    }

    textureMap.insert({PlayerTexture::IDLE, {textureIdleAnim, {4, 1}}});
    textureMap.insert({PlayerTexture::RUN, {textureRunAnim, {6, 1}}});
    textureMap.insert({PlayerTexture::JUMP, {textureJumpAnim, {8, 1}}});
}

sf::Texture & TextureManager::getTexture(PlayerTexture texture) {
    return textureMap[texture].texture;
}

sf::Vector2u TextureManager::getTextureSize(PlayerTexture texture) {
    return textureMap[texture].size;
}
