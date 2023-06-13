#pragma once
//Game Variable Library


namespace GVLib {

	//variables for change

	


	class Movespeed
	{
	public:
		float movespeed = 3.0f;
	};


}
namespace MapTransition{
	int hPos;
	int vPos;

	void TransportPosition(int hPosition,int vPosition)
	{
		hPos = hPosition;
		vPos = vPosition;
		Vector2 TransPos = { hPosition, vPosition };
	}
}
