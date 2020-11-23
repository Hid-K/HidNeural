#ifndef HIDNERURAL_HPP
#define HIDNERURAL_HPP

#include <stddef.h>
#include <random>
#include <ctime>
#include <iostream>

class HidNeural
{
private:
    double *** weightsTables;
    
    double * inputLayer;
    double ** layersOutputs;

    const size_t * layersSizesArr;
    size_t inputLayerSize;
    size_t layersCount;
    double (** * neuronsActivationFunctions)(double);
public:
    HidNeural
            (
              const size_t * _layersSizes,
              size_t _inputLayerSize,
              size_t _layerCount,
              double (** * actFunctions)(double)
            );
    ~HidNeural();

    double * getOutput();
    double * getIntput();

    void executeInput();

    char getWeight(size_t layer, size_t neuron, size_t w, double & weight_var);
    char setWeight(size_t layer, size_t neuron, size_t w, double & weight_var);

    char copy(HidNeural *);
};

#endif