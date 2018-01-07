#include<iostream>
using namespace std;



#include"activation_function.h"
#include"Defaults.h"
#include"convolution_2.h"
#include"pooling_1.h"

convolution_2::convolution_2() {

	for (size_t i = 0; i < number_kernal_2; i++)
	{
		kernal_object.emplace_back(new kernal_layer_conv_2());

	}

	for (size_t i = 0; i < feature_2_number; i++)
	{
		feature_object.emplace_back(new feature_layer_conv_2());
	}

}


void convolution_2::initialize()
{
	for (size_t i = 0; i < number_kernal_2; i++)
	{
		kernal_object[i]->creat_kernal_layer_conv_2();

	}



	for (size_t i = 0; i < feature_2_number; i++)
	{
		feature_object[i]->creat_feature_layer_conv_2();

	}
}

void convolution_2::second_convolution(pooling_1 pooling_1) {

	for (size_t k = 0; k < feature_2_number; k++)
	{
		int zzzz = 0;

		for (size_t w = 0; w < feature_2_D; w++)
		{
			int kkkk = 0;
			int nnnn = 1;

			for (size_t i = 0; i < feature_2_H; i++)
			{
				for (size_t j = 0; j < feature_2_W; j++)
				{
					long double z = 0;

					for (size_t m = 0; m < F_kernal_2; m++)
					{
						for (size_t n = 0; n < F_kernal_2; n++)
						{
							//cout << kernal_object[k].kernals[w]->weight[m][n];
							z += kernal_object[k]->kernals[w]->weight[m][n] *
								//pooling_1.pooling_object[zzzz].pooling_output_matrix[kkkk]->output[i + m][j + n];
								pooling_1.pooling_padding_object[zzzz]->pooling_padding_output_matrix[kkkk]->padding_output[i + m][j + n];
						}
					}

					feature_object[k]->feature_maps[w]->output[i][j] = relu(z);
					feature_object[k]->feature_maps[w]->output_diff[i][j] = de_relu(z);
					//cout << feature_object[k].feature_maps[w]->output[i][j]<<endl;
				}
			}
			if (nnnn == feature_2_D / pooling_D_1)
			{
				zzzz++;
				nnnn = 0;
			}

			nnnn++;
			kkkk++;

			if (kkkk == pooling_D_1) {
				kkkk = 0;
			}
		}
	}
};

void convolution_2::give_pooling_1_delta(pooling_1 pooling_1) {

	// num is iteration for every kernal object from 0 ~ 15
	int num = 0;

	for (size_t k = 0; k < pooling_1_number; k++)
	{
		for (size_t w = 0; w < pooling_D_1 - 2; w++)
		{
			for (size_t i = 0; i < pooling_H_1 - 2; i++)
			{
				for (size_t j = 0; j < pooling_W_1; j++)
				{
					long double zz = 0;

					// for number of kernals and feature maps
					for (size_t d = 0; d < number_kernal_2; d++)
					{
						for (size_t m = 0; m < F_kernal_2; m++)
						{
							for (size_t n = 0; n < F_kernal_2; n++)
							{
								zz += (kernal_object[d]->kernals[num]->weight[m][n])*
									(feature_object[d]->feature_maps[num]->dc_dz[i + m][j + n]);

								//	cout << kernal_object[d].kernals[num]->weight[m][n];
								//	cout << feature_object[d].feature_maps[num]->dc_dz[i + m][j + n];
							}
						}
					}
					pooling_1.pooling_object[k]->pooling_output_matrix[w]->dc_dz[i][j] = zz*
						pooling_1.pooling_object[k]->pooling_output_matrix[w]->output_diff[i][j];
				}
			}
			num++;
			//if (num == pooling_1_number*pooling_D_1) num -= 1;
		}
	}
};

void convolution_2::updata_weight(pooling_1 pooling_1) {

	for (size_t k = 0; k < number_kernal_2; k++)
	{
		int zzzz = 0;

		for (size_t w = 0; w < kernal_2_D; w++)
		{
			int kkkk = 0;
			int nnnn = 1;

			for (size_t i = 0; i < F_kernal_2; i++)
			{
				for (size_t j = 0; j < F_kernal_2; j++)
				{
					long double delta = 0;

					for (size_t m = 0; m < feature_2_H - 2; m++)
					{
						for (size_t n = 0; n < feature_2_W - 2; n++)
						{
							delta += feature_object[k]->feature_maps[w]->dc_dz[m][n] *
								pooling_1.pooling_object[zzzz]->pooling_output_matrix[kkkk]->output[m + i][n + j];
						}
					}
					kernal_object[k]->kernals[w]->weight[i][j] -= lamda*delta;
				}
			}

			if (nnnn == kernal_2_D / pooling_D_1)
			{
				zzzz++;
				nnnn = 0;
			}

			nnnn++;
			kkkk++;

			if (kkkk == pooling_D_1) {
				kkkk = 0;
			}
		}
	}



};

void convolution_2::print()
{

	for (size_t i = 0; i < feature_2_number; i++)
	{
		for (size_t j = 0; j < feature_2_D; j++)
		{
			for (size_t k = 0; k < feature_2_H; k++)
			{
				for (size_t w = 0; w < feature_2_W; w++)
				{
					cout << feature_object[i]->feature_maps[j]->output[k][w];
				}
				cout << endl;
			}
		}
	}
}

//----------------------------------------------------------------------------

void  kernal_conv_2::creat_kernal_1_conv_2()
{
	float sign = -1;
	float random;

	weight = new long double*[F_kernal_2];
	for (int i = 0; i < F_kernal_2; i++)
		weight[i] = new long double[F_kernal_2];

	for (int i = 0; i<F_kernal_2; i++)
	{
		for (size_t j = 0; j < F_kernal_2; j++)
		{
			random = (float(rand()) / float(RAND_MAX)) / 2.f;
			random *= sign;
			sign *= -1;
			weight[i][j] = random;
		}
	}
}

void  kernal_layer_conv_2::creat_kernal_layer_conv_2()
{
	int i;
	kernals = new kernal_conv_2*[kernal_2_D];

	for (i = 0; i<kernal_2_D; i++)
	{
		kernals[i] = new kernal_conv_2;
		kernals[i]->creat_kernal_1_conv_2();
	}
}

void  feature_map_conv_2::creat_feature_conv_2()
{
	float sign = -1;
	float random;

	// i=°ª«×
	// j=¼e«×

	int HH = feature_2_H;
	int WW = feature_2_W;

	output = new long double*[WW];
	for (int i = 0; i < HH; i++)
		output[i] = new long double[WW];

	// for differntial
	output_diff = new long double*[WW];
	for (int i = 0; i < HH; i++)
		output_diff[i] = new long double[WW];

	// for delta
	dc_dz = new long double*[WW];
	for (int i = 0; i < HH; i++)
		dc_dz[i] = new long double[WW];

}

void feature_layer_conv_2::creat_feature_layer_conv_2()
{
	int i;
	feature_maps = new feature_map_conv_2*[feature_2_D];

	for (i = 0; i<feature_2_D; i++)
	{
		feature_maps[i] = new feature_map_conv_2;
		feature_maps[i]->creat_feature_conv_2();
	}
}
