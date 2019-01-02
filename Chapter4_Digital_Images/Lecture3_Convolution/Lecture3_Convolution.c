#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "BMPImage.h"

RGB get_color(RGB* rgb_array, int width, int height, int i, int j)
{
	// repeated boundary
	//if (i < 0) i += width;
	//if (j < 0) j += height;

	//i = i % width;
	//j = j % height;

	// copy boundary
	if (i < 0) i = 0;
	if (j < 0) j = 0;
	if (i > width - 1)  i = width - 1;
	if (j > height - 1) j = height - 1;

	// 2D to 1D index
	const int ix = i + width * j;

	assert(ix >= 0);
	assert(ix < width*height);

	return rgb_array[ix];
}

void clip(RGB * rgb, float min, float max)
{
	if (rgb->red < min) rgb->red = min;
	if (rgb->green < min) rgb->green = min;
	if (rgb->blue < min) rgb->blue = min;

	if (rgb->red > max) rgb->red = max;
	if (rgb->green > max) rgb->green = max;
	if (rgb->blue > max) rgb->blue = max;
}

void main()
{
	int res_x, res_y;		// width, height (+ depth in 3D images)

	RGB *rgb_array = NULL;	//unsigned char* rgb_array = NULL;
	readBMP24("tree.bmp", &res_x, &res_y, &rgb_array);

	RGB *rgb_temp = (RGB*)malloc(sizeof(RGB)*res_x*res_y);

	// convolution matrix
	float conv_mat[3][3] = { -1, -1, -1,
	  					     -1,  8, -1,
							 -1, -1, -1 };

	/*for (int sub_j = 0; sub_j < 3; sub_j++)
	for (int sub_i = 0; sub_i < 3; sub_i ++)
	{ 
	    conv_mat[sub_i][sub_j] /= 16.0f;
	}*/

	for (int j = 0; j < res_y; j++)
		for (int i = 0; i < res_x; i++)
		{
			RGB color_temp = { 0.0f, 0.0f, 0.0f };

			for (int sub_j = 0; sub_j < 3; sub_j++)
				for (int sub_i = 0; sub_i < 3; sub_i++)
				{
					RGB color_sub = get_color(rgb_array, res_x, res_y, i + sub_i - 1, j + sub_j - 1);

					color_sub.red *= conv_mat[sub_j][sub_i];
					color_sub.green *= conv_mat[sub_j][sub_i];
					color_sub.blue *= conv_mat[sub_j][sub_i];

					color_temp.red += color_sub.red;
					color_temp.green += color_sub.green;
					color_temp.blue += color_sub.blue;
				}
				
			clip(&color_temp, 0.0f, 1.0f);
			rgb_temp[i + res_x * j] = color_temp;
		}

	writeBMP24("output.bmp", res_x, res_y, rgb_temp);

	free(rgb_array);
	free(rgb_temp);
}
