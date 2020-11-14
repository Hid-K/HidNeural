#ifndef HIDNEURAL_CPP
#define HIDNEURAL_CPP

#include <iostream>
#include <math.h>

namespace HidNeural
{
	const float e = 2.718281828459045F;		//Eiler nubber constant.

	/*
		Neurons layer output structure.
	*/

	struct NeurOut
	{
		float * outputs_ptr;
		uintmax_t outputs_count;
	};

	/*
		Default activation function (sygmoid).
	*/

	float sygmoid( float arg )
	{
		return 1/(1+pow(e, -arg));
	};

	/*
		NN layer class.

		Gets activation function as a template arg.
		Gets (NeurOut) inputs, weights table and neurons count as constructor args.

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
	
	"NeurOut getOutputs()" - returns (NeurOut) structure for next layer connecting.
	
	"void setInput(NeurOut in)" - .

	"void setWeightsTable(float * table)" - .

	"void setOutputs(NeurOut ou)" - .
	*/

	template<float (*act_func)(float arg)>
	class NeuralNetworkLayer
	{
	private:
		NeurOut input;
		NeurOut output;
		float * input_weights;

	public:

		NeuralNetworkLayer(NeurOut inputs, float * weights_table, uintmax_t neurons_count)
		{
			this->input.outputs_ptr = inputs.outputs_ptr;
			this->input.outputs_count = inputs.outputs_count;

			this->input_weights = weights_table;

			this->output.outputs_ptr = new float[neurons_count];
			this->output.outputs_count = neurons_count;
		};
		~NeuralNetworkLayer()
		{
			if (*this->output.outputs_ptr) delete(this->output.outputs_ptr);
		};

		NeurOut getOutputs()
		{
			return output;
		};

		void setOutputs(NeurOut ou)
		{
			if (ou.outputs_count < this->output.outputs_count)
			{
				std::cout<<this<<":WARNING! Too small outputs array given!"<<std::endl;
				return;
			};

			this->output.outputs_ptr = ou.outputs_ptr;
		};

		void setInput(NeurOut in)
		{
			this->input.outputs_ptr = in.outputs_ptr;
			this->input.outputs_count = in.outputs_count;
		};

		void setWeightsTable(float * table)
		{
			this->input_weights = table;
		};

		void exec_data()
		{
			for (uintmax_t n = 0; n < this->output.outputs_count; ++n)
			{
				for (uintmax_t i = 0; i < this->input.outputs_count; ++i)
				{
					this->output.outputs_ptr[n] = this->input.outputs_ptr[i] * 
					*(this->input_weights + n*this->input.outputs_count + i);
				}
				this->output.outputs_ptr[n] = act_func(this->output.outputs_ptr[n]);
			};
		};
	};

	void find_out_error(float * idl, float * error_arr, NeurOut res)
	{
		for (uintmax_t o = 0; o < res.outputs_count; ++o)
		{
			error_arr[o] = idl[o] - res.outputs_ptr[o];
		};
	};

	void find_error(NeurOut input, 				NeurOut output, 
					
					float * input_lay_error, 	float * output_lay_error,

					float * input_weights)
	{
		for (uintmax_t i = 0; i < input.outputs_count; ++i)
		{
			for (uintmax_t n = 0; n < output.outputs_count; ++n)
			{
				input_lay_error[i] +=
				*(input_weights + n*input.outputs_count + i) * output_lay_error[i];
			};
		};
	};

	void weights_correction(float * input_lay_error, float * output_lay_error, float * input_weights,
							NeurOut input, NeurOut output, float k)
	{
		for (uintmax_t i = 0; i < input.outputs_count; ++i)
		{
			for (uintmax_t n = 0; n < output.outputs_count; ++n)
			{
				*(input_weights + n*input.outputs_count + i) += k * output_lay_error[n]
				* input.outputs_ptr[i] * output.outputs_ptr[n] * (1-output.outputs_ptr[n]);
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
