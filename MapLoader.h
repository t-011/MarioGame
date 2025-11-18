//
// Created by tariq on 11/18/2025.
//

#ifndef MARIOGAME_MAPLOADER_H
#define MARIOGAME_MAPLOADER_H

#include <vector>
#include "Platform.h"
#include "TextureManager.h"

struct LevelData {
    sf::VertexArray tileVertices;
    const sf::Texture* tileTexture;
    std::vector<Tile> collisionPlatforms;
    sf::Vector2f playerSpawnPos;
};

class MapLoader {
public:
    static constexpr int TILE_SIZE = 32;
    static constexpr int MAP_WIDTH = 50;
    static constexpr int MAP_HEIGHT = 22;

    // 0 = empty, 1 = ground, 2 = player spawn
    static constexpr int tiles[MAP_HEIGHT][MAP_WIDTH] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,2,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    };

    static LevelData loadLevel(TextureManager& textureManager) {
        LevelData level;
        level.tileTexture = &textureManager.getTexture(TextureManager::TextureId::GROUND);
        level.tileVertices.setPrimitiveType(sf::PrimitiveType::Triangles);
        level.collisionPlatforms.reserve(500);
        level.playerSpawnPos = {100.f, 500.f};

        sf::Vector2u texSize = level.tileTexture->getSize();

        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                float posX = static_cast<float>(x * TILE_SIZE);
                float posY = static_cast<float>(y * TILE_SIZE);

                if (tiles[y][x] == 1 || tiles[y][x] == 2) {
                    if (tiles[y][x] == 2) {
                        level.playerSpawnPos = {posX + TILE_SIZE/2.f, posY - 32.f};
                    }

                    // Create 2 triangles (6 vertices) for each quad
                    // Triangle 1
                    level.tileVertices.append(sf::Vertex({posX, posY}, sf::Color::White, {0.f, 0.f}));
                    level.tileVertices.append(sf::Vertex({posX + TILE_SIZE, posY}, sf::Color::White, {static_cast<float>(texSize.x), 0.f}));
                    level.tileVertices.append(sf::Vertex({posX, posY + TILE_SIZE}, sf::Color::White, {0.f, static_cast<float>(texSize.y)}));

                    // Triangle 2
                    level.tileVertices.append(sf::Vertex({posX + TILE_SIZE, posY}, sf::Color::White, {static_cast<float>(texSize.x), 0.f}));
                    level.tileVertices.append(sf::Vertex({posX + TILE_SIZE, posY + TILE_SIZE}, sf::Color::White, {static_cast<float>(texSize.x), static_cast<float>(texSize.y)}));
                    level.tileVertices.append(sf::Vertex({posX, posY + TILE_SIZE}, sf::Color::White, {0.f, static_cast<float>(texSize.y)}));

                    // Create collision platform
                    float scaleX = static_cast<float>(TILE_SIZE) / texSize.x;
                    float scaleY = static_cast<float>(TILE_SIZE) / texSize.y;
                    level.collisionPlatforms.emplace_back(
                        *level.tileTexture,
                        sf::Vector2f{scaleX, scaleY},
                        sf::Vector2f{posX, posY}
                    );
                }
            }
        }

        return level;
}
};

#endif //MARIOGAME_MAPLOADER_H