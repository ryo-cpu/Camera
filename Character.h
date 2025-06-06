#pragma once
#include"DxLib.h"

class Character
{
protected:
	VECTOR Pos;
	VECTOR Dir;
	float Speed;
	/// <summary>
	/// ���a�\�L
	/// </summary>
	float SphereSize;
	int Img;
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
    virtual	void   Update();
 	void    Draw();
	static bool Collison(Character C1, Character C2);
};

