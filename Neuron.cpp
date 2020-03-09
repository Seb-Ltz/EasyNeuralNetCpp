//
// Created by Sébastien Letzelter on 29.02.20.
//

#include <printf.h>
#include <iostream>
#include "Neuron.h"
#include "Layers/SuperLayer.h"
#include "Model.h"

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

    for(int i = 0; i < prevLayer->getLayerSize(); i++) {
        //Init all the weights to a random number
        prevLayerWeights[i] = ((float) rand() / (RAND_MAX));
//        prevLayerWeights[i] = 0.25;
    }
}

SuperLayer *Neuron::getNextLayer() const {
    return nextLayer;
}

void Neuron::setNextLayer(SuperLayer *nextLayer) {
    if(nextLayer == nullptr) {
        return;
    }
    Neuron::nextLayer = nextLayer;
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
    Neuron* prevNeurons = getPrevLayer()->getLayerNeurons();

    //Calculate the sum of all the weights + the bias
    float sum = bias;
    for(int i = 0; i < getPrevWeightsSize(); ++i) {
        sum += prevNeurons[i].getCurrentValue() * prevLayerWeights[i];
    }

    //Calculate the activation function
    float H = ActivationCalculator::calculate(activationFunction, sum);

    //And save it in current value
    currentValue = H;

}

void Neuron::setActivationFunction(ACTIVATION_FUNCTION activationFunction) {
    Neuron::activationFunction = activationFunction;
}

float Neuron::getCurrentValue() const {
    return currentValue;
}

float Neuron::getPrevWeightAt(unsigned int i) const {
    return prevLayerWeights[i];
}

void Neuron::addWeightAt(unsigned int i, float value) {
    prevLayerWeights[i] += value;
}

void Neuron::addBias(float value) {
    bias += value;
}

float Neuron::getBias() const {
    return bias;
}

float Neuron::getDelta() const {
    return delta;
}

void Neuron::setDelta(float delta) {
    Neuron::delta = delta;
}

