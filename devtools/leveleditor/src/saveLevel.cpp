#include "saveLevel.hpp"
#include <fstream>
#include "editorParams.hpp"
#include "editorElement.hpp"
#include "blockElement.hpp"
#include "utils/tileLoader.hpp"

int saveLevel(const std::string& filename) {
    std::ofstream outFile(filename, std::ios::binary | std::ios::trunc);
    if (!outFile) {
        return -1; // Error opening file
    }
    int numElements = editorParams->elements.size();
    outFile.write(reinterpret_cast<const char*>(&numElements), sizeof(numElements));\

    for (EditorElement* element : editorParams->elements) {
        element->save(outFile);
    }
    outFile.close();
    return 0;
}

int loadLevel(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        return -1;
    }
    int numElements;
    inFile.read(reinterpret_cast<char*>(&numElements), sizeof(numElements));
    for (int i = 0; i < numElements; ++i) {
        EditorElementType type;
        inFile.read(reinterpret_cast<char*>(&type), sizeof(type));
        EditorElement* element = nullptr;
        if (type == EditorElementType::BLOCK) {
            element = new BlockElement(0, 0, 0, 0);
        }
        if (element) {
            element->load(inFile);
            editorParams->elements.push_back(element);
        }
    }
    inFile.close();
    return 0;
}

int exportLevel(const std::string& filename) {
    std::ofstream outFile(filename, std::ios::binary | std::ios::trunc);
    if (!outFile) {
        return -1;
    }

    int numElements = editorParams->elements.size();
    outFile.write(reinterpret_cast<const char*>(&numElements), sizeof(numElements));
    for (EditorElement* element : editorParams->elements) {
        if (element->type != EditorElementType::BLOCK) {
            continue;
        }
        BlockElement* blockElement = static_cast<BlockElement*>(element);
        outFile.write(reinterpret_cast<const char*>(&blockElement->blockType), sizeof(element->type));
        outFile.write(reinterpret_cast<const char*>(&element->x), sizeof(element->x));
        outFile.write(reinterpret_cast<const char*>(&element->y), sizeof(element->y));
    }
    outFile.close();
    return 0;
}