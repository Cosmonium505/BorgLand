#include "engine.hpp"
#include "world.hpp"
#include "block.hpp"

#include <vector>

#include "utils/tileLoader.hpp"

int testTileMap[5][5] = {
    {0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0},
    {0, 1, 1, 1, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0}
};

std::vector<Tile> convertBitmaskToTilemap(int* tilemap, int sizeX, int sizeY) {
    std::vector<Tile> tiles = std::vector<Tile>();
    for (int y = 0; y < sizeY; ++y) {
        for (int x = 0; x < sizeX; ++x) {
            if (tilemap[y * sizeX + x] == 1) {
                Tile tile;
                tile.type = 1;
                tile.x = x;
                tile.y = y;
                tiles.push_back(tile);
            }
        }
    }
    return tiles;
}