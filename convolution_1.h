#pragma once
#ifndef CONVOLUTION__H_

#include"Defaults.h"
#include"images.h"
#include<vector>

using namespace std;


struct kernal {
	long double **weight;
	void creat_kernal_1();
};
struct kernal_layer {
	kernal **kernals;
	void creat_kernal_layer();
};

//----------------------------------------------------------------------------
struct feature_map {
	long double **output;
	long double **output_diff;
	long double **dc_dz;
	void creat_feature();
};
struct feature_layer {
	feature_map **feature_maps;
	void creat_feature_layer();
};

class convolution_1  
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

public:
 
	vector<kernal_layer*> kernal_object;
	vector<feature_layer*> feature_object;


	// kernal_layer kernal_object[number_kernal_1];
    // feature_layer feature_object[feature_1_number];

	// kernal_layer kernal_object ;
	// feature_layer feature_object ;


	convolution_1();

	void initialize();
	void print();
	void first_convolution(image_part image_part);
	void updata_weight(image_part image_part);


	friend class pooling_1;
};







#endif // !CONVOLUTION__H_
