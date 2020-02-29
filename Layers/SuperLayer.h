//
// Created by Sébastien Letzelter on 29.02.20.
//

#ifndef NEURALNETWORKS_SUPERLAYER_H
#define NEURALNETWORKS_SUPERLAYER_H


#include "../Neuron.h"

enum LAYER_TYPE {
    INPUT,
    HIDDEN
};

class SuperLayer {
public:
    SuperLayer(int neuronNb);

    /**
     * @return the numbers of Neurons in the layer
     */
    int getLayerSize() const;

    virtual ~SuperLayer();

    virtual LAYER_TYPE getLayerType() const = 0;

    virtual void compile() = 0;

    SuperLayer *getPrevLayer() const;
    void setPrevLayer(SuperLayer *prevLayer);

    SuperLayer *getNextLayer() const;
    void setNextLayer(SuperLayer *nextLayer);

    void calculateNeurons();
protected:
    SuperLayer* prevLayer;
    SuperLayer* nextLayer;
    Neuron* layerNeurons;
private:
    int layerSize;
};


#endif //NEURALNETWORKS_SUPERLAYER_H
