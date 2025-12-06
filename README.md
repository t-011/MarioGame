# Mario Game

A simple Mario-like platformer built with SFML in C++.

## Features

- Player movement and jumping
- Enemy AI
- Collision detection
- Animation system
- Tile-based map loading
- Texture management

## Requirements

- C++
- SFML library (configured by developer)
- CMake
- Compiler with C++11 support

## Build
```bash
cmake .
make
./MarioGame
```

## Controls

- **Arrow Keys** — Move left/right and jump
- **ESC** — Exit game

## Architecture

- `Player.h/cpp` — Player mechanics
- `Enemy.h/cpp` — Enemy behavior
- `Platform.h/cpp` — Platforms and collision
- `Animation.h/cpp` — Sprite animation
- `MapLoader.h` — Level loading
- `TextureManager.h/cpp` — Asset management

Note: Configure SFML and build settings before cloning.
