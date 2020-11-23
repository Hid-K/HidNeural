#include "HidNeural.hpp"

HidNeural::HidNeural
        (
            const size_t * _layersSizes,
            size_t _inputLayerSize,
            size_t _layersCount,
            double (** * actFunctions)(double)
        )
        :
        layersCount(_layersCount),
        neuronsActivationFunctions(actFunctions),
        layersSizesArr(_layersSizes),
        inputLayerSize(_inputLayerSize)
{
    srand(time(nullptr));
    this->inputLayer = new double [inputLayerSize];
    /*
        Weights table init.
    */
    this->weightsTables = new double ** [layersCount];

    this->weightsTables[0] = new double * [this->layersSizesArr[0]];
    
    for(size_t i = 0; i < this->layersSizesArr[0]; ++i)
    {
        srand(time(nullptr));
        this->weightsTables[0][i] = new double[inputLayerSize];
        for(size_t w = 0; w < this->inputLayerSize; ++w)
        {
            this->weightsTables[0][i][w] = 1/( rand() % 3 + 0.5 );
        };
    };
    
    for(size_t layer = 1; layer < this->layersCount; ++layer)
    {
        srand(time(nullptr));
        this->weightsTables[layer] = new double * [this->layersSizesArr[layer]];
        for(size_t neuron = 0; neuron < this->layersSizesArr[layer]; ++neuron)
        {
            srand(time(nullptr));
            this->weightsTables[layer][neuron] = new double [this->layersSizesArr[layer-1]];
            for(size_t w = 0; w < this->layersSizesArr[layer-1]; ++w)
            {
                this->weightsTables[layer][neuron][w] = 1/( rand() % 3 + 0.5 );
            };
        };
    };

    /*
        Layers outputs init.
    */
   this->layersOutputs = new double * [layersCount];
   
   for(size_t layer = 0; layer < layersCount; ++layer)
   {
       this->layersOutputs[layer] = new double [this->layersSizesArr[layer]];
   };
};
HidNeural::~HidNeural()
{
    for(size_t layer = 0; layer < layersCount; ++layer)
   {
       delete this->layersOutputs[layer];
   };
   delete this->layersOutputs;

   for(size_t layer = 0; layer < this->layersCount; ++layer)
    {
        for(size_t neuron = 0; neuron < this->layersSizesArr[layer]; ++neuron)
        {
            delete this->weightsTables[layer][neuron];
        };
        delete this->weightsTables[layer];
    };

    delete this->weightsTables;
    delete this->inputLayer;
};

double *
HidNeural::getOutput()
{
    return this->layersOutputs[layersCount - 1];
};

double *
HidNeural::getIntput()
{
    return this->inputLayer;
};

char
HidNeural::getWeight(size_t layer, size_t neuron, size_t w, double & weight_var)
{
    if(layer == 0 && neuron < this->layersSizesArr[0] && w < this->inputLayerSize)
    {
        weight_var = this->weightsTables[layer][neuron][w];
        return 0;
    } else
        if(neuron >= this->layersSizesArr[0] || w >= this->inputLayerSize)
    {
        return -1;
    } else
        if(layer < this->layersCount &&
              neuron < this->layersSizesArr[layer] &&
              w < this->layersSizesArr[layer -1 ])
    {
        weight_var = this->weightsTables[layer][neuron][w];
        return 0;
    } else
    {
        return -1;
    };
};

char
HidNeural::setWeight(size_t layer, size_t neuron, size_t w, double & weight_var)
{
    if(layer == 0 && neuron < this->layersSizesArr[0] && w < this->inputLayerSize)
    {
        this->weightsTables[layer][neuron][w] = weight_var;
        return 0;
    } else
        if(neuron >= this->layersSizesArr[0] || w >= this->inputLayerSize)
    {
        return -1;
    } else
        if(layer < this->layersCount &&
              neuron < this->layersSizesArr[layer] &&
              w < this->layersSizesArr[layer -1 ])
    {
        this->weightsTables[layer][neuron][w] = weight_var;
        return 0;
    } else
    {
        return -1;
    };
};

char
HidNeural::copy(HidNeural * parent_network)
{
    for(size_t layer = 1; layer < this->layersCount; ++layer)
    {
        for(size_t neuron = 0; neuron < this->layersSizesArr[layer]; ++neuron)
        {
            double weight = 0.0;
            for(size_t input = 0; input < this->layersSizesArr[layer - 1]; ++input)
            {
                if( this->getWeight(layer, neuron, input, weight) < 0 ||
                    parent_network->setWeight(layer, neuron, input, weight) < 0)
                    goto ERROREXIT;
            };
        };
    };
    return 0;
    ERROREXIT:
    return -1;
};

void
HidNeural::executeInput()
{
    for(size_t neuron = 0; neuron < this->layersSizesArr[0]; ++neuron)
    {
        double inputsSumm = 0.0;
        for(size_t input = 0; input < inputLayerSize; ++input)
        {
            inputsSumm +=
                this->inputLayer[input] *
                this->weightsTables[0][neuron][input];
            std::cout<<this->weightsTables[0][neuron][input]<<std::endl;
        };
        std::cout<<std::endl<<inputsSumm<<std::endl;
        this->layersOutputs[0][neuron] =
            this->neuronsActivationFunctions[0][neuron](inputsSumm);
        std::cout<<std::endl;
    };
    std::cout<<std::endl<<std::endl;

    for(size_t layer = 1; layer < this->layersCount; ++layer)
    {
        for(size_t neuron = 0; neuron < this->layersSizesArr[layer]; ++neuron)
        {
            double inputsSumm = 0.0;
            for(size_t input = 0; input < this->layersSizesArr[layer - 1]; ++input)
            {
                inputsSumm +=
                    this->layersOutputs[layer-1][input] *
                    this->weightsTables[layer][neuron][input];
                
                std::cout<<this->weightsTables[layer][neuron][input]<<std::endl;
            };
            std::cout<<std::endl<<inputsSumm<<std::endl;
            this->layersOutputs[layer][neuron] =
                this->neuronsActivationFunctions[layer][neuron](inputsSumm);
            std::cout<<std::endl;
        };
        std::cout<<std::endl<<std::endl;
    };
};