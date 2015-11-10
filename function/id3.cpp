#include <iostream>
#include "id3.h"
using std::cout;

void printVec(const std::vector<string> & list) {
    std::cout << "size = " << list.size() << std::endl;
    for (const auto &var : list) {
        std::cout << var << std::endl;
    }
}

void printGroup(const ID3Group &id3G) {
    cout << "sizeof id3Group = " << id3G.vecNodes.size() << endl;
    for (auto &row : id3G.vecNodes) {
        for (auto &var : row.vecAttribute) {
            cout << var << ' ';
        }
        cout << endl;
    }
}

int readGroup(ID3Group &id3G, char *filePath) {
    std::ifstream inputFile;
    inputFile.open(filePath, std::ifstream::in);
    if (!inputFile.is_open()) {
        std::cerr << "ERROR** ID3 - readGroup -> can't open inputFile" << std::endl;
        return -1;
    }
    char ch;
    string attributeString;

    while (inputFile >> attributeString) {
        id3G.vecAttributeList.push_back(attributeString);
        ch = inputFile.get();
        if (ch == '\n') {
            break;
        }
    }

    // print attribute list
    // printVec(id3G.vecAttributeList);

    // read attributes of each node
    int count = 0;
    ID3Node newNode;
    while (inputFile >> attributeString) {
        if (count % id3G.vecAttributeList.size() == 0) {
            id3G.vecNodes.push_back(newNode);
            newNode.vecAttribute.clear();
        }
        newNode.vecAttribute.push_back(attributeString);
        count++;
    }

    // print group
    // printGroup(id3G);

    inputFile.close();
    return 0;
}