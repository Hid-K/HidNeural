#include "HidNeural.hpp"
#include "HidNeuralNetworkLearner.hpp"
#include <iostream>
#include <math.h>

double sygmoid(double x)
{
    return 1/(1+exp(-x));
};

size_t layersSizes[] = 
{
    2,
    2,
    1
};

int main()
{
    static double INPUT_DATA0[] = {1.0, 1.0};
    static double INPUT_DATA1[] = {1.0, 1.0};
    static double INPUT_DATA2[] = {1.0, 1.0};
    static double INPUT_DATA3[] = {1.0, 1.0};

    static double ** INPUT_DATA = new double * [4];

    INPUT_DATA[0] = INPUT_DATA0;
    INPUT_DATA[1] = INPUT_DATA1;
    INPUT_DATA[2] = INPUT_DATA2;
    INPUT_DATA[3] = INPUT_DATA3;

    static double OUTPUT_DATA0[] = {0.0};
    static double OUTPUT_DATA1[] = {0.0};
    static double OUTPUT_DATA2[] = {0.0};
    static double OUTPUT_DATA3[] = {1.0}; 

    static double ** OUTPUT_DATA = new double * [4];

    OUTPUT_DATA[0] = OUTPUT_DATA0;
    OUTPUT_DATA[1] = OUTPUT_DATA1;
    OUTPUT_DATA[2] = OUTPUT_DATA2;
    OUTPUT_DATA[3] = OUTPUT_DATA3;

    HidNeuralNetworkLearner_DATASET dataset;
    
    dataset.inputData = INPUT_DATA;
    dataset.outputData = OUTPUT_DATA;

    dataset.inputsCount = 2;
    dataset.outputsCount = 1;

    dataset.datasetSize = 4;

    double (*lay0funcs[])(double) =
    {
        sygmoid,
        sygmoid
    };

    double (*lay1funcs[])(double) =
    {
        sygmoid,
        sygmoid
    };

    double (*lay2funcs[])(double) =
    {
        sygmoid
    };

    double (**funcs[])(double) =
    {
        lay0funcs,
        lay1funcs,
        lay2funcs
    };

    HidNeuralNetworkLearner * learner = new HidNeuralNetworkLearner(3, &dataset, layersSizes, 2, 3, funcs);

for(;getchar() != 'q';)
    {
        learner->execGeneation();
        // if(learner->getLearningStatus() == 1)
        // {
        //     std::cout<<"Some network learned!"<<std::endl;
        // };
    };
};