#ifndef MARIOGAME_TEXTUREMANAGER_H
#define MARIOGAME_TEXTUREMANAGER_H

#include <cstddef>
#include <unordered_map>
#include <SFML/Graphics/Texture.hpp>


class TextureManager { // Assuming all textures are one row
public:
    enum class PlayerTexture : size_t {IDLE = 0, RUN, JUMP};

    TextureManager();
    sf::Texture& getTexture(PlayerTexture texture);
    sf::Vector2u getTextureSize(PlayerTexture texture);

public:
    const sf::Vector2u TEXTURE_SIZE = sf::Vector2u(32, 32);

private:
    struct TextureInfo {
        sf::Texture texture{};
        sf::Vector2u size{};
    };

private:
    std::unordered_map<PlayerTexture, TextureInfo> textureMap;

};


#endif