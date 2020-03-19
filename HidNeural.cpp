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

			 | WEIGHT_0 | WEIGHT_1 | WEIGHT_2 | . . . | WEIGHT_N |
	___________________________________________ . . . ____________
	NEURON_0 |          |          |          | . . . |          |
	___________________________________________       ____________
	NEURON_1 |          |          |          | . . . |          |
	___________________________________________       ____________
	NEURON_2 |          |          |          | . . . |          |
	___________________________________________       ____________
	NEURON_3 |          |          |          | . . . |          |
	___________________________________________       ____________
	NEURON_4 |          |          |          | . . . |          |
			 .          .          .          . . . . .          .
			 .          .          .          . . . . .          .
			 .          .          .          . . . . .          .
	___________________________________________ . . . ____________
	NEURON_N |          |          |          | . . . |          |

	weights_arr[neuron][weight];

	"void exec_data();" - executing every input by activation func and puts in into neuron output.
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
		~NeuralNetworkLayer()
		{
			if(this->input_lay_error)
			{
				delete(this->input_lay_error);
			};
		};
		
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
	};

	void find_out_error(float * idl, float * error_arr, float * res, uintmax_t outputs_count)
	{
		for (uintmax_t o = 0; o < outputs_count; ++o)
		{
			error_arr[o] = idl[o] - res[o];
		};
	};

	void find_error(float * input_lay_error, float * output_lay_error, float * input_weights,
					uintmax_t ic, 									   uintmax_t nc)
	{
		for (uintmax_t i = 0; i < ic; ++i)
		{
			input_lay_error[i] = 0;
			for (uintmax_t n = 0; n < nc; ++n)
			{
				input_lay_error[i] +=
				*(input_weights + n*ic + i) * output_lay_error[i];
			};
		};
	};

	void weights_correction(float * input_lay_error, float * output_lay_error, float * input_weights,
							float * input,			 float * output,
							uintmax_t ic, 			 uintmax_t oc,	  		   float k)
	{
		for (uintmax_t i = 0; i < ic; ++i)
		{
			for (uintmax_t n = 0; n < oc; ++n)
			{
				*(input_weights + n*ic + i) = 
				*(input_weights + n*ic + i) + k * output_lay_error[n]
				* input[i] * output[n] * (1-output[n]);
				// std::cout<<*(weights + n*ic + i);
			};
			// std::cout<<std::endl;
		}
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
