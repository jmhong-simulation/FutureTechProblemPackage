#include <stdio.h>

#include "BMPImage.h"

bool is_circle(int x, int y)
{
	const int x_c = 550;
	const int y_c = 330;
	const int radius = 150;

	const int f = (x - x_c)*(x - x_c) + (y - y_c)*(y - y_c) - radius * radius;

	if (f <= 0) return true;
	else return false;
}

int main()
{
	int width, height;
	unsigned char *rgb_arr = NULL;
	readBMP24("colors.bmp", &width, &height, &rgb_arr);

	printf("%d %d\n", width, height);

	for(int h = 0; h < height; ++h)
		for (int w = 0; w < width; ++w)
		{
			rgb_arr[0 + w * 3 + 3 * width * h] = 0;
			//rgb_arr[1 + w * 3 + 3 * width * h] = 0;
			rgb_arr[2 + w * 3 + 3 * width * h] = 0;

			//float gray = 0.0f;

			//for (int c = 0; c < 3; ++c) // RGB
			//{
			//	gray += rgb_arr[c + w * 3 + 3 * width * h];
			//}

			//gray /= 3.0f;
			//gray *= 0.4f;

			//if (!is_circle(w, h))
			//{
			//	for (int c = 0; c < 3; ++c) // RGB
			//	{
			//		rgb_arr[c + w * 3 + 3 * width * h] = (char)gray;
			//	}
			//}
		}

	writeBMP24("tree_circle.bmp", width, height, rgb_arr);
}
