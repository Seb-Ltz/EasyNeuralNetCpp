#include <iostream>
#include "Model.h"
#include "Layers/InputLayer.h"
#include "Data.h"

/**
 * Maps the numbers between 0-9 to an array of length 10 with 9 zeroes and a one.
 * @return
 */
float** const mapNumbers(float* arr, size_t arrSize) {
    auto** result = new float*[arrSize];
    for (int i = 0; i < arrSize; ++i) {
        float x = arr[i];
        auto* temp = new float[10];
        temp[static_cast<int>(x)] = 1.f;
        result[i] = temp;
    }
    return result;
}

/**
 * Makes all floats in the 2D array from 0-255 to 0-1
 * @return a new 2D Array with values only between 0 and 1
 */
void normalizeArr(float** arr, size_t arrSize, size_t elemSize) {
    for(int i = 0; i < arrSize; ++i) {
        for (int j = 0; j < elemSize; ++j) {
            arr[i][j] /= 255;
        }
    }
}

int main() {

    Model model;
    model.add(new InputLayer(784));
    model.add(new HiddenLayer(64, ACTIVATION_FUNCTION::SIGMOID));
    model.add(new HiddenLayer(10, ACTIVATION_FUNCTION::SIGMOID));

    model.compile();

    //Load the datasets
    Data trainX("Datasets/MNIST_Train_x-ubyte");
    Data trainY("Datasets/MNIST_Train_y-ubyte");

    Data testX("Datasets/MNIST_Test_x-ubyte");
    Data testY("Datasets/MNIST_Test_y-ubyte");

    //Map the trainX and testX data from 0-255 --> 0-1
    float** parsedTrainX = trainX.parseTo2D(0x016, 60000, 28*28);
    normalizeArr(parsedTrainX, 60000, 28*28);
    float** parsedTestX = testX.parseTo2D(0x16, 60000, 28*28);
    normalizeArr(parsedTestX, 10000, 28*28);

    float* parsedTrainY = trainY.parseTo1D(0x08, 60000);
    float* parsedTestY = testY.parseTo1D(0x08, 10000);

    //Train the model
    int batch_size = 10000;
    int epochs = 10;
    model.fit(parsedTrainX, mapNumbers(parsedTrainY, 60000), 60000, epochs, batch_size);

    //Predict new models
    float** predicted = model.predict(parsedTestX, 10000);


    //Print the 10 first results
    for(int i = 0; i < 10; i++) {
        std::cout << i << ":  ";
        for(int j = 0; j < 10; j++) {
            std::cout << predicted[i][j] << " ; ";
        }
        std::cout << "Target = " << parsedTestY[i];
        std::cout << std::endl;
    }


    //Calculate accuracy
    float accuracy = 0;
    for(int i = 0; i < 10000; ++i) {

        //Get the max value of the array
        float maxVal = 0;
        int maxValI = -1;
        for(int j = 0; j < 10; ++j) {
            if(predicted[i][j] > maxVal || maxValI == -1) {
                maxVal = predicted[i][j];
                maxValI = j;
            }
        }
        if(maxValI == parsedTestY[i])
            accuracy++;
    }
    accuracy /= 100;
    std::cout << accuracy << "%" << std::endl;

    return 0;
}