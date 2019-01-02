#pragma once

#include "BMPImage.h"
#include <string>
#include <vector>
#include <cassert>

class Image
{
public:
	int width = 0, height = 0;

	std::vector<RGB> rgb_array;

	Image(const Image & img)
		: width(img.width), height(img.height)
	{
		rgb_array = img.rgb_array;
	}

	Image(const std::string & filename)
	{
		read(filename);
	}

	void read(const std::string & filename)
	{
		RGB * rgb_temp = new RGB[width * height];

		readBMP24(filename.c_str(), &width, &height, &rgb_temp);
		
		rgb_array.resize(width * height);
		for (int i = 0; i < width * height; ++i)
			rgb_array[i] = rgb_temp[i];

		delete[] rgb_temp;
	}

	void write(const std::string & filename)
	{
		writeBMP24(filename.c_str(), width, height, rgb_array.data());
	}

	RGB & getColor(const int & _i, const int & _j)
	{
		int i(_i), j(_j);

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

	const RGB & getColor(const int & _i, const int & _j) const
	{
		int i(_i), j(_j);

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

};
