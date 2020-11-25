#ifndef HIDNERURALNETWORKLEANER_HPP
#define HIDNERURALNETWORKLEANER_HPP

#include <stddef.h>
#include <iostream>

#include "HidNeural.hpp"

struct HidNeuralNetworkLearner_DATASET
{
    double ** inputData;
    double ** outputData;
    size_t inputsCount;
    size_t outputsCount;

    size_t datasetSize;
};


class HidNeuralNetworkLearner
{
private:
    HidNeuralNetwork ** networks;
    const HidNeuralNetworkLearner_DATASET * dataset;
    size_t individualsCount;
    double * networksErrorsList;
    size_t * networksErrorsNumbersList;
    char learningStatus = -1;
public:
    HidNeuralNetworkLearner
    (
        size_t individualsCount,
        const HidNeuralNetworkLearner_DATASET * dataset,
        const size_t * _layersSizes,
        size_t _inputLayerSize,
        size_t _layersCount,
        double (** * actFunctions)(double)
    );
    ~HidNeuralNetworkLearner();

    void execGeneation();
    void execGeneations(size_t);

    char getLearningStatus(){return this->learningStatus;};

    HidNeuralNetwork * getNetwork(size_t n){return this->networks[n];};
};


#endif