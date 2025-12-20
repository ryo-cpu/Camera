#pragma once
#include"DxLib.h"
#include"Sphere_Collision.h"
#include<cmath>
#include"EffectM.h"

class Character
{
protected:
	VECTOR Pos;
	VECTOR Dir;
	VECTOR Move;
	float Speed;
	int Img;
	float Scale;
	Sphere_Collision Collision;
	Sphere_Collision AttackCollision;
	int Attack;
	int Hp;
	int AnimType;
	int AnimIndex;
	float AnimTotalTime;
	float NowAnimTime;
	float AnimSpeed;
	bool IsAnim;
	float LiveTime;
	float StartLiveTime;
	int MaxHp;
	bool isDraw;
	bool isUpdate;
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
	void    AnimUpdate(float deltaTime);
	void    MoveUpdate(VECTOR move);
    virtual	void   Update(float deltaTime);
 	void    Draw();
	void    Turn(VECTOR RotatePower);
	Sphere_Collision GetCollision();
	void SetCollision(VECTOR Pos, float size);
	void MoveCollision(VECTOR move);
	float GetLiveTime();
	void  AddLiveTime(float PassedTime);
	float GetStartLiveTime();
	void SetStartLiveTime(float time);
	int GetMaxHp();
	void SubHp(int Damage);
	void SetisDraw(bool Flg);
	bool GetisDraw();
	Sphere_Collision GetAttackCollision();
	void SetAttackCollision(VECTOR Pos, float size);
	bool GetIsUpdate();
	void SetIsUpdate(bool isupdate);
	bool GetIsAnim();
};

