#pragma once
#ifndef ACTIVATION_H_
#include<iostream>

using namespace std;

 static double sigmoid( double x)
{
	return 1 / (1 + exp(-x));
}

static double relu( double x)
{
	//return log(1 + exp(x));
	return 1 / (1 + exp(-x));
}

 static double de_relu( double x)
{
	return (1 / (1 + exp(-x)))*(1 - (1 / (1 + exp(-x))));
}







#endif // !ACTIVATION_H_
