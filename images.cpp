

 

#include"images.h"
#include<iostream>
#include"Defaults.h"

using namespace std;


void image_part::padding_1() {

	for (size_t k = 0; k < image_D; k++)
	{
		for (size_t i = 1; i < image_H + 1; i++)
		{
			for (size_t j = 1; j < image_W + 1; j++)
			{
				image_padding_object[0].padding_images[k]->padding_pixels[i][j] =
					image_object[0].images[k]->pixels[i - 1][j - 1];
			}
		}
	}
}

void image_part::print() {

	for (size_t i = 0; i < image_D; i++)
	{
		for (size_t j = 0; j < image_H; j++)
		{
			for (size_t k = 0; k < image_W; k++)
			{
				cout << image_object[0].images[i]->pixels[j][k];
			}
			cout << endl;
		}
	}
};

void image_part::initialize() {

	image_object[0].creat_image_layer();
	image_padding_object[0].creat_image_padding_layer();
};


// 由此可輸入 pixel 值

void image_part::get_pixel() {

	for (size_t i = 0; i < image_D; i++)
	{
		for (size_t j = 0; j < image_H; j++)
		{
			for (size_t k = 0; k < image_W; k++)
			{
				image_object[0].images[i]->pixels[j][k] = 0.1;
			}
		}
	}
};

void  image::creat_image_1()
{
	pixels = new long double*[image_W];
	for (int i = 0; i < image_H; i++)
		pixels[i] = new long double[image_W];
}

void image_layer::creat_image_layer()
{
	int i;

	//number_feature_layer_matrix =  5*3

	images = new image*[image_D];

	for (i = 0; i<image_D; i++)
	{
		images[i] = new image;
		images[i]->creat_image_1();
	}
}

void image_padding::creat_image_padding_1() {

	// i=高度
	// j=寬度

	int ww = image_W + 2;
	int hh = image_H + 2;

	padding_pixels = new long double*[ww];
	for (int i = 0; i < hh; i++)
		padding_pixels[i] = new long double[ww];

	for (size_t i = 0; i < ww; i++)
	{
		for (size_t j = 0; j < hh; j++)
		{
			padding_pixels[i][j] = 0;
		}
	}
}

void image_padding_layer::creat_image_padding_layer() {

	int i;

	//number_feature_layer_matrix =  5*3

	padding_images = new image_padding*[image_D];

	for (i = 0; i<image_D; i++)
	{
		padding_images[i] = new image_padding;
		padding_images[i]->creat_image_padding_1();
	}
}









