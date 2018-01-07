

#include<iostream>
#include<vector>
using namespace std;

#include"interface.h"
#include"activation_function.h"
#include"FULL_connected.h"
#include"pooling_2.h"



full_connected::full_connected() {


	for (size_t i = 0; i < full_connected_number_hidden_layers; i++)
	{
		full_connected_hidden_layer_object.emplace_back(new layer());

	}


	for (size_t i = 0; i < 1; i++)
	{
		full_connected_output_layer_object.emplace_back(new output_layer());

	}


	for (size_t i = 0; i < 1; i++)
	{
		full_connected_first_layer_object.emplace_back(new first_layer());

	}


}


void full_connected::back_output_last_hidden(vector<double> target) {

	for (size_t i = 0; i < full_connected_number_output_neurons; i++)
	{
		long double d = 0;

		d = (full_connected_output_layer_object[0]->output_neurons[i]->output - target[i])*
			(full_connected_output_layer_object[0]->output_neurons[i]->output_diff);

		full_connected_output_layer_object[0]->output_neurons[i]->dc_dz = d;

	}
	// updata weight

	for (size_t i = 0; i < full_connected_number_output_neurons; i++)
	{
		for (size_t j = 0; j < full_connected_number_hidden_neurons; j++)
		{
			double dd = 0;

			dd = (full_connected_output_layer_object[0]->output_neurons[i]->dc_dz)*
				(full_connected_hidden_layer_object[full_connected_number_hidden_layers - 1]->neurons[j]->output);

			full_connected_output_layer_object[0]->output_neurons[i]->weight[j] -= lamda* dd;

		}
	}
};

