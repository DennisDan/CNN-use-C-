#pragma once
#ifndef FULL_CONNECTED_H_

#include<iostream>
#include<vector>
using namespace std;

#include"interface.h"


struct first_neuron {
	long double output_diff;
	long double output;
	long double dc_dz;
	long double *weight;
	void creat_first_neuron();
};
struct first_layer {
	first_neuron **first_neurons;
	void creat_first_layer();
};

//------------------------------  full connected hidden layer

struct neuron {
	long double output_diff;

	long double output;
	long double dc_dz;
	long double *weight;
	void creat_neuron();
};
struct layer {
	neuron **neurons;
	void creat_layer();
};

//------------------------------  full connected output layer

struct output_neuron {
	long double output_diff;

	long double output;
	long double dc_dz;
	long double *weight;
	void creat_output_neuron();
};
struct output_layer {
	output_neuron **output_neurons;
	void creat_output_layer();
};


class full_connected
	//class convolution_1
{
private:

	//-------------------------------  full onnected first layer



	//------------------------------  creat objects

	//layer full_connected_hidden_layer_object[full_connected_number_hidden_layers];
	//output_layer full_connected_output_layer_object[1];
	//first_layer full_connected_first_layer_object[1];

	vector<layer*> full_connected_hidden_layer_object;
	vector<output_layer*> full_connected_output_layer_object;
	vector<first_layer*> full_connected_first_layer_object;





public:
	full_connected();

	void initialize();
	void giveValue(interface__ interface__);
	void print();
	void forward_first(interface__ interface__);
	void forward_hidden();
	void forward_output();

	void back_output_last_hidden(vector<double> target);
	void back_hidden_input(interface__ interface__, pooling_2  pooling_2);


};







#endif // !FULL_CONNECTED_H_
