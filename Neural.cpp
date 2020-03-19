#include <iostream>
#include "HidNeural.cpp"
#include <cstdlib>
#include <ctime>

float NNinput[9] =				  {0.0F, 0.0F, 0.0F,
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

float input_options[14][9] {{0.0f, 0.0f, 0.0f,
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
	// std::srand(unsigned(std::time(0)));
	std::srand(12);

	for (uintmax_t x = 0; x < 3; ++x)
	{
		for (int y = 0; y < 4; ++y)
		{
			NNlay0_weights[x][y] = std::rand();
			std::cout<<NNlay0_weights[x][y]<<" ";
		};
	};

	std::cout<<'\n';

	for (uintmax_t x = 0; x < 4; ++x)
	{
		for (int y = 0; y < 9; ++y)
		{
			NNinput_correction[x][y] = std::rand();
			std::cout<<NNinput_correction[x][y]<<" ";
		};
	};

	std::cout<<'\n';

	for (uintmax_t x = 0; x < 2; ++x)
	{
		for (int y = 0; y < 3; ++y)
		{
			NNlay1_weights[x][y] = std::rand();
			std::cout<<NNlay1_weights[x][y]<<" ";
		};
	};

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
				float input_error[9]{0.0f, 0.0f, 0.0f,
									 0.0f, 0.0f, 0.0f,
									 0.0f, 0.0f, 0.0f};

				float output_error[2]/*{ideat_out[v][0] - NNoutput[0], ideat_out[v][0] - NNoutput[0]}*/;

				float NNlay1_error[3]{0.0, 0.0, 0.0};

				float NNlay0_error[4]{0.0, 0.0, 0.0, 0.0};


				NeuralNet::find_out_error(ideat_out[v], output_error, NNoutput, 2);	

				NeuralNet::find_error(NNlay0_error, NNlay1_error, (float*)NNlay1_weights, 4, 3);		//Get error for lay1.
			
				NeuralNet::find_error(input_error, NNlay1_error, (float*)NNinput_correction, 9, 4);		//Get error for lay1.

				NeuralNet::weights_correction(NNlay0_error, NNlay1_error, (float*)NNlay1_weights, 
											  NNlay1_out, NNlay0_out, 4, 3, 0.5);
			
				NeuralNet::weights_correction(input_error, NNlay1_error, (float*)NNinput_correction, 
											  NNinput, NNlay1_out, 9, 4, 0.5);
			};
		};
		if (tests_result[0] 	&& tests_result[1] 		&&
		 	tests_result[2] 	&& tests_result[3] 		&&
		 	tests_result[4] 	&& tests_result[5] 		&& 
		 	tests_result[6] 	&& tests_result[7] 		&& 
		 	tests_result[8] 	&& tests_result[9] 		&& 
		 	tests_result[10] 	&& tests_result[11] 	&& 
			tests_result[12] 	&& tests_result[13])
		{
			break;
		}
		if(qwe > 154){break;};
	}

	return 0;
};
