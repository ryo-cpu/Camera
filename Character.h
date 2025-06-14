#pragma once
#include"DxLib.h"
#include"Sphere_Collision.h"
class Character
{
protected:
	VECTOR Pos;
	VECTOR Dir;
	VECTOR Move;
	float Speed;
	/// <summary>
	/// ”¼Œa•\‹L
	/// </summary>
	float SphereSize;
	int Img;
	float Scale;
	Sphere_Collision Collison;
public:
	int 	GetImg();
	void    SetImg(int img);
	VECTOR  GetPos();
	void    SetPos(VECTOR pos);
	VECTOR  GetDir();
	void    SetDir(VECTOR dir);
	VECTOR  GetMove();
	void    SetMove(VECTOR move);
	float   GetSpeed();
	void    SetSpeed(float speed);
	float   GetSphereSize();
	void    SetSphereSize(float sphereSize);
	float   GetScale();
	void    SetScale(float scale);
    virtual	void   Update();
 	void    Draw();
	void    Turn(VECTOR Power);
};

