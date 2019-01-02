#include "ImageConvolution.h"

int main()
{
	ImageConvolution img_conv;
	img_conv.convolute(Image("tree.bmp")).write("output.bmp");
}
