#pragma once
#include"DxLib.h"
class Player
{
private:
	VECTOR Pos;
	VECTOR Dir;
	float Speed;
	float SphereSize;
	int Img;

public:
	int 	GetImg();
	void    SetImg(int Img);
	VECTOR  GetPos();
	void    SetPos(VECTOR Pos);
	VECTOR  GetDir();
	void    SetDir(VECTOR Dir);
	float   GetSpeed();
	void    SetSpeed(float Speed);
	float   GetSphereSize();
	void    SetSphereSize(float SpheereSize);
	void    Update();
	void    Draw();

};

