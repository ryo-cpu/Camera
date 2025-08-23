#pragma once
#include"DxLib.h"
#include"Sphere_Collision.h"
#include<cmath>
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
	int AnimIndex;
	float AnimTotalTime;
	float NowAnimTime;
	float AnimSpeed;
	bool IsAnim;
	int LiveCount;
	int StartLiveCount;
	int MaxHp;
	bool isDraw;
public:
	Character();
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
	void    SetAnimIndex(int animIndex);
	int     GetAnimIndex();
	void    SetAnimType(int animType);
	int     GetAnimType();
	float   GetNowAnimTime();
	void    SetNowAnimTime(float nowanimtime);
	void    SetTotalAnimTime(float animtotalTime);
	float   GetTotalAnimTime();
	void    SetAnimSpeed(float Speed);
	float   GetAnimSpeed();
	void    AnimUpdate();
	void    MoveUpdate(VECTOR move);
    virtual	void   Update();
 	void    Draw();
	void    Turn(VECTOR Power);
	Sphere_Collision GetCollison();
	void SetCollison(VECTOR Pos, float size);
	void MoveCollison(VECTOR move);
	int GetLiveCount();
	int GetStartLiveCount();
	void SetStartLiveCount(int count);
	int GetMaxHp();
	void SubHp(int Damge);
	void SetisDraw(bool Flg);
	bool GetisDraw();
};