void full_connected::back_hidden_input(interface__ interface__, pooling_2 pooling_2) {



	//convolution_2.convolution_2_hidden_layer_object[0].neurons[0]->output = 1000;
	// dc_dz for last hidden layer

	for (size_t i = 0; i < full_connected_number_hidden_neurons; i++)
	{

		double b = 0;

		for (size_t j = 0; j < full_connected_number_output_neurons; j++)
		{
			b += full_connected_output_layer_object[0]->output_neurons[j]->dc_dz*
				full_connected_output_layer_object[0]->output_neurons[j]->weight[i];
		}

		full_connected_hidden_layer_object[full_connected_number_hidden_layers - 1]->neurons[i]->dc_dz = b*
			(full_connected_hidden_layer_object[full_connected_number_hidden_layers - 1]->neurons[i]->output_diff);
	}


	// find dc_dz
	for (size_t i = (full_connected_number_hidden_layers - 2); i == 0; i--)
	{
		for (size_t j = 0; j < full_connected_number_hidden_neurons; j++)
		{
			double dddd = 0;

			for (size_t k = 0; k < full_connected_number_hidden_neurons; k++)
			{
				dddd += full_connected_hidden_layer_object[i + 1]->neurons[k]->dc_dz*
					full_connected_hidden_layer_object[i + 1]->neurons[k]->weight[j];
			}

			full_connected_hidden_layer_object[i]->neurons[j]->dc_dz = dddd*
				full_connected_hidden_layer_object[i]->neurons[j]->output_diff;
		}
	}

	for (size_t w = 0; w < full_connected_number_intput_neurons; w++)
	{
		double ddddd = 0;

		for (size_t n = 0; n < full_connected_number_hidden_neurons; n++)
		{
			ddddd += full_connected_hidden_layer_object[0]->neurons[n]->dc_dz *
				full_connected_hidden_layer_object[0]->neurons[n]->weight[w];
		}
		full_connected_first_layer_object[0]->first_neurons[w]->dc_dz = ddddd*
			full_connected_first_layer_object[0]->first_neurons[w]->output_diff;
	}

	//**************************  dc_dz for pooling_2 last layer ***************************//

	int sssss = 0;

	for (size_t k = 0; k < pooling_2_number; k++)
	{
		for (size_t w = 0; w < pooling_D_2; w++)
		{
			for (size_t i = 0; i < pooling_H_2; i++)
			{
				for (size_t j = 0; j < pooling_W_2; j++)
				{
					long double itr = 0;

					for (size_t m = 0; m < full_connected_number_intput_neurons; m++)
					{
						//cout << sssss << endl;
						itr += full_connected_first_layer_object[0]->first_neurons[m]->dc_dz*
							full_connected_first_layer_object[0]->first_neurons[m]->weight[sssss];
					}
					pooling_2.pooling_object[k]->pooling_output_matrix[w]->dc_dz[i][j] = itr*
						pooling_2.pooling_object[k]->pooling_output_matrix[w]->output_diff[i][j];
					sssss++;

					if (sssss == interface__number_neurons) sssss -= 1;

				}
			}
		}
	}



	//**************************  dc_dz for pooling_2 last layer ***************************//



	// update weight  last hidden layer

	for (size_t i = 0; i < full_connected_number_hidden_neurons; i++)
	{
		for (size_t j = 0; j < full_connected_number_hidden_neurons; j++)
		{
			double g = 0;

			for (size_t k = 0; k < full_connected_number_output_neurons; k++)
			{
				g += full_connected_output_layer_object[0]->output_neurons[k]->dc_dz*
					full_connected_output_layer_object[0]->output_neurons[k]->weight[i];
			}
			full_connected_hidden_layer_object[full_connected_number_hidden_layers - 1]->neurons[i]->weight[j] -= lamda*g*
				full_connected_hidden_layer_object[full_connected_number_hidden_layers - 1]->neurons[i]->output*
				(1 - (full_connected_hidden_layer_object[full_connected_number_hidden_layers - 1]->neurons[i]->output))*
				full_connected_hidden_layer_object[full_connected_number_hidden_layers - 2]->neurons[j]->output;
		}
	}



	//   full_connected_number_hidden_layers -2
	for (size_t i = full_connected_number_hidden_layers - 2; i == 1; i--)  // layer
	{
		for (size_t j = 0; j < full_connected_number_hidden_neurons; j++)  // neuron
		{
			for (size_t k = 0; k < full_connected_number_hidden_neurons; k++) // weight
			{

				double dddddd = 0;

				for (size_t w = 0; w < full_connected_number_hidden_neurons; w++)
				{
					dddddd += full_connected_hidden_layer_object[i + 1]->neurons[w]->dc_dz*
						full_connected_hidden_layer_object[i + 1]->neurons[w]->weight[j];
				}

				full_connected_hidden_layer_object[i]->neurons[j]->weight[k] -= lamda*dddddd*
					full_connected_hidden_layer_object[i]->neurons[j]->output*
					(1 - (full_connected_hidden_layer_object[i]->neurons[j]->output))*
					full_connected_hidden_layer_object[i - 1]->neurons[k]->output;
			}
		}
	}


	// update first hidden layer
	for (size_t i = 0; i < full_connected_number_hidden_neurons; i++)   // neuron
	{
		for (size_t j = 0; j < full_connected_number_intput_neurons; j++)  // weight
		{
			double aa = 0;

			for (size_t k = 0; k < full_connected_number_hidden_neurons; k++)
			{
				aa += full_connected_hidden_layer_object[1]->neurons[k]->dc_dz*
					full_connected_hidden_layer_object[1]->neurons[k]->weight[i];
			}
			full_connected_hidden_layer_object[0]->neurons[i]->weight[j] -= lamda*aa*
				full_connected_hidden_layer_object[0]->neurons[i]->output*
				(1 - (full_connected_hidden_layer_object[0]->neurons[i]->output))*
				full_connected_first_layer_object[0]->first_neurons[j]->output;
		}
	}




	for (size_t i = 0; i < full_connected_number_intput_neurons; i++)  // neuron
	{
		for (size_t j = 0; j < interface__number_neurons; j++)  // weight
		{
			double aaa = 0;

			for (size_t k = 0; k < full_connected_number_hidden_neurons; k++)
			{
				aaa += full_connected_hidden_layer_object[0]->neurons[k]->dc_dz*
					full_connected_hidden_layer_object[0]->neurons[k]->weight[i];

			}

			full_connected_first_layer_object[0]->first_neurons[i]->weight[j] -= lamda*aaa*
				full_connected_first_layer_object[0]->first_neurons[i]->output*
				(1 - (full_connected_first_layer_object[0]->first_neurons[i]->output))*
				interface__.convolution_2_hidden_layer_object[0]->neurons[j]->output;
		}
	}
};

void full_connected::forward_first(interface__ interface__) {

	// input = convolution_2.convolution_2_hidden_layer_object[i].neurons[j]->output



	for (size_t j = 0; j < full_connected_number_intput_neurons; j++)
	{
		double num = 0;

		for (size_t k = 0; k < interface__number_neurons; k++)
		{

			num +=
				interface__.convolution_2_hidden_layer_object[0]->neurons[k]->output
				*full_connected_first_layer_object[0]->first_neurons[j]->weight[k];
		}
		full_connected_first_layer_object[0]->first_neurons[j]->output = relu(num);
		//cout << full_connected_first_layer_object[0].first_neurons[j]->output;
		full_connected_first_layer_object[0]->first_neurons[j]->output_diff = de_relu(num);
	}

};

void full_connected::forward_hidden() {


	for (size_t w = 0; w < full_connected_number_hidden_neurons; w++)
	{
		double nnu = 0;

		for (size_t x = 0; x < full_connected_number_intput_neurons; x++)
		{

			nnu +=
				full_connected_first_layer_object[0]->first_neurons[x]->output*
				full_connected_hidden_layer_object[0]->neurons[w]->weight[x];
		}
		full_connected_hidden_layer_object[0]->neurons[w]->output = relu(nnu);
		full_connected_hidden_layer_object[0]->neurons[w]->output_diff = de_relu(nnu);
	}





	for (size_t i = 1; i < full_connected_number_hidden_layers; i++)
	{
		for (size_t j = 0; j < full_connected_number_hidden_neurons; j++)
		{
			double numm = 0;

			for (size_t k = 0; k < full_connected_number_hidden_neurons; k++)
			{
				numm +=
					full_connected_hidden_layer_object[i - 1]->neurons[k]->output*
					full_connected_hidden_layer_object[i]->neurons[j]->weight[k];
			}

			full_connected_hidden_layer_object[i]->neurons[j]->output = sigmoid(numm);
		}
	}
};

