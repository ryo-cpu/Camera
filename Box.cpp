#include "Box.h"
const int MaxAlpha = 255;
const int MinAlpha = 0;
const int MaxColor = 255;
const int MinColor = 0;


Box::Box(float x, float y, int startAlpha)
{
	SizeX = x;
	SizeY = y;
	Alpha = startAlpha;
	Red = 0;
	Green = 0;
	Blue = 0;
}

void Box::SetAlpha(int alpha)
{
	if (alpha >= MaxAlpha)Alpha = 255;
	else if (alpha <= MinAlpha) Alpha = MinAlpha;
	else Alpha = alpha;
	
}

int Box::GetAlpha()
{
	
	return Alpha;
}

void Box::SetColor(int R, int G, int B)
{
	Red = R;
	Green = G;
	Blue = B;
}

void Box::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
	DrawBox(0, 0, SizeX, SizeY, GetColor(Red, Green, Blue), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
