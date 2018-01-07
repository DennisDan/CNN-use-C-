#pragma once
#ifndef CONVOLUTION_2_H_
#include"Defaults.h"
#include"pooling_1.h"
#include<vector>

using namespace std;
struct kernal_conv_2 {
	long double **weight;
	void creat_kernal_1_conv_2();
};
struct kernal_layer_conv_2 {
	kernal_conv_2 **kernals;
	void creat_kernal_layer_conv_2();
};

//----------------------------------------------------------------------------
struct feature_map_conv_2 {
	long double **dc_dz;
	long double **output_diff;
	long double **output;
	void creat_feature_conv_2();
};
struct feature_layer_conv_2 {
	feature_map_conv_2 **feature_maps;
	void creat_feature_layer_conv_2();
};



class convolution_2 //: public basic
{
private:


	// 一層kernal layer 有很多顆 kernal matrixs   =>  number_kernal_matrix
	// 每個 kernal matrix 有3*3個weight   => number_kernal_dim


	// 自行設定第一層有
	//  5 * 3 個kernal matrix  5=5個立體kernal  3=RGB
	//  每個 matrix 3*3
	//  output feature layer 有5*3個matrix 厚度和 kernal matrix 依樣
	//  output feature 每個 W=(w-F)/s  +  1  w=image 大小   F=filter 大小
	//  output feature 每個 H=(h-F)/s  +  1  s=stride



	//----------------------------------------------------------------------------
	// 一層kernal layer 
	//kernal_layer kernal_object[number_kernal_2];
	//feature_layer feature_object[feature_2_number];

	vector<kernal_layer_conv_2*> kernal_object;
	vector<feature_layer_conv_2*> feature_object;

public:
	convolution_2();
	void initialize();
	void print();
	void second_convolution(pooling_1 pooling_1);
	void updata_weight(pooling_1 pooling_1);
	void give_pooling_1_delta(pooling_1 pooling_1);
	friend class pooling_2;
};






#endif // !CONVOLUTION_2_H_
