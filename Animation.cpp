//
// Created by tariq on 11/14/2025.
//

#include "Animation.h"

#include <iostream>
#include <utility>


Animation::Animation(const TextureManager&  textureManager, const float switchTime)
    : textureManager(textureManager), switchTime(switchTime)
{

    rect.size.x = textureManager.TEXTURE_SIZE.x;
    rect.size.y = textureManager.TEXTURE_SIZE.y;
}

void Animation::update(pTexture texture, const float deltaTime) {
    // currPos.y = static_cast<size_t>(row);


    totalTime += deltaTime;
    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currPos.x = (currPos.x + 1) % textureManager.getTextureSize(texture).x;
    }

    rect.position.x = currPos.x * rect.size.x;
    // rect.position.y = currPos.y * rect.size.y;
}

