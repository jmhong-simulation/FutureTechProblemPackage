#include <stdio.h>
#include "BMPImage.h"

int main()
{
	printf("Hello, World!\n");

	int width, height;
	unsigned char *rgb_arr = NULL;
	readBMP24("colors.bmp", &width, &height, &rgb_arr);
	printf("%d %d\n", width, height);

	//for (int h = 0; h < height; ++h)
	for(int h = height - 1; h >= 0; --h)
	{
		for (int w = 0; w < width; ++w)
		{
			if (w < width / 2)
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

	writeBMP24("colors_gray.bmp", width, height, rgb_arr);
}
