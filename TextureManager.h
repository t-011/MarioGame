#ifndef MARIOGAME_TEXTUREMANAGER_H
#define MARIOGAME_TEXTUREMANAGER_H

#include <cstddef>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <SFML/Graphics/Texture.hpp>


class TextureManager { // Assuming all textures are one row
public:
    enum class TextureId : size_t {IDLE = 0, RUN, JUMP, BG, GROUND, ENEMY};

    TextureManager();
    sf::Texture& getTexture(TextureId texture);
    sf::Vector2u getTextureSize(TextureId texture);

public:
    const sf::Vector2u CHARACTER_SIZE = sf::Vector2u(32, 32);

private:
    struct TextureInfo {
        sf::Texture texture{};
        sf::Vector2u size{};

        TextureInfo(const std::string& path, sf::Vector2u s) : size(s) {
            if (!texture.loadFromFile(path)) {
                std::cerr << "TextureManager::TextureManager(): "
                             "Could not load texture from " << path << std::endl;
                exit(1);
            }
        }
    };

private:
    std::vector<TextureInfo> textureVec;

};


#endif