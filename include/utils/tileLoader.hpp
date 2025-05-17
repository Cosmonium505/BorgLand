#pragma once
#include <vector>

class Tile {
    public:
        int type;
        int x, y;
};

extern int testTileMap[5][5];

std::vector<Tile> convertBitmaskToTilemap(int* tilemap, int sizeX, int sizeY);