//
// Created by Sébastien Letzelter on 28.02.20.
//

#include <iostream>
#include "Model.h"
#include "Layers/InputLayer.h"

Model::Model() {
    layers = new std::vector<SuperLayer*>();
}

void Model::add(SuperLayer* layer) {
    layers->push_back(layer);
}

void Model::compile() {
    //Give the layers the layers before and after them
    for (unsigned i = 0; i < layers->size(); ++i) {
        SuperLayer* current = layers->at(i);

        if(i > 0) {
            current->setPrevLayer(layers->at(i-1));
        }
        if(i < layers->size() - 1) {
            current->setNextLayer(layers->at(i+1));
        }

        std::cout << current->getLayerSize() << std::endl;
    }

    //And then "compile" everything
    for (unsigned i = 0; i < layers->size(); ++i) {
        SuperLayer* current = layers->at(i);
        current->compile();
    }

}

void Model::fit(float** input) {
    //TODO
    //TODO COST FUNCTION AND EVERYTHING
}

float** Model::predict(float input[]) {

    //Set the values to the neurons of the input layer
    SuperLayer* fistLayer = layers->at(0);
    if(fistLayer->getLayerType() == INPUT) {
        InputLayer* inputLayer = (dynamic_cast<InputLayer*>(fistLayer));
        inputLayer->initNeurons(input);
    } else {
        std::cerr << "Model.cpp - predict - First layer of the model is not an Input Layer" << std::endl;
    }

    //Now calculate the results of each layer
    for(int i = 1; i < layers->size(); ++i) {
        layers->at(i)->calculateNeurons();
    }

    //Retrieve the values of the output layer
    //TODO
    return nullptr;
}
