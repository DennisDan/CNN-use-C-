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


	// �@�hkernal layer ���ܦh�� kernal matrixs   =>  number_kernal_matrix
	// �C�� kernal matrix ��3*3��weight   => number_kernal_dim


	// �ۦ�]�w�Ĥ@�h��
	//  5 * 3 ��kernal matrix  5=5�ӥ���kernal  3=RGB
	//  �C�� matrix 3*3
	//  output feature layer ��5*3��matrix �p�שM kernal matrix �̼�
	//  output feature �C�� W=(w-F)/s  +  1  w=image �j�p   F=filter �j�p
	//  output feature �C�� H=(h-F)/s  +  1  s=stride



	//----------------------------------------------------------------------------
	// �@�hkernal layer 
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
