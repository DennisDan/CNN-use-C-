 

#include<iostream>
#include<vector>
#include<time.h>
using namespace std;



#include"images.h"
#include"convolution_1.h"
#include"pooling_1.h"
#include"convolution_2.h"
#include"pooling_2.h"
#include"interface.h"
#include"FULL_connected.h"
#include"Defaults.h"

//******* image


 int image_D = 3;
 int image_W = 100;
 int image_H = 100;
 real lamda = 0.8;


//****** convolution_1


 int F_kernal_1 = 3;                                        // fiter大小
 int kernal_1_D = image_D;
 int number_kernal_1 = 5;


 int  stride_kernal_1 = 1;
 int  feature_1_D = kernal_1_D;
 int	 feature_1_H = (image_H - F_kernal_1 + 2) / stride_kernal_1 + 1;               //(h - F) / s + 1;
 int	 feature_1_W = (image_W - F_kernal_1 + 2) / stride_kernal_1 + 1;                // (w - F) / s + 1;
 int  feature_1_number = number_kernal_1;


// ********* using mean pooling 

 int F_pooling_1 = 2;                              //pooling_filter
 int pooling_D_1 = feature_1_D;
 int stride_pooling_1 = 2;
 int pooling_W_1 = (feature_1_W - F_pooling_1) / stride_pooling_1 + 1;
 int pooling_H_1 = (feature_1_H - F_pooling_1) / stride_pooling_1 + 1;
 int pooling_1_number = feature_1_number;


//**********  convolution_2
 int F_kernal_2 = 3;                                     // fiter大小
 int kernal_2_D = pooling_D_1*pooling_1_number;
 int number_kernal_2 = 10;
 int  stride_kernal_2 = 1;
 int  feature_2_D = kernal_2_D;
 int	 feature_2_H = (pooling_H_1 - F_kernal_2 + 2) / stride_kernal_2 + 1;       //(h - F) / s + 1;
 int	 feature_2_W = (pooling_W_1 - F_kernal_2 + 2) / stride_kernal_2 + 1;              // (w - F) / s + 1;
 int  feature_2_number = number_kernal_2;


// **********using mean pooling 

 int F_pooling_2 = 2;                          //pooling_filter
 int pooling_D_2 = feature_2_D;
 int stride_pooling_2 = 2;
 int pooling_W_2 = (feature_2_W - F_pooling_2) / stride_pooling_2 + 1;
 int pooling_H_2 = (feature_2_H - F_pooling_2) / stride_pooling_2 + 1;
 int pooling_2_number = feature_2_number;


 int interface__number_layers = 1;
 int interface__number_neurons = (pooling_D_2*pooling_W_2*pooling_H_2*pooling_2_number);


//********** full_connected

 int full_connected_number_hidden_layers = 10;
 int full_connected_number_hidden_neurons = 10;
 int full_connected_number_output_neurons = 10;
 int full_connected_number_intput_neurons = 10;


 



int main()
{

	srand((unsigned)time(NULL));  //initialize time
// initialize all
	image_part aa;
	aa.initialize();
	aa.get_pixel();

	convolution_1 bb;
	bb.initialize();

	pooling_1 cc;
	cc.initialize();

	convolution_2 dd;
	dd.initialize();

	pooling_2 ee;
	ee.initialize();

	interface__ ff;
	ff.initialize();
	ff.giveValue(ee);

	full_connected gg;
	gg.initialize();


	vector<double> v;
	for (int i = 0; i < 10; i++)
		v.push_back(i*0.1);



	for (size_t i = 0; i < 30000; i++)
	{
		aa.padding_1();
		bb.first_convolution(aa);
		//a.print();	
		cc.first_pooling(bb);
		cc.creat_padding();
		//cc.print();		
		dd.second_convolution(cc);
		//dd.print();
		ee.second_pooling(dd);
		//ee.print();

		gg.forward_first(ff);
		gg.forward_hidden();
		gg.forward_output();
		gg.back_output_last_hidden(v);
		gg.back_hidden_input(ff, ee);

		ee.give_conv_2_delta(dd);
		dd.give_pooling_1_delta(cc);
		cc.give_conv_1_delta(bb);

		dd.updata_weight(cc);
		bb.updata_weight(aa);


		gg.print();



	}



	system("pause");

}