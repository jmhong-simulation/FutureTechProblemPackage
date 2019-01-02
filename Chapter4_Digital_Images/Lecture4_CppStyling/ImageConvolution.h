#pragma once

#include "Image.h"

class ImageConvolution
{
public:
	// convolution matrix (edge detection)
	float conv_mat[3][3] = { -1, -1, -1,
							 -1,  8, -1,
							 -1, -1, -1 };

	/*for (int sub_j = 0; sub_j < 3; sub_j++)
	for (int sub_i = 0; sub_i < 3; sub_i ++)
	{
		conv_mat[sub_i][sub_j] /= 16.0f;
	}*/

	Image convolute(const Image & input_img) const
	{
		Image temp_img(input_img);

		for (int j = 0; j < input_img.height; j++)
			for (int i = 0; i < input_img.width; i++)
			{
				RGB color_temp = { 0.0f, 0.0f, 0.0f };

				for (int sub_j = 0; sub_j < 3; sub_j++)
					for (int sub_i = 0; sub_i < 3; sub_i++)
					{
						RGB color_sub = input_img.getColor(i + sub_i - 1, j + sub_j - 1);

						color_sub *= conv_mat[sub_j][sub_i];
						color_temp += color_sub;
					}

				temp_img.getColor(i, j) = color_temp.getClamped(0.0f, 1.0f);
			}

		return temp_img;
	}
};