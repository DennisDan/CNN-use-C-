#pragma once
#ifndef IMAGE_H_

struct image {
	long double **pixels;
	void creat_image_1();
};

struct image_layer {
	image **images;
	void creat_image_layer();
};

//*************************************

struct image_padding {
	long double **padding_pixels;
	void creat_image_padding_1();
};

struct image_padding_layer {
	image_padding **padding_images;
	void creat_image_padding_layer();
};

//*************************************

class image_part {

public:

	friend class convolution_1;

	//*************************************
	image_layer image_object[1];
	image_padding_layer image_padding_object[1];

	void get_pixel();
	void initialize();
	void padding_1();
	void print();
};





#endif // !IMAGE_H_
