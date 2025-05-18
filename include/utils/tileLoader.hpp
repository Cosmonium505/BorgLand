#pragma once
#include <vector>

class Tile {
    public:
        int type;
        float x, y;
};

std::vector<Tile> convertBitmaskToTilemap(int* tilemap, int sizeX, int sizeY);
std::vector<Tile> loadTilemapFromFile(const std::string& filename);