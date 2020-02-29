//
// Created by Sébastien Letzelter on 28.02.20.
//

#ifndef NEURALNETWORKS_LAYER_H
#define NEURALNETWORKS_LAYER_H

#include "SuperLayer.h"
#include "../ActivationFunction.h"


class HiddenLayer : public SuperLayer {

public:
    HiddenLayer(int neuronNb, ACTIVATION_FUNCTION activation_function);

    LAYER_TYPE getLayerType() const override;

    void compile() override;

private:

};


#endif //NEURALNETWORKS_LAYER_H
