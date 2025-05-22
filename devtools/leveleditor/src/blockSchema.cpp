#include "blockSchema.hpp"
#include <fstream>
#include <iostream>


std::vector<BlockSchema> readSchemasFromFile(const std::string& filename) {
    std::vector<BlockSchema> schemas;
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        throw std::runtime_error("Could not open file: " + filename);
    }

    file.seekg(0, std::ios::beg);
    int blockCount = 0;
    file.read(reinterpret_cast<char*>(&blockCount), sizeof(blockCount));

    for (int i = 0; i < blockCount; ++i) {
        BlockSchema schema;
        file.read(reinterpret_cast<char*>(&schema.id), sizeof(schema.id));
        file.read(reinterpret_cast<char*>(&schema.type), sizeof(schema.type));
        int nameLength;
        file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        schema.name.resize(nameLength);
        file.read(reinterpret_cast<char*>(schema.name.data()), nameLength);
        schemas.push_back(schema);
    }
    file.close();
    return schemas;


}