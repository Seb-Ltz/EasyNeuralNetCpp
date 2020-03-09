//
// Created by Sébastien Letzelter on 29.02.20.
//

#include <iostream>
#include "InputLayer.h"

InputLayer::InputLayer(int neuronNb) : SuperLayer(neuronNb) {

}

LAYER_TYPE InputLayer::getLayerType() const {
    return INPUT;
}

void InputLayer::compile() {
    for (int i = 0; i < getLayerSize(); i++) {
        //Give every Neuron a reference to the layer before it and after it
        layerNeurons[i].setNextLayer(nextLayer);
    }
}

/**
 * Sets the values of the Neurons of the input layer.
 * @param input Array of floats containing all the values for every neuron of the layer.
 */
void InputLayer::initNeurons(float *input) {
    for(int i = 0; i < getLayerSize(); i++) {
        layerNeurons[i].setValue(input[i]);
    }

}
