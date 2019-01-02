#pragma once

#include <algorithm>

class RGB
{
public:
	float red;
	float green;
	float blue;

	RGB getClamped(const float & min, const float & max) const
	{
		using namespace std;

		return { clamp(red, 0.0f, 1.0f), clamp(green, 0.0f, 1.0f), clamp(blue, 0.0f, 1.0f) };
	}

	RGB operator *= (const float& scalar)
	{
		this->red *= scalar;
		this->green *= scalar;
		this->blue *= scalar;

		return *this;
	}

	RGB operator += (const RGB& rgb_in)
	{
		this->red += rgb_in.red;
		this->green += rgb_in.green;
		this->blue += rgb_in.blue;

		return *this;
	}
};
