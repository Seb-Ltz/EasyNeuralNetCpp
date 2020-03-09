//
// Created by Sébastien Letzelter on 29.02.20.
//

#include "ActivationFunction.h"
#include <algorithm>
#include <cmath>

const float ActivationCalculator::calculate(ACTIVATION_FUNCTION activationFunction, float x) {
    switch (activationFunction) {
        case RELU:
            return std::max(0.f,x);
        case SIGMOID:
            return 1.f / (1.f + std::exp(-x));
        default:
            return -1.0f;
    }
}

const float ActivationCalculator::calculateDerivative(ACTIVATION_FUNCTION activationFunction, float x) {
    switch (activationFunction) {
        case RELU:
            if(x <= 0) return 0;
            else return 1;
        case SIGMOID:
            return calculate(SIGMOID, x) * (1 - calculate(SIGMOID, x));
        default:
            return -1.0f;
    }
}
