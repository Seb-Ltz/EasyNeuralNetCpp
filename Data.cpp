//
// Created by Sébastien Letzelter on 29.02.20.
//

#include <iostream>
#include "Data.h"

Data::Data(const std::string &filename) : filename(filename), file(filename, std::ifstream::binary)
{
    if(!file.is_open()) {
        std::cerr << "Data.cpp - Data - Error opening file..." << std::endl;
        return;
    }
}

float** Data::parseTo2D(int offset, int size, int elementSize) {
    if(!file.is_open()) {
        std::cerr << "Data.cpp - parseTo2D - Error opening file..." << std::endl;
        return nullptr;
    }

    //Set offset
    file.seekg(offset, file.beg);

    //Init 2D array
    auto ** res = new float*[size];
    for (int i = 0; i < size; ++i) {
        res[i] = new float[elementSize];
    }

    //TODO: Maybe optimize this part, like having a bigger buffer
    char buff[elementSize];
    for (int i = 0; i < size; ++i) {
        //Read one byte to the buffer
        file.read(buff, elementSize);

        for (int j = 0; j < elementSize; ++j) {
            auto value = static_cast<float>(static_cast<unsigned char>(buff[j]));
            res[i][j] = value;
        }
    }

    return res;
}

float* Data::parseTo1D(int offset, int size) {
    if(!file.is_open()) {
        std::cerr << "Data.cpp - parseTo1D - Error opening file..." << std::endl;
        return nullptr;
    }

    auto res = new float[size];
    //Set offset
    file.seekg(offset, file.beg);

    //TODO: Maybe optimize this part, like having a bigger buffer
    char buff[1];

    for (int i = 0; i < size; ++i) {
        //Read one byte to the buffer
        file.read(buff, 1);

        auto value = static_cast<float>(static_cast<unsigned char>(buff[0]));
        res[i] = value;
    }

    return res;
}
