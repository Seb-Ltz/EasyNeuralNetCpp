//
// Created by Sébastien Letzelter on 28.02.20.
//

#include <iostream>
#include "HiddenLayer.h"

HiddenLayer::HiddenLayer(int neuronNb, ACTIVATION_FUNCTION activation_function) : SuperLayer(neuronNb) {
    //Init all the neurons with their according activation_function
    for (int i = 0; i < neuronNb; ++i) {
        layerNeurons[i].setActivationFunction(activation_function);
    }
}


LAYER_TYPE HiddenLayer::getLayerType() const {
    return HIDDEN;
}

void HiddenLayer::compile() {
    for (int i = 0; i < getLayerSize(); i++) {
        //Give every Neuron a reference to the layer before it and after it
        layerNeurons[i].setPrevLayer(prevLayer);
        layerNeurons[i].setNextLayer(nextLayer);
    }

    std::cout << layerNeurons[0].getPrevWeightsSize() << " - " << getLayerSize() << " - " << layerNeurons[1].getNextWeightsSize() << std::endl;
}
