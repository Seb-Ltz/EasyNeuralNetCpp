//
// Created by Sébastien Letzelter on 29.02.20.
//

#ifndef NEURALNETWORKS_INPUTLAYER_H
#define NEURALNETWORKS_INPUTLAYER_H


#include "SuperLayer.h"

class InputLayer : public SuperLayer {
public:
    InputLayer(int neuronNb);

    LAYER_TYPE getLayerType() const override;

    void compile() override;

    void initNeurons(float input[]);
};


#endif //NEURALNETWORKS_INPUTLAYER_H