void full_connected::forward_output()
{
	for (size_t i = 0; i < full_connected_number_output_neurons; i++)
	{
		double nummm = 0;

		for (size_t j = 0; j < full_connected_number_hidden_neurons; j++)
		{
			nummm +=
				full_connected_hidden_layer_object[full_connected_number_hidden_layers - 1]->neurons[j]->output*
				full_connected_output_layer_object[0]->output_neurons[i]->weight[j];
		}
		full_connected_output_layer_object[0]->output_neurons[i]->output = relu(nummm);
		full_connected_output_layer_object[0]->output_neurons[i]->output_diff = de_relu(nummm);



	}
}


// convolution_2 的 output 就是 full connected 的 input

void full_connected::giveValue(interface__ interface__)
{

	for (size_t i = 0; i < full_connected_number_hidden_layers; i++)
	{
		for (size_t j = 0; j < full_connected_number_hidden_neurons; j++)
		{
			for (size_t k = 0; k < full_connected_number_hidden_neurons; k++)
			{
				full_connected_hidden_layer_object[i]->neurons[j]->weight[k] = 1;
			}
		}
	}


	for (size_t i = 0; i < full_connected_number_hidden_layers; i++)
	{
		for (size_t j = 0; j < full_connected_number_hidden_neurons; j++)
		{
			full_connected_hidden_layer_object[i]->neurons[j]->output = j
				+ interface__.convolution_2_hidden_layer_object[i]->neurons[j]->output;
		}
	}



}

void full_connected::print()
{

	for (size_t j = 0; j < full_connected_number_hidden_neurons; j++)
	{
		//	cout << full_connected_output_layer_object[0].output_neurons[2]->weight[j] << " ";
		//	cout << full_connected_hidden_layer_object[4].neurons[0]->weight[j]<<" ";
	}
	cout << endl;

	for (size_t j = 0; j < full_connected_number_output_neurons; j++)
	{
		cout << full_connected_output_layer_object[0]->output_neurons[j]->output << " ";
	}
	cout << endl;
}

void full_connected::initialize()
{
	//hidden and first layer
	for (size_t i = 0; i < full_connected_number_hidden_layers; i++)
	{
		full_connected_hidden_layer_object[i]->creat_layer();
	}
	// last output layer
	full_connected_output_layer_object[0]->creat_output_layer();
	full_connected_first_layer_object[0]->creat_first_layer();

}


void  neuron::creat_neuron()
{
	float sign = -1;
	float random;
	weight = new long double[full_connected_number_hidden_neurons];
	//output = new double[full_connected_number_hidden_neurons];

	for (int i = 0; i<full_connected_number_hidden_neurons; i++)
	{
		random = (float(rand()) / float(RAND_MAX)) / 2.f;
		random *= sign;
		sign *= -1;
		weight[i] = random;
		//output[i] = 0;
	}
}

void  layer::creat_layer()
{
	int i;
	neurons = new neuron*[full_connected_number_hidden_neurons];

	for (i = 0; i<full_connected_number_hidden_neurons; i++)
	{
		neurons[i] = new neuron;
		neurons[i]->creat_neuron();
	}
}


void  output_neuron::creat_output_neuron()
{
	float sign = -1;
	float random;
	weight = new long double[full_connected_number_hidden_neurons];
	//output = new double[full_connected_number_hidden_neurons];

	for (int i = 0; i<full_connected_number_hidden_neurons; i++)
	{
		random = (float(rand()) / float(RAND_MAX)) / 2.f;
		random *= sign;
		sign *= -1;
		weight[i] = random;
		//output[i] = 0;
	}
}

void  output_layer::creat_output_layer()
{
	int i;
	output_neurons = new output_neuron*[full_connected_number_output_neurons];

	for (i = 0; i<full_connected_number_output_neurons; i++)
	{
		output_neurons[i] = new output_neuron;
		output_neurons[i]->creat_output_neuron();
	}
}


void  first_neuron::creat_first_neuron()
{
	float sign = -1;
	float random;
	weight = new long double[interface__number_neurons];

	//output = new double[full_connected_number_hidden_neurons];

	for (int i = 0; i<interface__number_neurons; i++)
	{
		random = (float(rand()) / float(RAND_MAX)) / 2.f;
		random *= sign;
		sign *= -1;
		weight[i] = random;
		//output[i] = 0;
	}
}

void  first_layer::creat_first_layer()
{
	int i;
	first_neurons = new first_neuron*[full_connected_number_intput_neurons];

	for (i = 0; i<full_connected_number_intput_neurons; i++)
	{
		first_neurons[i] = new first_neuron;
		first_neurons[i]->creat_first_neuron();
	}
}



