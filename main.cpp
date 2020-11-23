#include "HidNeural.hpp"
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

    HidNeuralNetwork * network = new HidNeuralNetwork(layersSizes, 2, 3, funcs);

    network->getIntput()[0] = 1234729346.23468127634;
    network->getIntput()[1] = 125987498723.2347243;

    network->executeInput();

    std::cout<<network->getOutput()[0]<<std::endl;
};