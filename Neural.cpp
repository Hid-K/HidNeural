#include <iostream>
#include "HidNeural.cpp"
#include <cstdlib>
#include <ctime>

const float LEARN_CO = 100.0f;

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

float NNlay0_weights[3][4];


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

NeuralNet::NeuralNetworkLayer<NeuralNet::sygmoid> NNlay0({NNinput, 9}, 
														 (float*)NNinput_correction, 4);

NeuralNet::NeuralNetworkLayer<NeuralNet::sygmoid> NNlay1(NNlay0.getOutputs(),
														(float*)NNlay0_weights, 3);

NeuralNet::NeuralNetworkLayer<NeuralNet::sygmoid> NNout(NNlay1.getOutputs(),
													   (float*)NNlay1_weights, 2);

int main(int argc, char const *argv[])
{
	// std::srand(unsigned(std::time(0)));
	std::srand(12);

	NNout.setOutputs({NNoutput, 2});

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

	/*
	if (argc > 0)
	{
		LEARN_CO = (float)argv[0][0];
	};
	*/


	for(int qwe = 0; qwe < 150; qwe++)
	{
		std::cout<<"AGE:"<<qwe<<'\n';
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


			std::cout<<"IDEAL:"<<ideat_out[v][0]<<" "<<ideat_out[v][1]<<std::endl;
			std::cout<<"OUTPUT:"<<NNoutput[0]<<" "<<NNoutput[1]<<std::endl<<std::endl;

			if (NNoutput[0] == ideat_out[v][0] && NNoutput[1] == ideat_out[v][1])
			{
				tests_result[v]=1;
				continue;
			}else
			{
				static float input_error[9]{0.0f, 0.0f, 0.0f,
									 0.0f, 0.0f, 0.0f,
									 0.0f, 0.0f, 0.0f};

				static float output_error[2];

				static float NNlay1_error[3]{0.0, 0.0, 0.0};

				static float NNlay0_error[4]{0.0, 0.0, 0.0, 0.0};


				NeuralNet::find_out_error(ideat_out[v], output_error, NNout.getOutputs());	

				NeuralNet::find_error(NNlay0.getOutputs(), {NNinput, 9}, input_error, NNlay1_error, 
									 (float*)NNlay1_weights); //Get error for lay1.

				NeuralNet::find_error({NNinput, 9}, NNlay1.getOutputs(), input_error, NNlay1_error,
									  (float*)NNinput_correction); //Get error for lay0.



				std::cout<<"input_error:\n";

				for (int i = 0; i < 9; ++i)
				{
					std::cout<<input_error[i]<<" ";
				}

				std::cout<<'\n';

				std::cout<<"NNlay1_error:\n";

				for (int i = 0; i < 4; ++i)
				{
					std::cout<<NNlay1_error[i]<<" ";
				}

				std::cout<<'\n';

				std::cout<<"NNlay0_error:\n";

				for (int i = 0; i < 3; ++i)
				{
					std::cout<<NNlay0_error[i]<<" ";
				}

				std::cout<<'\n';

				std::cout<<"output_error:\n";

				for (int i = 0; i < 2; ++i)
				{
					std::cout<<output_error[i]<<" ";
				}

				std::cout<<"\n\n\n\n";

				NeuralNet::weights_correction(input_error, NNlay1_error, (float*)NNinput_correction, 
											  {NNinput, 9}, NNlay1.getOutputs(), LEARN_CO);

				NeuralNet::weights_correction(NNlay0_error, NNlay1_error, (float*)NNlay0_weights, 
											  NNlay1.getOutputs(), NNlay0.getOutputs(), LEARN_CO);

			
				/*std::cout<<"Weights corrected:\n";

				for (uintmax_t x = 0; x < 3; ++x)
				{
					for (int y = 0; y < 4; ++y)
					{
						std::cout<<NNlay0_weights[x][y]<<" ";
					};
				};
			 
				std::cout<<'\n';

				for (uintmax_t x = 0; x < 4; ++x)
				{
					for (int y = 0; y < 9; ++y)
					{
						std::cout<<NNinput_correction[x][y]<<" ";
					};
				};

				std::cout<<'\n';

				for (uintmax_t x = 0; x < 2; ++x)
				{
					for (int y = 0; y < 3; ++y)
					{
						std::cout<<NNlay1_weights[x][y]<<" ";
					};
				};*/

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
	}

	return 0;
};
