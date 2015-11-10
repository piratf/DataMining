#ifndef ID3
#define ID3

#include <iostream>
#include <string>
#include <fstream>
#include "general.h"
using std::vector;
using std::string;
using std::ifstream;
using std::cout;
using std::endl;

struct ID3Node
{
    std::vector<string> vecAttribute;
};

struct ID3Group
{
    vector<string> vecAttributeList;
    vector<ID3Node> vecNodes;
};

void printVec(const std::vector<string> & list);

void printGroup(const ID3Group &id3G);

int readGroup(ID3Group &id3G, char *filePath);

#endif