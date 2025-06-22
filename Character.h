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
	int Img;
	float Scale;
	Sphere_Collision Collison;
	int Attack;
	int Hp;
	int AnimType;
	float AnimTotalTime;
	float NowAnimTime;
	float AnimSpeed;
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
	float   GetScale();
	void    SetScale(float scale);
	void    SetAttack(int attack);
	int     GetAttack();
	void    SetHp(int hp);
	int     GetHp();
	void    SetAnimType(int animType);
	int     GetAnimType();
	float   GetNowAnimTime();
	void    SetNowAnimTime(float nowanimtime);
	void    SetTotalAnimTime(float animtotalTime);
	float   GetTotalAnimTime();
	void    SetAnimSpeed(float Speed);
	float   GetAnimSpeed();
	void    AnimUpdate();
    virtual	void   Update();
 	void    Draw();
	void    Turn(VECTOR Power);
};

