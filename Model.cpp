//
// Created by Sébastien Letzelter on 28.02.20.
//

#include <iostream>
#include <cmath>
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
    }

    //And then "compile" everything
    for (unsigned i = 0; i < layers->size(); ++i) {
        SuperLayer* current = layers->at(i);
        current->compile();
    }

}

void Model::fit(float** input, float** expected, size_t arraySize, int epochs, int batch_size) {

    for(int epochsCounter = 0; epochsCounter < epochs; epochsCounter++) {
        float avgLoss = 0;

        //For each input
        for (int i = 0; i < arraySize && i < batch_size; ++i) {

            //Forward Pass
            float *predicted = predictOnce(input[i]);

            //Calculate the loss function of each Neuron
            float lossVal = loss(predicted, expected[i], getLayerSize(size() - 1));
            avgLoss += lossVal;

            //For every layer, starting from the last
            for (int j = (size() - 1); j > 0; --j) {
                size_t layerSize = getLayerSize(j);
                SuperLayer *currLayer = layers->at(j);
                Neuron *currLayerNeurons = layers->at(j)->getLayerNeurons();

                //For every neuron in that layer
                for (int neurJ = 0; neurJ < layerSize; ++neurJ) {

                    //Calculate the delta
                    float deltaNew = deltaJ(j, neurJ, expected, predicted, i);

                    //For every weight in that neuron
                    for (unsigned int neurI = 0; neurI < currLayerNeurons[neurJ].getPrevWeightsSize(); ++neurI) {

                        //                 Output of the neuron : o_i
                        float derivative = currLayer->getPrevLayer()->getLayerNeurons()[neurI].getCurrentValue();

                        derivative *= deltaNew;

                        //Update the weight
                        currLayerNeurons[neurJ].addWeightAt(neurI, -LEARNING_RATE * derivative);
                    }

                    currLayerNeurons[neurJ].addBias(-LEARNING_RATE * deltaNew);
                }
            }
        }

        avgLoss /= batch_size;
        std::cout << (epochsCounter + 1) << "/" << epochs << ":  Loss = " << avgLoss << std::endl;
    }

}

float** Model::predict(float** input, size_t inputSize) {

    auto** res = new float*[inputSize];

    for (int i = 0; i < inputSize; ++i) {
        res[i] = predictOnce(input[i]);
    }

    return res;
}

float* Model::predictOnce(float* input) {

    //Set the values to the neurons of the input layer
    SuperLayer* firstLayer = layers->at(0);

    if(firstLayer->getLayerType() == INPUT) {
        InputLayer* inputLayer = (dynamic_cast<InputLayer*>(firstLayer));
        inputLayer->initNeurons(input);
    } else {
        std::cerr << "Model.cpp - predict - First layer of the model is not an Input Layer" << std::endl;
    }

    //Now calculate the results of each layer
    for(unsigned int j = 1; j < size(); ++j) {
        layers->at(j)->calculateNeurons();
    }

    int outputLayerSize = getLayerSize(size() - 1);

    float* output = new float[outputLayerSize];
    for(unsigned int j = 0; j < outputLayerSize; ++j) {
        output[j] = layers->at(size() - 1)->getLayerNeurons()[j].getCurrentValue();
    }
    return output;

}

float Model::loss(const float* predicted, const float* expected, size_t arraySize) {
    //Using square error: E(y, y') = 1/2 * (y - y')^2
    float res = 0;
    for (int i = 0; i < arraySize; ++i) {
        res += pow(predicted[i] - expected[i], 2) * 0.5f;
    }

    return res;
}

float Model::lossD(const float *predicted, const float *expected, size_t arraySize) {

    //Using square error derivative: E(y, y')' = (y' - y')
    float res = 0;
    for (int i = 0; i < arraySize; ++i) {
        res += expected[i] - predicted[i];
    }

    return res;
}

unsigned int Model::size() {
    return static_cast<unsigned int>(layers->size());
}

unsigned int Model::getLayerSize(unsigned int i) {
    return static_cast<unsigned int>(layers->at(i)->getLayerSize());
}

float Model::deltaJ(unsigned int layer, int j, float** expected, float* predicted, int inputIndex) {
    float delta;

    Neuron *currLayerNeurons = layers->at(layer)->getLayerNeurons();

    if (layer == (size() - 1)) {
        //If it is an output neuron

        //(t - o_j)
        delta = predicted[j] - expected[inputIndex][j];
    } else {
        //It is not an output neuron
        delta = 0;

        //For all next neurons
        Neuron* nextLayerNeurons = layers->at(layer + 1)->getLayerNeurons();
        for(int l = 0; l < layers->at(layer + 1)->getLayerSize(); ++l) {
            //Get the weight that connects the next neuron to the neuron "j"
            float wjl = nextLayerNeurons[l].getPrevWeightAt(j);
            
            delta += wjl * nextLayerNeurons[l].getDelta();
        }
    }

    delta *= ActivationCalculator::calculateDerivative(SIGMOID, currLayerNeurons[j].getCurrentValue());

    //Store the value in the neuron
    currLayerNeurons[j].setDelta(delta);

    return delta;
}

