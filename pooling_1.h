#pragma once
#ifndef POOLING_1_H_


#include<iostream>
#include<vector>
using namespace std;

#include"Defaults.h"
#include"convolution_1.h"


struct pooling_matrix {
	long double **output;
	long double **dc_dz;
	long double **output_diff;
	void creat_pooling_1();
};
struct pooling_layer {
	pooling_matrix **pooling_output_matrix;
	void creat_pooling_layer();
};

struct pooling_padding_matrix {

	long double **padding_output;
	void creat_padding_pooling_1();
};

struct pooling_padding_layer {

	pooling_padding_matrix **pooling_padding_output_matrix;
	void creat_pooling_padding_layer();
};




class pooling_1
{
private:

	vector<pooling_layer*> pooling_object;
	vector<pooling_padding_layer*> pooling_padding_object;

	//pooling_layer pooling_object[pooling_1_number];
	//pooling_padding_layer pooling_padding_object[pooling_1_number];

public:

	pooling_1();

	void initialize();

	void first_pooling(convolution_1 convolution_1);
	void creat_padding();
	void give_conv_1_delta(convolution_1 convolution_1);
	void print();


	friend class convolution_2;

};














#endif // !POOLING_1_H_
