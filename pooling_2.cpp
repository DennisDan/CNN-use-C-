
#include<iostream>

using namespace std;


#include"pooling_2.h"
#include"convolution_2.h"
#include"Defaults.h"
#include"activation_function.h"


pooling_2::pooling_2() {

	for (size_t i = 0; i < pooling_2_number; i++)
	{
		pooling_object.emplace_back(new pooling_layer_po_2());

	}

}



void pooling_2::initialize() {

	for (size_t i = 0; i < pooling_2_number; i++)
	{
		pooling_object[i]->creat_pooling_layer_po_2();
	}
}

void pooling_2::second_pooling(convolution_2 convolution_2)
{

	for (size_t k = 0; k < pooling_2_number; k++)
	{
		for (size_t w = 0; w < pooling_D_2; w++)
		{
			for (size_t i = 0; i < pooling_H_2; i++)
			{
				for (size_t j = 0; j < pooling_W_2; j++)
				{
					long double z = 0;

					for (size_t m = 0; m < F_pooling_2; m++)
					{
						for (size_t n = 0; n < F_pooling_2; n++)
						{
							z += convolution_2.feature_object[k]->feature_maps[w]->output[stride_pooling_2 * i + m][stride_pooling_2 * j + n];
						}
					}
					pooling_object[k]->pooling_output_matrix[w]->output[i][j] = z / 4;

					//cout << pooling_object[k].pooling_output_matrix[w]->output[i][j];
				}
			}
		}
	}
}

void pooling_2::give_conv_2_delta(convolution_2 convolution_2) {

	for (size_t k = 0; k < pooling_2_number; k++)
	{
		for (size_t w = 0; w < pooling_D_2; w++)
		{
			for (size_t i = 0; i < pooling_H_2; i++)
			{
				for (size_t j = 0; j < pooling_W_2; j++)
				{
					long double z = (pooling_object[k]->pooling_output_matrix[w]->dc_dz[i][j]) / 4;

					for (size_t m = 0; m < F_pooling_2; m++)
					{
						for (size_t n = 0; n < F_pooling_2; n++)
						{
							convolution_2.feature_object[k]->feature_maps[w]->dc_dz[stride_pooling_2 * i + m][stride_pooling_2 * j + n] =
								z;
						}
					}
				}
			}
		}
	}
};



void pooling_2::print() {


	for (size_t k = 0; k < pooling_2_number; k++)
	{
		for (size_t w = 0; w < pooling_D_2; w++)
		{
			for (size_t i = 0; i < pooling_H_2; i++)
			{
				for (size_t j = 0; j < pooling_W_2; j++)
				{

					cout << pooling_object[k]->pooling_output_matrix[w]->output[i][j];
				}
			}
		}
	}



}

void  pooling_matrix_po_2::creat_pooling_1_po_2()
{
	float sign = -1;
	float random;

	output = new long double*[pooling_W_2];
	for (int i = 0; i < pooling_H_2; i++)
		output[i] = new long double[pooling_W_2];

	output_diff = new long double*[pooling_W_2];
	for (int i = 0; i < pooling_H_2; i++)
		output_diff[i] = new long double[pooling_W_2];

	// for delta
	dc_dz = new long double*[pooling_W_2];
	for (int i = 0; i < pooling_H_2; i++)
		dc_dz[i] = new long double[pooling_W_2];


	for (int i = 0; i<pooling_H_2; i++)
	{
		for (size_t j = 0; j < pooling_W_2; j++)
		{
			random = (float(rand()) / float(RAND_MAX)) / 2.f;
			random *= sign;
			sign *= -1;
			//output[i][j] = random;
		}
	}
}

void  pooling_layer_po_2::creat_pooling_layer_po_2()
{
	int i;
	pooling_output_matrix = new pooling_matrix_po_2*[pooling_D_2];

	for (i = 0; i<pooling_D_2; i++)
	{
		pooling_output_matrix[i] = new pooling_matrix_po_2;
		pooling_output_matrix[i]->creat_pooling_1_po_2();
	}
}