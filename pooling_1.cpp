 
#include<iostream>

using namespace std;


#include"pooling_1.h"
#include"convolution_1.h"
#include"Defaults.h"
#include"activation_function.h"

pooling_1::pooling_1() {

	for (size_t i = 0; i < pooling_1_number; i++)
	{
		pooling_object.emplace_back(new pooling_layer());

	}

	for (size_t i = 0; i < pooling_1_number; i++)
	{
		pooling_padding_object.emplace_back(new pooling_padding_layer());
	}

}

void pooling_1::first_pooling(convolution_1 convolution_1)
{
	for (size_t k = 0; k < pooling_1_number; k++)
	{
		for (size_t w = 0; w < pooling_D_1; w++)
		{
			for (size_t i = 0; i < pooling_H_1; i++)
			{
				for (size_t j = 0; j < pooling_W_1; j++)
				{

					long double z = 0;

					for (size_t m = 0; m < F_pooling_1; m++)
					{
						for (size_t n = 0; n < F_pooling_1; n++)
						{
							z += convolution_1.feature_object[k]->feature_maps[w]->output[stride_pooling_1 * i + m][stride_pooling_1 * j + n];
						}
					}
					pooling_object[k]->pooling_output_matrix[w]->output[i][j] = z / 4;
					pooling_object[k]->pooling_output_matrix[w]->output_diff[i][j] = de_relu(z / 4);
				}
			}
		}
	}
}

void pooling_1::creat_padding() {

	for (size_t k = 0; k < pooling_1_number; k++)
	{
		for (size_t w = 0; w < pooling_D_1; w++)
		{
			for (size_t i = 1; i < pooling_H_1 + 1; i++)
			{
				for (size_t j = 1; j < pooling_W_1 + 1; j++)
				{
					pooling_padding_object[k]->pooling_padding_output_matrix[w]->padding_output[i][j] =
						pooling_object[k]->pooling_output_matrix[w]->output[i - 1][j - 1];
				}
			}
		}
	}
}


void pooling_1::give_conv_1_delta(convolution_1 convolution_1)
{
	for (size_t k = 0; k < pooling_1_number; k++)
	{
		for (size_t w = 0; w < pooling_D_1; w++)
		{
			for (size_t i = 0; i < pooling_H_1; i++)
			{
				for (size_t j = 0; j < pooling_W_1; j++)
				{
					long double z = (pooling_object[k]->pooling_output_matrix[w]->dc_dz[i][j]) / 4;

					for (size_t m = 0; m < F_pooling_1; m++)
					{
						for (size_t n = 0; n < F_pooling_1; n++)
						{
							convolution_1.feature_object[k]->feature_maps[w]->dc_dz[stride_pooling_1 * i + m][stride_pooling_1 * j + n] =
								z;
						}
					}
				}
			}
		}
	}

}

void pooling_1::initialize() {
	for (size_t i = 0; i < pooling_1_number; i++)
	{
		pooling_object[i]->creat_pooling_layer();
		pooling_padding_object[i]->creat_pooling_padding_layer();
	}
}

void pooling_1::print() {


	for (size_t k = 0; k < pooling_1_number; k++)
	{
		for (size_t w = 0; w < pooling_D_1; w++)
		{
			for (size_t i = 0; i < pooling_H_1; i++)
			{
				for (size_t j = 0; j < pooling_W_1; j++)
				{

					cout << pooling_object[k]->pooling_output_matrix[w]->output[i][j];
				}
			}
		}
	}



}

void pooling_matrix::creat_pooling_1()
{
	float sign = -1;
	float random;

	output = new long double*[pooling_W_1];
	for (int i = 0; i < pooling_H_1; i++)
		output[i] = new long double[pooling_W_1];

	// for delta
	dc_dz = new long double*[pooling_W_1];
	for (int i = 0; i < pooling_H_1; i++)
		dc_dz[i] = new long double[pooling_W_1];

	output_diff = new long double*[pooling_W_1];
	for (int i = 0; i < pooling_H_1; i++)
		output_diff[i] = new long double[pooling_W_1];

	for (int i = 0; i<pooling_H_1; i++)
	{
		for (size_t j = 0; j < pooling_W_1; j++)
		{
			random = (float(rand()) / float(RAND_MAX)) / 2.f;
			random *= sign;
			sign *= -1;
			//output[i][j] = random;
		}
	}
}

void pooling_layer::creat_pooling_layer()
{
	int i;
	pooling_output_matrix = new pooling_matrix*[pooling_D_1];

	for (i = 0; i<pooling_D_1; i++)
	{
		pooling_output_matrix[i] = new pooling_matrix;
		pooling_output_matrix[i]->creat_pooling_1();
	}
}

void pooling_padding_matrix::creat_padding_pooling_1() {

	padding_output = new long double*[pooling_W_1 + 2];
	for (int i = 0; i < pooling_H_1 + 2; i++)
		padding_output[i] = new long double[pooling_W_1 + 2];

	for (int i = 0; i<pooling_H_1 + 2; i++)
	{
		for (size_t j = 0; j < pooling_W_1 + 2; j++)
		{
			padding_output[i][j] = 0;
		}
	}
}

void pooling_padding_layer::creat_pooling_padding_layer() {

	int i;
	pooling_padding_output_matrix = new pooling_padding_matrix*[pooling_D_1];

	for (i = 0; i<pooling_D_1; i++)
	{
		pooling_padding_output_matrix[i] = new pooling_padding_matrix;
		pooling_padding_output_matrix[i]->creat_padding_pooling_1();
	}
}