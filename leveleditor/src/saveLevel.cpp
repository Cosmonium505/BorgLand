#include "saveLevel.hpp"
#include <fstream>
#include "editorParams.hpp"
#include "editorElement.hpp"
#include "blockElement.hpp"

int saveLevel(const std::string& filename) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        return -1; // Error opening file
    }
    int numElements = editorParams->elements.size();
    outFile.write(reinterpret_cast<const char*>(&numElements), sizeof(numElements));
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
        printf("Loading element of type %d\n", static_cast<int>(type));
        if (type == EditorElementType::BLOCK) {
            element = new BlockElement(0, 0, 0, 0);
        }
        if (element) {
            element->load(inFile);
            printf("Loaded element of type %d at (%f, %f)\n", static_cast<int>(type), element->x, element->y);
            editorParams->elements.push_back(element);
        }
    }
    inFile.close();
    return 0;
}