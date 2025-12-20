#include "EffectImg.h"

EffectImg::EffectImg(char* Link)
{
	Img = LoadEffekseerEffect(Link, 1.0f);
}

EffectImg::EffectImg(char* Link, float Size)
{
	Img = LoadEffekseerEffect(Link, Size);
}


int EffectImg::GetImg() const
{
	return Img;
}
