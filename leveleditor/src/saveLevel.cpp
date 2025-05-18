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
    outFile.write(reinterpret_cast<const char*>(&numElements), sizeof(numElements));\

    for (EditorElement* element : editorParams->elements) {
        std::cout << "before: " << outFile.tellp() << std::endl;
        element->save(outFile);
        std::cout << "after: " << outFile.tellp() << std::endl;
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
            std::cout << "before: " << inFile.tellg() << std::endl;
            element->load(inFile);
            std::cout << "after: " << inFile.tellg() << std::endl;
            editorParams->elements.push_back(element);
        }
    }
    inFile.close();
    return 0;
}