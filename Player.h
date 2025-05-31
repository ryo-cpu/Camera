#pragma once
#include"DxLib.h"
class Player
{
private:
	VECTOR Pos;
	VECTOR Dir;
	float Speed;
	float SphereSize;
	int Img ;
	float Scale;
public:
	int 	GetImg();
	void    SetImg(int img);
	VECTOR  GetPos();
	void    SetPos(VECTOR pos);
	VECTOR  GetDir();
	void    SetDir(VECTOR dir);
	float   GetSpeed();
	void    SetSpeed(float speed);
	float   GetSphereSize();
	void    SetSphereSize(float sphereSize);
	float   GetScale();
	void    SetScale(float scale);
	void    Update();
	void    Draw();

};

