 

#include<iostream>
using namespace std;



#include"convolution_1.h"
#include"Defaults.h"
#include"activation_function.h"


convolution_1::convolution_1() {
 
	// kernal_layer kernal_object[number_kernal_1];
	// feature_layer feature_object[feature_1_number];


	for (size_t i = 0; i < number_kernal_1; i++)
	{
		kernal_object.emplace_back(new kernal_layer());
	
	}

	for (size_t i = 0; i < feature_1_number; i++)
	{
		feature_object.emplace_back(new feature_layer());
	}

}


void convolution_1::initialize()
{
	for (size_t i = 0; i < number_kernal_1; i++)
	{
		kernal_object[i]->creat_kernal_layer();		
	}



	for (size_t i = 0; i < feature_1_number; i++)
	{
		feature_object[i]->creat_feature_layer();
	}
}

void convolution_1::first_convolution(image_part image_part) {
	for (size_t k = 0; k < feature_1_number; k++)
	{
		for (size_t w = 0; w < feature_1_D; w++)
		{
			for (size_t i = 0; i < feature_1_H; i++)
			{
				for (size_t j = 0; j < feature_1_W; j++)
				{
					long double res = 0;

					for (size_t m = 0; m < F_kernal_1; m++)
					{
						for (size_t n = 0; n < F_kernal_1; n++)
						{
							//	cout << kernal_object[k].kernals[w]->weight[m][n] << "    "<<image_part.image_object[0].images[w]->pixels[i + m][j + n] << endl;
							res += kernal_object[k]->kernals[w]->weight[m][n] *
								//image_part.image_object[0].images[w]->pixels[i + m][j + n];
								image_part.image_padding_object[0].padding_images[w]->padding_pixels[i + m][j + n];
							//cout << image_part.image_padding_object[0].padding_images[w]->padding_pixels[i + m][j + n] << endl;

						}
					}

					feature_object[k]->feature_maps[w]->output[i][j] = relu(res);
				}
			}
		}
	}
};

void convolution_1::updata_weight(image_part image_part) {

	for (size_t k = 0; k < number_kernal_1; k++)
	{
		int zzzz = 0;

		for (size_t w = 0; w < kernal_1_D; w++)
		{
			int kkkk = 0;
			int nnnn = 1;

			for (size_t i = 0; i < F_kernal_1; i++)
			{
				for (size_t j = 0; j < F_kernal_1; j++)
				{
					long double delta = 0;

					for (size_t m = 0; m < feature_1_H - 2; m++)
					{
						for (size_t n = 0; n < feature_1_W - 2; n++)
						{
							//cout << zzzz ;
							delta += feature_object[k]->feature_maps[w]->dc_dz[m][n] *
								image_part.image_object[0].images[kkkk]->pixels[m + i][n + j];
							//image_part.image_padding_object[zzzz].padding_images[kkkk]->padding_pixels[m + i][n + j];
						}
					}
					kernal_object[k]->kernals[w]->weight[i][j] -= lamda*delta;
				}
			}

			if (nnnn == kernal_1_D / image_D)
			{
				zzzz++;
				nnnn = 0;
			}

			nnnn++;
			kkkk++;

			if (kkkk == image_D) {
				kkkk = 0;
			}
		}
	}



}

void convolution_1::print()
{
	for (size_t i = 0; i < feature_1_number; i++)
	{
		for (size_t j = 0; j < feature_1_D; j++)
		{
			for (size_t k = 0; k < feature_1_H; k++)
			{
				for (size_t w = 0; w < feature_1_W; w++)
				{
					cout << feature_object[i]->feature_maps[j]->output[k][w];
				}
			}
		}
	}


	for (size_t i = 0; i < feature_1_number; i++)
	{
		for (size_t j = 0; j < feature_1_D; j++)
		{
			for (size_t k = 0; k < feature_1_H; k++)
			{
				for (size_t w = 0; w < feature_1_W; w++)
				{
					cout << feature_object[i]->feature_maps[j]->output[k][w];
				}
			}
		}
	}





}

//----------------------------------------------------------------------------

void  kernal::creat_kernal_1()
{
	float sign = -1;
	float random;

	weight = new long double*[F_kernal_1];
	for (int i = 0; i < F_kernal_1; i++)
		weight[i] = new long double[F_kernal_1];

	for (int i = 0; i<F_kernal_1; i++)
	{
		for (size_t j = 0; j < F_kernal_1; j++)
		{
			random = (float(rand()) / float(RAND_MAX)) / 2.f;
			random *= sign;
			sign *= -1;
			weight[i][j] = random;
		}
	}
}

void  kernal_layer::creat_kernal_layer()
{
	int i;
	kernals = new kernal*[kernal_1_D];

	for (i = 0; i<kernal_1_D; i++)
	{
		kernals[i] = new kernal;
		kernals[i]->creat_kernal_1();
	}
}

void  feature_map::creat_feature()
{
	float sign = -1;
	float random;

	// i=°ª«×
	// j=¼e«×

	int HH = feature_1_H;
	int WW = feature_1_W;

	output = new long double*[WW];
	for (int i = 0; i < HH; i++)
		output[i] = new long double[WW];

	// for differential
	output_diff = new long double*[WW];
	for (int i = 0; i < HH; i++)
		output_diff[i] = new long double[WW];

	// for delta
	dc_dz = new long double*[WW];
	for (int i = 0; i < HH; i++)
		dc_dz[i] = new long double[WW];

}

void  feature_layer::creat_feature_layer()
{
	int i;
	feature_maps = new feature_map*[feature_1_D];

	for (i = 0; i<feature_1_D; i++)
	{
		feature_maps[i] = new feature_map;
		feature_maps[i]->creat_feature();
	}
}
