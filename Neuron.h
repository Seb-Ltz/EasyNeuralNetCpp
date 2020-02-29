//
// Created by Sébastien Letzelter on 29.02.20.
//

#ifndef NEURALNETWORKS_NEURON_H
#define NEURALNETWORKS_NEURON_H

#include "ActivationFunction.h"

class SuperLayer;

class Neuron {
public:
    Neuron();

    SuperLayer *getPrevLayer() const;

    void setPrevLayer(SuperLayer *prevLayer);

    SuperLayer *getNextLayer() const;

    void setNextLayer(SuperLayer *nextLayer);

    int getPrevWeightsSize();
    int getNextWeightsSize();

    void setValue(float val);
    void calculate();

    void setActivationFunction(ACTIVATION_FUNCTION activationFunction);
private:
    SuperLayer* prevLayer;
    SuperLayer* nextLayer;
    float* prevLayerWeights;

    //TODO: MAYBE REMOVE THIS \/ and replace it with just an "output"
    //TODO: which is the sum of all prevLayerWeights + bias through activation function
    float* nextLayerWeights;

    float currentValue = 0;
    float bias = 0;
    ACTIVATION_FUNCTION activationFunction = RELU;
public:
};


#endif //NEURALNETWORKS_NEURON_H
