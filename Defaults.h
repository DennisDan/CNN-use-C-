#pragma once
#ifndef DEFAULT_H_

typedef double real;

extern  int image_D;



extern  int image_W;
extern  int image_H;
extern  real lamda;


//******************************

extern  int F_kernal_1;
extern  int kernal_1_D;
extern  int number_kernal_1;
extern  int stride_kernal_1;
extern  int feature_1_D;
extern  int feature_1_H;
extern  int feature_1_W;
extern  int feature_1_number;


//************************************

extern  int F_pooling_1;
extern  int pooling_D_1;
extern  int stride_pooling_1;
extern  int pooling_W_1;
extern  int pooling_H_1;
extern  int pooling_1_number;

//***********************************
extern  int F_kernal_2;
extern  int kernal_2_D;
extern  int number_kernal_2;
extern  int stride_kernal_2;
extern  int feature_2_D;
extern  int feature_2_H;
extern  int feature_2_W;
extern  int feature_2_number;


// *************************************  using mean pooling  ***************************************
extern  int F_pooling_2;
extern  int pooling_D_2;
extern  int stride_pooling_2;
extern  int pooling_W_2;
extern  int pooling_H_2;
extern  int pooling_2_number;


//***********************************************************************************
extern  int interface__number_layers;
extern  int interface__number_neurons;

// full_connected
extern  int full_connected_number_hidden_layers;
extern  int full_connected_number_hidden_neurons;
extern  int full_connected_number_output_neurons;
extern  int full_connected_number_intput_neurons;





#endif // !DEFAULT_H_
