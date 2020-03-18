#ifndef HIDNEURAL_CPP
#define HIDNEURAL_CPP

#include <iostream>
#include <math.h>

float LEARN_CO = 0.0f;

namespace NeuralNet
{
	const float e = 2.718281828459045F;		//Eiler nubber constant.

	/*
		Default activation function (sygmoid).
	*/

	float sygmoid( float arg )
	{
		return 1/(1+pow(e, arg));
	};

	/*
		NN layer class.

		Gets neurons count and activation function as a template.
		Gets pointer to inputs array, pointer to weights, count of inputs, pointer to output array
		as constructor args.

		Inputs weights table are structured like:

			 | WEIGHT_0 | WEIGHT_1 | WEIGHT_2 |. . . | WEIGHT_N |
	___________________________________________. . . ____________
	NEURON_0 |          |          |          |. . . |          |
	___________________________________________      ____________
	NEURON_1 |          |          |          |. . . |          |
	___________________________________________      ____________
	NEURON_2 |          |          |          |. . . |          |
	___________________________________________      ____________
	NEURON_3 |          |          |          |. . . |          |
	___________________________________________      ____________
	NEURON_4 |          |          |          |. . . |          |
			 .          .          .          . . . .           .
			 .          .          .          . . . .           .
			 .          .          .          . . . .           .
	___________________________________________ . . .____________
	NEURON_N |          |          |          |. . . |          |

	"void exec_data();" - executing every input by activation func and puts in into neuron output.

	"void weights_correction(float k);" - correcting last layer weights for every neuron.
	*/

	template<float (*act_func)(float arg)>
	class NeuralNetworkLayer
	{
	private:
		float *  inputs;
		float *  inputs_correction;
		uintmax_t inputs_count;
		uintmax_t neurons_count;
		float * outputs;

	public:
		float * input_lay_error;

		NeuralNetworkLayer(float * input, float *input_weights, uintmax_t input_count,
						   float * output, uintmax_t neurons_count)
		{
			this->inputs = 				input;
			this->inputs_correction = 	input_weights;
			this->inputs_count = 		input_count;
			this->outputs = 			output;
			this->neurons_count	=		neurons_count;
			this->input_lay_error = new float[this->inputs_count];
		};
		~NeuralNetworkLayer(){};
		
		void exec_data()
		{
			for (uintmax_t n = 0; n < this->neurons_count; ++n)
			{
				this->outputs[n] = 0;
				for (uintmax_t i = 0; i < this->inputs_count; ++i)
				{
					this->outputs[n] += this->inputs[i] * *(this->inputs_correction + n*this->inputs_count + i);
				}
				this->outputs[n] = act_func(this->outputs[n]);
			};
		};

		void weights_correction(float k, float * output_neuron_error)
		{
			for (uintmax_t i = 0; i < this->inputs_count; ++i)
			{
				for (uintmax_t n = 0; n < this->neurons_count; ++n)
				{
					*(this->inputs_correction + n*this->inputs_count + i) = 
					*(this->inputs_correction + n*this->inputs_count + i) + k * output_neuron_error[n]
					* this->outputs[n] * (1-this->outputs[n]) * this->inputs[i];
				}
			}
		}

		void find_error(float * output_lay_error)
		{
			for (uintmax_t i = 0; i < this->inputs_count; ++i)
			{
				this->input_lay_error[i]=0;
				for (int n = 0; n < this->neurons_count; ++n)
				{
					this->input_lay_error[i] = 
					*(this->inputs_correction + n*this->inputs_count + i) * output_lay_error[i];
				};
			};
		};
	};

	/*
		Single neuron class;

		Gets activation function as a template arg.

		Gets pointer to inputs array, pointer to weights, count of inputs, link to output
		as constructor args.

		Weights are just single dimention array.
	*/

	template< float ( *act_func )( float arg ) >
	class Neuron
	{
	private:
		float * 	last_layer;
		float * 	last_layer_weights;
		uintmax_t 	inputs_count;
		float & 	output;

	public:
		Neuron( float * last_layer_ptr, float * last_layer_weights_ptr, uintmax_t inputs_count_a,
				float &output_l )
		{
			this->last_layer = last_layer_ptr;
			this->last_layer_weights = last_layer_weights_ptr;
			this->inputs_count = inputs_count_a;
			this->output = output_l;
		};
		~Neuron(){};

		void set_input( float * in, float * w, uintmax_t count)
		{
			this->last_layer = in;
			this->last_layer_weights = w;
			this->inputs_count = count;
		};

		void set_output( float & o )
		{
			this->output = o;
		}
		
		void exec_data()
		{
			output = 0;
			for (uintmax_t i = 0; i < this->inputs_count; ++i)
			{
				output += this->last_layer[i] * this->last_layer_weights[i];
			};
			output = act_func(output);
		};
	};

};

#endif
