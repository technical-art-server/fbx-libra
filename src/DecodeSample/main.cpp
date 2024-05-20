#include <iostream>
#include <fstream>
#include <fbxsdk.h>
#include <filesystem>

#include "../data/hcw_generated.h"

using namespace std;
using namespace FbxLibra::CounterWeight;

int main() {
    ifstream fin("sample.hcw", ios::in | ios::binary);
    if (!fin){
        return 1;
    }

    auto begin = fin.tellg();
    fin.seekg(0, fin.end);
    auto end = fin.tellg();
    fin.clear();
    fin.seekg(0, fin.beg);
    auto len = end - begin;
    auto buf = new char[len + 1];
    fin.read(buf, len);
    fin.close();

    auto hierarchy = GetHierarchy((uint8_t*)buf);

    printf("{\n");

    for (auto node: *hierarchy->nodes()){
        auto transform = node->transform();
        auto position = transform->position();
        auto rotation = transform->rotation();
        auto scale = transform->scale();

        std::cout << std::fixed;
        std::cout << node->name()->c_str() << std::endl;
        std::cout << "\tTranslation: (" << position->x() << ", " << position->y() << ", " << position->z() << ")" << std::endl;
        std::cout << "\tRotation: (" << rotation->x() << ", " << rotation->y() << ", " << rotation->z() << ")" << std::endl;
        std::cout << "\tScaling: (" << scale->x() << ", " << scale->y() << ", " << scale->z() << ")" << std::endl;
    }

    printf("}\n");
    delete[] buf;

    return 0;
}