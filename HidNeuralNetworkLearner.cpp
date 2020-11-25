#include "HidNeuralNetworkLearner.hpp"

HidNeuralNetworkLearner::HidNeuralNetworkLearner
(
    size_t individualsCount,
    const HidNeuralNetworkLearner_DATASET * dataset,
    const size_t * _layersSizes,
    size_t _inputLayerSize,
    size_t _layersCount,
    double (** * actFunctions)(double)
)
:
dataset(dataset),
individualsCount(individualsCount)
{
    this->networks = (HidNeuralNetwork **)malloc(sizeof( HidNeuralNetwork *) * individualsCount );
    for(size_t net = 0; net < individualsCount; ++net)
    {
        networks[net] = new HidNeuralNetwork
        (
            _layersSizes,
            _inputLayerSize,
            _layersCount,
            actFunctions
        );
    };
    this->networksErrorsList = new double[this->individualsCount];
    this->networksErrorsNumbersList = new size_t[this->individualsCount];
};
HidNeuralNetworkLearner::~HidNeuralNetworkLearner()
{
    delete this->networks;
    delete this->networksErrorsList;
    delete this->networksErrorsNumbersList;
};

void
HidNeuralNetworkLearner::execGeneation()
{
    size_t datasetNumber = rand() % this->dataset->datasetSize;

    for(size_t i = 0; i < this->individualsCount; ++i)
    {
        for(size_t in = 0; in < this->dataset->inputsCount; ++in)
        {
            this->networks[i]->getIntput()[in] = this->dataset->inputData[datasetNumber][in];
        };
        this->networks[i]->executeInput();
    };

    for(size_t i = 0; i < this->individualsCount; ++i)
    {
        std::cout<<"Layer #"<<i<<':'<<std::endl;
        double layerError = 0.0;
        for(size_t out = 0; out < this->dataset->outputsCount; ++out)
        {
            std::cout<<"Output #"<<out<<' '<< this->networks[i]->getOutput()[out]<<std::endl;
            std::cout<<"Error: "<<abs(this->dataset->outputData[datasetNumber][out] - this->networks[i]->getOutput()[out])
                <<std::endl;
            layerError += abs(this->dataset->outputData[datasetNumber][out] - this->networks[i]->getOutput()[out]);
        };
        layerError /= this->dataset->outputsCount;
        this->networksErrorsList[i] = layerError;
        networksErrorsNumbersList[i] = i;
    };

    for (size_t step = 0; step < this->individualsCount - 1; ++step)
    {
        for (size_t i = 0; i < this->individualsCount - step - 1; ++i)
        {
            if (this->networksErrorsList[i] > this->networksErrorsList[i + 1])
            {

                double temp = this->networksErrorsList[i];
                this->networksErrorsList[i] = this->networksErrorsList[i + 1];
                this->networksErrorsList[i + 1] = temp;

                size_t buf = this->networksErrorsNumbersList[i];
                this->networksErrorsNumbersList[i] = this->networksErrorsNumbersList[i + 1];
                this->networksErrorsNumbersList[i + 1] = buf;
            };
        };
    };

    // if(this->networksErrorsList[0] == 0)
    // {
    //     this->learningStatus = 1;
    //     return;
    // };

    networks[this->networksErrorsNumbersList[0]]->merge(networks[this->networksErrorsNumbersList[1]]);
    
    for(size_t n = 0; n < this->individualsCount; ++n)
    {
        if(n != this->networksErrorsNumbersList[0])
        {
            networks[n]->copy(networks[this->networksErrorsNumbersList[0]]);
        };
        networks[n]->mutate(this->networksErrorsNumbersList[n]);
    };
};

void
HidNeuralNetworkLearner::execGeneations(size_t t)
{
    for(; t > 0; --t) this->execGeneation();
};