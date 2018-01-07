#pragma once
#ifndef INTERFACE_H_
#include"pooling_2.h"

struct neuron_face {
	long double output;
	void creat_neuron_face();
};
struct layer_face {
	neuron_face **neurons;
	void creat_layer_face();
};


class interface__
	//class convolution_1
{
private:


	//layer convolution_2_hidden_layer_object[interface__number_layers];
	vector<layer_face*> convolution_2_hidden_layer_object;

public:
	interface__();
	void initialize();
	// friend from convolution_1 to max_pooling_1
	void giveValue(pooling_2 pooling_2);

	friend class full_connected;


};




#endif // !INTERFACE_H_
