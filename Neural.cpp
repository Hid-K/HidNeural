#include <iostream>
#include "HidNeural.cpp"
#include <cstdlib>

float NNinput[9] =				  		  {0.0F, 0.0F, 0.0F,
								   0.0F, 0.0F, 0.0F,
								   0.0F, 0.0F, 0.0F};

float NNinput_correction[4][9]/* = {{1.0f, 1.0f, 1.0f,
								   1.0f, 1.0f, 1.0f,
								   1.0f, 1.0f, 1.0f},
								  
								  {1.0f, 1.0f, 1.0f,
								   1.0f, 1.0f, 1.0f,
								   1.0f, 1.0f, 1.0f},
								  
								  {1.0f, 1.0f, 1.0f,
								   1.0f, 1.0f, 1.0f,
								   1.0f, 1.0f, 1.0f},
								  
								  {1.0f, 1.0f, 1.0f,
								   1.0f, 1.0f, 1.0f,
								   1.0f, 1.0f, 1.0f}}*/;

float NNlay0_out[4] {0.0F, 0.0F, 0.0F, 0.0F};

float NNlay0_weights[3][4];


float NNlay1_out[] {0.0F, 0.0F, 0.0F};

float NNlay1_weights[2][3];


float NNoutput[2] = {0.0F, 0.0F};		//1 - vertical
										//2 - horizontal

float ideat_out[14][2] {{0.0F, 0.0F},				//0 0

					    	{1.0F, 0.0F},				//1 0

					    	{0.0F, 1.0F},				//0 1
					    
					    	{0.0F, 1.0F},				//0 1

						{0.0F, 1.0F},				//0 1
						
						{1.0F, 0.0F},				//1 0
						
						{1.0F, 0.0F},				//1 0
						
						{1.0F, 1.0F},				//1 1
						
						{1.0F, 1.0F},				//1 1

						{1.0F, 1.0F},				//1 1

						{1.0F, 1.0F},				//1 1

						{1.0F, 1.0F},				//1 1

						{1.0F, 1.0F},				//1 1

						{1.0F, 1.0F}};				//1 1

float input_options[14][9] {				{0.0f, 0.0f, 0.0f,
							 0.0f, 0.0f, 0.0f,				//0 0
							 0.0f, 0.0f, 0.0f},
							
							{1.0f, 0.0f, 0.0f,
							 1.0f, 0.0f, 0.0f,				//1 0
							 1.0f, 0.0f, 0.0f},
							
							{1.0f, 1.0f, 1.0f,
							 0.0f, 0.0f, 0.0f,				//0 1
							 0.0f, 0.0f, 0.0f},
							
							{0.0f, 0.0f, 0.0f,
							 1.0f, 1.0f, 1.0f,				//0 1
							 0.0f, 0.0f, 0.0f},
							
							{0.0f, 0.0f, 0.0f,
							 0.0f, 0.0f, 0.0f,				//0 1
							 1.0f, 1.0f, 1.0f},
							
							{0.0f, 1.0f, 0.0f,
							 0.0f, 1.0f, 0.0f,				//1 0
							 0.0f, 1.0f, 0.0f},
							
							{0.0f, 0.0f, 1.0f,
							 0.0f, 0.0f, 1.0f,				//1 0
							 0.0f, 0.0f, 1.0f},
							
							{1.0f, 1.0f, 1.0f,
							 1.0f, 0.0f, 0.0f,				//1 1
							 1.0f, 0.0f, 0.0f},
							
							{0.0f, 1.0f, 0.0f,
							 1.0f, 1.0f, 1.0f,				//1 1
							 0.0f, 1.0f, 0.0f},
							
							{0.0f, 0.0f, 1.0f,
							 1.0f, 1.0f, 1.0f,				//1 1
							 0.0f, 0.0f, 1.0f},
							
							{1.0f, 1.0f, 1.0f,
							 0.0f, 1.0f, 0.0f,				//1 1
							 0.0f, 1.0f, 0.0f},
							
							{0.0f, 1.0f, 0.0f,
							 0.0f, 1.0f, 0.0f,				//1 1
							 1.0f, 1.0f, 1.0f},
							
							{0.0f, 0.0f, 1.0f,
							 0.0f, 0.0f, 1.0f,				//1 1
							 1.0f, 1.0f, 1.0f},
							
							{0.0f, 1.0f, 0.0f,
							 0.0f, 1.0f, 0.0f,				//1 1
							 1.0f, 1.0f, 1.0f}};

NeuralNet::NeuralNetworkLayer<NeuralNet::sygmoid> NNlay0(NNinput, (float*)NNinput_correction, 9, NNlay0_out, 4);

NeuralNet::NeuralNetworkLayer<NeuralNet::sygmoid> NNlay1(NNlay0_out, (float*)NNlay0_weights, 4, NNlay1_out, 3);

NeuralNet::NeuralNetworkLayer<NeuralNet::sygmoid> NNout(NNlay1_out, (float*)NNlay1_weights, 3, NNoutput, 2);

int main(int argc, char const *argv[])
{
	float test0 = 0.0f;
	float test1 = 0.0f;
	float test2 = 0.0f;
	float test3 = 0.0f;
	if (argc > 0)
	{
		LEARN_CO = (float)argv[0][0];
	};
	int qwe = 0;
	for(;;)
	{
		qwe ++;
		bool tests_result[14]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		for (int v = 0; v < 14; ++v)
		{
			for (uintmax_t i = 0; i < 9; ++i)
			{
				NNinput[i] = input_options[v][i];
			};

			NNlay0.exec_data();
			NNlay1.exec_data();
			NNout.exec_data();

			std::cout<<NNoutput[0]<<" "<<NNoutput[1]<<std::endl;

			if (NNoutput[0] == ideat_out[v][0] && NNoutput[1] == ideat_out[v][1])
			{
				tests_result[v]=1;
				continue;
			}else
			{
				float input_error[9]			{0.0f, 0.0f, 0.0f,
									 0.0f, 0.0f, 0.0f,
									 0.0f, 0.0f, 0.0f};

				float output_error[2]{ideat_out[v][0] - NNoutput[0], ideat_out[v][0] - NNoutput[0]};

				float NNlay1_error[3]{0.0, 0.0, 0.0};

				float NNlay0_error[4]{0.0, 0.0, 0.0, 0.0};

				NNlay1.find_error(output_error);

				NNlay0.find_error(NNlay1_error);

				NNlay0.weights_correction(0.1, NNlay1_error);
				NNlay1.weights_correction(0.1, output_error);
			};
		};
		if (	tests_result[0] 	&& tests_result[1] 		&&
		 	tests_result[2] 	&& tests_result[3] 		&&
		 	tests_result[4] 	&& tests_result[5] 		&& 
		 	tests_result[6] 	&& tests_result[7] 		&& 
		 	tests_result[8] 	&& tests_result[9] 		&& 
		 	tests_result[10] 	&& tests_result[11] 		&& 
			tests_result[12] 	&& tests_result[13])
		{
			break;
		}
		if(qwe > 154){break;};
	}

	return 0;
};
