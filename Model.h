//
// Created by Sébastien Letzelter on 28.02.20.
//

#ifndef NEURALNETWORKS_MODEL_H
#define NEURALNETWORKS_MODEL_H

#include <vector>
#include "Layers/HiddenLayer.h"

class Model {
public:
    Model();
    /**
     * Adds a layer to the Neural Network Model
     * @param layer Layer to add
     */
    void add(SuperLayer* layer);

    /**
     * "Compiling" the model gives the Layers all informations needed for the training
     */
    void compile();

    /**
     * Trains the input using backpropagation
     * @param input Input data to train the model on
     */
    void fit(float** input, float** expected, size_t arraySize, int epochs, int batch_size);

    /**
     * Once the Model got trained, call this function to predict new values
     * @param input A 2D array of values to predict
     * @return a 2D array of the predicted values
     */
    float** predict(float** input, size_t inputSize);

    /**
     * @return The amount of layers that are in the models
     */
    unsigned int size();

    /**
     * @param i Position of the layer to see the amount of neurons of.
     * @return The amounts of neurons in the layer at position i
     */
    unsigned int getLayerSize(unsigned int i);

    static constexpr float LEARNING_RATE = 0.5f;
private:
    std::vector<SuperLayer*>* layers;
    /**
     * Predicts one time
     * @param input an array of values to predict
     * @return an array of the predicted value
     */
    float* predictOnce(float* input);

    /**
     * Calculates the loss using the square error between the predicted and expected values of the neural network.
     * @param predicted Predicted values from the neural network
     * @param expected Expected values
     * @return the value of the loss function
     */
    float loss(const float* predicted, const float* expected, size_t arraySize);

    /**
     * Calculates the value of the derivative of the square error loss function.
     * @param predicted Predicted values from the neural network
     * @param expected Expected values
     * @return the value of the derivative of the loss function
     */
    float lossD(const float* predicted, const float* expected, size_t arraySize);

    float deltaJ(unsigned int layer, int j, float** expected, float* predicted, int inputIndex);

    //Used to get info about the other layers
    Model* model;
};


#endif //NEURALNETWORKS_MODEL_H
