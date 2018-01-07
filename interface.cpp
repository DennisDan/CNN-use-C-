#include<iostream>
using namespace std;



#include"activation_function.h"
#include"Defaults.h"
#include"pooling_2.h"
#include"interface.h"



interface__::interface__() {


	for (size_t i = 0; i < interface__number_layers; i++)
	{
		convolution_2_hidden_layer_object.emplace_back(new layer_face());

	}


}

void interface__::giveValue(pooling_2 pooling_2)
{

	int zzz = 0;
	for (size_t i = 0; i < pooling_2_number; i++)
	{
		for (size_t j = 0; j < pooling_D_2; j++)
		{
			for (size_t k = 0; k < pooling_H_2; k++)
			{
				for (size_t w = 0; w < pooling_W_2; w++)
				{
					//	cout << zzz;
					//	interface__number_neurons=394
					//	cout << pooling_2_number<<"  "<< pooling_D_2<<"  "<< pooling_H_2<<"  "<< pooling_W_2<<endl;
					convolution_2_hidden_layer_object[0]->neurons[zzz]->output =
						pooling_2.pooling_object[i]->pooling_output_matrix[j]->output[k][w];

					//	cout<< pooling_2.pooling_object[i].pooling_output_matrix[j]->output[k][w];
					zzz++;
				}
			}
		}
	}
	//for (size_t j = 0; j < interface__number_neurons; j++)
	//	{
	//	convolution_2_hidden_layer_object[0].neurons[j]->output = 0.1;
	//}
}



void interface__::initialize()
{
	convolution_2_hidden_layer_object[0]->creat_layer_face();
}

void  neuron_face::creat_neuron_face() {};

void  layer_face::creat_layer_face()
{
	int i;
	neurons = new neuron_face*[93750];

	for (i = 0; i<93750; i++)
	{
		neurons[i] = new neuron_face;
		neurons[i]->creat_neuron_face();
	}
}

