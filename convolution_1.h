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
