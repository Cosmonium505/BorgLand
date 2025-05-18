#include "engine.hpp"
#include "world.hpp"
#include "block.hpp"

#include <vector>
#include <fstream>
#include <iostream>

#include "utils/tileLoader.hpp"

std::vector<Tile> convertBitmaskToTilemap(int* tilemap, int sizeX, int sizeY) {
    std::vector<Tile> tiles = std::vector<Tile>();
    for (int y = 0; y < sizeY; ++y) {
        for (int x = 0; x < sizeX; ++x) {
            if (tilemap[y * sizeX + x] != 0) {
                Tile tile;
                tile.type = tilemap[y * sizeX + x];
                tile.x = x;
                tile.y = y;
                tiles.push_back(tile);
            }
        }
    }
    return tiles;
}

std::vector<Tile> loadTilemapFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    int amountOfBlocks = 0;
    file.read(reinterpret_cast<char*>(&amountOfBlocks), sizeof(int));
    std::vector<Tile> tiles;

    for (int i = 0; i < amountOfBlocks; ++i) {
        Tile tile;
        file.read(reinterpret_cast<char*>(&tile.type), sizeof(int));
        file.read(reinterpret_cast<char*>(&tile.x), sizeof(int));
        file.read(reinterpret_cast<char*>(&tile.y), sizeof(int));
        tiles.push_back(tile);
    }
    file.close();
    return tiles;
}