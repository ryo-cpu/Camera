#pragma once
#include "DxLib.h"
class Box
{
	/// <summary>
	/// 画面左上を０、０としたときの右下の値
	/// </summary>
	float SizeX;
	/// <summary>
	/// 画面左上を０、０としたときの右下の値
	/// </summary>
	/// 
	float SizeY;
	/// <summary>
	/// BOXの透明度
	/// </summary>
	int Alpha;
	int Red;
	int Green;
	int Blue;
public:
	Box(float x, float y, int startAlpha);

	void SetAlpha(int alpha);
	int GetAlpha();
	/// <summary>
	/// RGB方式で０～２５５
	/// </summary>
	/// <param name="R"></param>
	/// <param name="G"></param>
	/// <param name="B"></param>
	void SetColor(int R, int G, int B);
	void Draw();
};

