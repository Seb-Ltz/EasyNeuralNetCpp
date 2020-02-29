//
// Created by Sébastien Letzelter on 29.02.20.
//

#include <printf.h>
#include <iostream>
#include "Neuron.h"
#include "Layers/SuperLayer.h"

Neuron::Neuron() {
}

SuperLayer *Neuron::getPrevLayer() const {
    return prevLayer;
}

void Neuron::setPrevLayer(SuperLayer *prevLayer) {
    if(prevLayer == nullptr) {
        return;
    }
    Neuron::prevLayer = prevLayer;

    //As we now know how many Neurons we have on the previous layer we can create a list of weights
    prevLayerWeights = new float[prevLayer->getLayerSize()];
}

SuperLayer *Neuron::getNextLayer() const {
    return nextLayer;
}

void Neuron::setNextLayer(SuperLayer *nextLayer) {
    if(nextLayer == nullptr) {
        return;
    }
    Neuron::nextLayer = nextLayer;
    //Here too, we can now know how many weights we have on the right side
    nextLayerWeights = new float[nextLayer->getLayerSize()];
}

int Neuron::getPrevWeightsSize() {
    if(prevLayer == nullptr) return 0;
    return prevLayer->getLayerSize();
}

int Neuron::getNextWeightsSize() {
    if(nextLayer == nullptr) return 0;
    return nextLayer->getLayerSize();
}

void Neuron::setValue(float val) {
    currentValue = val;
}

void Neuron::calculate() {
    //Calculate the sum of all the weights + the bias
    float sum = bias;
    for(int i = 0; i < getPrevWeightsSize(); ++i) {
        sum += prevLayerWeights[0];
    }

    //Calculate the activation function
    float H = ActivationCalculator::calculate(activationFunction, sum);

    //And save it in current value
    currentValue = H;

}

void Neuron::setActivationFunction(ACTIVATION_FUNCTION activationFunction) {
    Neuron::activationFunction = activationFunction;
}
