cmake_minimum_required(VERSION 3.12)
project(EasyNeuralNet)

set(CMAKE_CXX_STANDARD 14)

add_executable(EasyNeuralNet main.cpp Layers/HiddenLayer.cpp Layers/HiddenLayer.h Model.cpp Model.h Neuron.cpp Neuron.h Layers/SuperLayer.cpp Layers/SuperLayer.h Layers/InputLayer.cpp Layers/InputLayer.h Data.cpp Data.h ActivationFunction.h ActivationFunction.cpp)