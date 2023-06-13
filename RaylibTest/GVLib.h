#pragma once
//Game Variable Library


namespace GVLib {

	//variables for change

	


	class Movespeed
	{
	public:
		float movespeed = 3.0f;
	};

	bool IsAtBounds_H = false;
	bool IsAtBounds_V = false;


	float Clamp(float value, float min, float max)
	{
		if (value < min)
			return min;
		if (value > max)
			return max;
		return value;
	}


}

