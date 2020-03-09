//
// Created by Sébastien Letzelter on 29.02.20.
//

#ifndef NEURALNETWORKS_DATA_H
#define NEURALNETWORKS_DATA_H


#include <string>
#include <fstream>

class Data {
public:
    Data(const std::string &filename);

    /**
     * Parses a file into a 2D Array
     * @param offset Offset before starting to read the content of file
     * @param size amount of elements that are going to be read
     * @param elementSize amount of floats that are in an individual element.
     * @return a 2D Array containg every elements
     */
    float** parseTo2D(int offset, int size, int elementSize);
    float* parseTo1D(int offset, int size);

private:
    std::string filename;
    std::ifstream file;
};


#endif //NEURALNETWORKS_DATA_H
