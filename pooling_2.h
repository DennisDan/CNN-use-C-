#pragma once
#ifndef POOLING_2_H_

#include<iostream>
#include<vector>
using namespace std;

#include"Defaults.h"
#include"convolution_2.h"


struct pooling_matrix_po_2 {
	long double **output;
	long double **dc_dz;
	long double **output_diff;

	void creat_pooling_1_po_2();
};
struct pooling_layer_po_2 {
	pooling_matrix_po_2 **pooling_output_matrix;
	void creat_pooling_layer_po_2();
};



class pooling_2
{
private:

	//pooling_layer pooling_object[pooling_2_number];
	vector<pooling_layer_po_2*> pooling_object;


public:

	friend class interface__;
	friend class full_connected;

	pooling_2();
	void initialize();
	void second_pooling(convolution_2 convolution_2);
	void give_conv_2_delta(convolution_2 convolution_2);

	void print();

};


#endif // !POOLING_
