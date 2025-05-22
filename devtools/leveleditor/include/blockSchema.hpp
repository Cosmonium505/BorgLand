#pragma once

#include <string>
#include <vector>

class BlockSchema {
    public:
        int id;
        std::string name;
        u_int8_t type;
};

std::vector<BlockSchema> readSchemasFromFile(const std::string& filename);