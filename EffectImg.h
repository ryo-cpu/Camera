#pragma once
#include "EffekseerForDXLib.h"
class EffectImg
{
int Img;
public:
	EffectImg(char* Link);///デフォルト読み込み　基本等倍
	EffectImg(char* Link, float Size);///サイズ変更読み込み
	int GetImg();

};

