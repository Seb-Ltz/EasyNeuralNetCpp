//
// Created by Sébastien Letzelter on 29.02.20.
//

#ifndef NEURALNETWORKS_ACTIVATIONFUNCTION_H
#define NEURALNETWORKS_ACTIVATIONFUNCTION_H

enum ACTIVATION_FUNCTION {
        RELU,
        SIGMOID,
        TANH,
        LINEAR,
        LEAKY_RELU,
};

class ActivationCalculator {
public:
    static const float calculate(ACTIVATION_FUNCTION activationFunction, float x);
};

#endif //NEURALNETWORKS_ACTIVATIONFUNCTION_H
