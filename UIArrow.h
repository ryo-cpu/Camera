#pragma once
#include "Dxlib.h"
class UIArrow
{
private:
	float TopX, TopY;
	float Root1X, Root1Y;
	float Root2X, Root2Y;
public:
   void  Make(VECTOR Target,VECTOR Root);
   void	 Draw();
};

