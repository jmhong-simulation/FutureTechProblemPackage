#include <stdio.h>
#include "BMPImage.h"

void color_to_gray(const int sep, const int width, const int height, unsigned char *rgb_arr)
{
	for (int h = height - 1; h >= 0; --h)
	{
		for (int w = 0; w < width; ++w)
		{
			if (w < sep)
			{
				const unsigned char red = rgb_arr[(w + width * h) * 3 + 0]; // 0 <= red_uc <= 255
				const unsigned char green = rgb_arr[(w + width * h) * 3 + 1];
				const unsigned char blue = rgb_arr[(w + width * h) * 3 + 2];

				const double red_real = red / 255.0;    // 0.0 <= red_real <= 1.0
				const double green_real = green / 255.0;
				const double blue_real = blue / 255.0;

				double ave = (red_real + green_real + blue_real) / 3.0 * 1.5;

				if (ave > 1.0) ave = 1.0; // clip

				rgb_arr[(w + width * h) * 3 + 0] = (unsigned char)(ave * 255.0);
				rgb_arr[(w + width * h) * 3 + 1] = (unsigned char)(ave * 255.0);
				rgb_arr[(w + width * h) * 3 + 2] = (unsigned char)(ave * 255.0);
			}
		}
	}
}

int main()
{
	printf("Hello, World!\n");

	int width, height;
	unsigned char *rgb_arr = NULL;
	readBMP24("colors.bmp", &width, &height, &rgb_arr);
	printf("%d %d\n", width, height);

	// back up original input image
	unsigned char *rgb_arr_backup = (unsigned char*)malloc(sizeof(unsigned char) * width * height * 3); // *3 = rgb
	for (int i = 0; i < width * height * 3; ++i)
		rgb_arr_backup[i] = rgb_arr[i];

	// making image sequence
	for (int tr = 0; tr < width; ++tr)
	{
		//color_to_gray(sep, width, height, rgb_arr);

		for (int h = 0; h < height; ++h)
		for (int w = 0; w < width; ++w)
		{ 
			int w_tr = w - tr;

			if (w_tr < 0) w_tr += width;

			for (int c = 0; c < 3; ++c)
				rgb_arr[(w + width * h) * 3 + c] = rgb_arr_backup[(w_tr + width * h) * 3 + c];
		}

		char filename[255];
		sprintf(filename, "tr_%05d.bmp", tr);
		writeBMP24(filename, width, height, rgb_arr);

		//// restore rgb_arr to original
		//for (int i = 0; i < width * height * 3; ++i)
		//	rgb_arr[i] = rgb_arr_backup[i];
	}

	free(rgb_arr_backup);
	free(rgb_arr);
}
