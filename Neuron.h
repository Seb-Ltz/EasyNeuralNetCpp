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

    float getCurrentValue() const;

    float getPrevWeightAt(unsigned int i) const;

    /**
     * Adds to the weight at position i, the float "value".
     * @param i the position of the weight.
     * @param value the value that will be added to the weight.
     */
    void addWeightAt(unsigned int i, float value);

    void addBias(float value);

    float getDelta() const;

    void setDelta(float delta);

    float getBias() const;


private:
    SuperLayer* prevLayer;
    SuperLayer* nextLayer;
    float* prevLayerWeights;

    float currentValue = 0;
    float bias = 0;
    float delta = 0;

    ACTIVATION_FUNCTION activationFunction = RELU;
public:
};


#endif //NEURALNETWORKS_NEURON_H
