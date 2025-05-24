#pragma once

#include <string>
#include <vector>

class BlockSchema {
    public:
        int id;
        std::string name;
        unsigned char type;
};

std::vector<BlockSchema> readSchemasFromFile(const std::string& filename);