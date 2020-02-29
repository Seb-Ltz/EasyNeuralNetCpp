//
// Created by Sébastien Letzelter on 29.02.20.
//

#include <iostream>
#include "SuperLayer.h"

SuperLayer::SuperLayer(int neuronNb) : layerSize(neuronNb) {
    layerNeurons = new Neuron[neuronNb];
}

int SuperLayer::getLayerSize() const {
    return layerSize;
}

SuperLayer::~SuperLayer() {
    free(layerNeurons);
}

SuperLayer *SuperLayer::getPrevLayer() const {
    return prevLayer;
}

void SuperLayer::setPrevLayer(SuperLayer *prevLayer) {
    SuperLayer::prevLayer = prevLayer;
}

SuperLayer *SuperLayer::getNextLayer() const {
    return nextLayer;
}

void SuperLayer::setNextLayer(SuperLayer *nextLayer) {
    SuperLayer::nextLayer = nextLayer;
}

void SuperLayer::calculateNeurons() {
    for (int i = 0; i < getLayerSize(); ++i) {
        layerNeurons[i].calculate();
    }
}


