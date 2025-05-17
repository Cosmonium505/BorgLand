#pragma once
#include <vector>

class Tile {
    public:
        int type;
        int x, y;
};

std::vector<Tile> convertBitmaskToTilemap(int* tilemap, int sizeX, int sizeY);