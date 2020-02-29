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
    void fit(float** input);

    /**
     * Once the Model got trained, call this function to predict new values
     * @param input A 2D array of values to predict
     * @return a 2D array of the predicted values
     */
    float** predict(float input[]);

private:
    std::vector<SuperLayer*>* layers;

    //Used to get info about the other layers
    Model* model;
    const float LEARNING_RATE = 0.5;
};


#endif //NEURALNETWORKS_MODEL_H
