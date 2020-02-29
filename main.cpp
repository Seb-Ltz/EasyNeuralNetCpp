#include <iostream>
#include "Model.h"
#include "Layers/InputLayer.h"
#include "Data.h"
int main() {
    Model model;
    model.add(new InputLayer(784));
    model.add(new HiddenLayer(64, ACTIVATION_FUNCTION::RELU));
    model.add(new HiddenLayer(10, ACTIVATION_FUNCTION::RELU));

    model.compile();


    float** predicted = model.predict(Data().testInput);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}