#include <iostream>
#include <math.h>

float LEARN_CO = 0.0f;

namespace NeuralNet
{
	const float e = 2.718281828459045f;

	template<uintmax_t neuron_count>
	class NeuralNetworkLayer
	{
	private:
		float *  inputs;
		float *  inputs_correction;
		uintmax_t inputs_count;
		uintmax_t neurons_count;

		float * outputs;

	public:
		NeuralNetworkLayer(float * input, float *input_weights, uintmax_t input_count,
						   float * output)
		{
			this->inputs = 				input;
			this->inputs_correction = 	input_weights;
			this->inputs_count = 		input_count;
			this->outputs = 			output;
			this->neurons_count	=		neuron_count;
		};
		~NeuralNetworkLayer(){};
		
		void exec_data()
		{
			for (uintmax_t n = 0; n < this->neurons_count; ++n)
			{
				for (uintmax_t i = 0; i < this->inputs_count; ++i)
				{
					// std::cout<<*(inputs_correction + n*inputs_count + i);
					this->outputs[n] = 0;
					this->outputs[n] += this->inputs[i] * *(this->inputs_correction + n*this->inputs_count + i);
				}
				// std::cout<<std::endl;
				this->outputs[n] = 1/(1+pow(e, this->outputs[n]));
			}
		};

		void weights_correction(float k)
		{
			for (uintmax_t i = 0; i < this->inputs_count; ++i)
			{
				for (uintmax_t n = 0; n < this->neurons_count; ++n)
				{
					*(this->inputs_correction + n*this->inputs_count + i) = 
					*(this->inputs_correction + n*this->inputs_count + i) + k * this->outputs[n]
					* this->outputs[n] * (1-this->outputs[n]) * this->inputs[i];
				}
			}
		}
	};
};

float NNinput[2] =				  {0.0f, 0.0f};
float NNinput_correction[2][2] = {{1.0f, 1.0f},
							      {1.0f, 1.0f}};

float input_lay_out[2] =  	    {0.0f, 0.0f};
float input_lay_weights[2][3] = {{1.0f, 1.0f, 1.0f},
							   	 {1.0f, 1.0f, 1.0f}};

float lay1out[3] =  	   {0.0f, 0.0f, 0.0f};
float lay1weights[3][3] = {{1.0f, 1.0f, 1.0f},
						   {1.0f, 1.0f, 1.0f},
						   {1.0f, 1.0f, 1.0f}};

float lay2out[3] =  	   {0.0f, 0.0f, 0.0f};
float lay2weights[3][3] = {{1.0f, 1.0f, 1.0f},
						   {1.0f, 1.0f, 1.0f},
						   {1.0f, 1.0f, 1.0f}};

float NNoutput[1] = {0.0f};

// NeuralNet::NeuralNetworkLayer<2> NNinput1(NNinput, (float*)NNinput_correction, 2, input_lay_out);

// NeuralNet::NeuralNetworkLayer<3> NNlay1(input_lay_out, (float*)input_lay_weights, 2, lay1out);

NeuralNet::NeuralNetworkLayer<2> NNlay2(NNinput, (float*)NNinput_correction, 2, lay2out);

NeuralNet::NeuralNetworkLayer<1> NNoutput1(lay2out, (float*)lay2weights, 2, NNoutput);

int main(int argc, char const *argv[])
{
	float test0 = 0.0f;
	float test1 = 0.0f;
	float test2 = 0.0f;
	float test3 = 0.0f;
	if (argc > 0)
	{
		LEARN_CO = (float)argv[0][0];
	}
	for (;;)
	{
		// printf("\033" "[2J");

		NNinput[0] = 0.0f;
		NNinput[1] = 0.0f;

		// NNinput1.exec_data();
		// NNlay1.exec_data();
		NNlay2.exec_data();
		NNoutput1.exec_data();

		test0 = NNoutput[0];

		std::cout<<NNoutput[0]<<std::endl;

		NNinput[0] = 1.0f;
		NNinput[1] = 0.0f;

		// NNinput1.exec_data();
		// NNlay1.exec_data();
		NNlay2.exec_data();
		NNoutput1.exec_data();

		test1 = NNoutput[0];

		std::cout<<NNoutput[0]<<std::endl;

		NNinput[0] = 0.0f;
		NNinput[1] = 1.0f;

		// NNinput1.exec_data();
		// NNlay1.exec_data();
		NNlay2.exec_data();
		NNoutput1.exec_data();

		test2 = NNoutput[0];

		std::cout<<NNoutput[0]<<std::endl;

		NNinput[0] = 1.0f;
		NNinput[1] = 1.0f;

		// NNinput1.exec_data();
		// NNlay1.exec_data();
		NNlay2.exec_data();
		NNoutput1.exec_data();

		test3 = NNoutput[0];

		std::cout<<NNoutput[0]<<std::endl;
		std::cout<<std::endl;
		if (test0 == 0.0f && test1 == 1.0f && test2 == 1.0f && test3 == 1.0f)	//If network learned correctly rinting all weights:
		{
			std::cout<<std::endl;
			std::cout<<"Input lay weights:"<<std::endl;
			for (int n = 0; n < sizeof(input_lay_weights)/sizeof(*input_lay_weights); ++n)
			{
				for (int i = 0; i < sizeof(input_lay_weights[0])/sizeof(*input_lay_weights[0]); ++i)
				{
					std::cout<<input_lay_weights[n][i];
				}
				std::cout<<std::endl;
			}

			std::cout<<std::endl;
			std::cout<<"Lay 1 weights:"<<std::endl;
			for (int n = 0; n < sizeof(lay1weights)/sizeof(*lay1weights); ++n)
			{
				for (int i = 0; i < sizeof(lay1weights[0])/sizeof(*lay1weights[0]); ++i)
				{
					std::cout<<lay1weights[n][i];
				}
				std::cout<<std::endl;
			}

			std::cout<<std::endl;
			std::cout<<"Lay 2 weights:"<<std::endl;
			for (int n = 0; n < sizeof(lay2weights)/sizeof(*lay2weights); ++n)
			{
				for (int i = 0; i < sizeof(lay2weights[0])/sizeof(*lay2weights[0]); ++i)
				{
					std::cout<<lay2weights[n][i];
				}
				std::cout<<std::endl;
			}

			break;
		} else		//If network learned wrong trying to fing error and correct weights
		{
			// NNinput1.weights_correction(LEARN_CO);
			// NNlay1.weights_correction(LEARN_CO);
			NNlay2.weights_correction(LEARN_CO);
			NNoutput1.weights_correction(LEARN_CO);
		};
		if (test0 < 0 || test1 < 0 || test2 < 0 || test3 < 0)
		{
			return 0;
		}
	}
	return 0;
};