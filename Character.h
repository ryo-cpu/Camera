#pragma once
#include<iostream>
#include<vector>
#include "DxLib.h"
#include "Sphere_Collision.h"
#include<cmath>
#include "EffectM.h"
#include "Capsule.h"
#include "ModelCheckers.h"

class Character
{
protected:
	VECTOR Pos;
	VECTOR Dir;
	/// <summary>
	/// 移動値
	/// </summary>
	VECTOR Move;
	/// <summary>
	/// dirにかけることでMoveを求める
	/// </summary>
	float Speed;
	/// <summary>
	/// モデルの格納
	/// </summary>
	int Img;
	/// <summary>
	/// モデルのスケール値
	/// </summary>
	float Scale;
	Sphere_Collision Collision;
	Sphere_Collision AttackCollision;
	std::vector<Capsule> CapsuleCollision;
	int Attack;
	int Hp;
	int AnimType;
	int AnimIndex;
	/// <summary>
	/// 現在再生されているアニメーションの終わりまでの時間
	/// </summary>
	float AnimTotalTime;
	/// <summary>
	/// アニメーションが再生されてからの時間
	/// </summary>
	float NowAnimTime;
	/// <summary>
	/// アニメーション再生スピード
	/// </summary>
	float AnimSpeed;
	bool IsAnim;
	/// <summary>
	/// キャラクターの存在した時間（キャラごとのタイマー）
	/// </summary>
	float LiveTime;
	/// <summary>
	/// 行動時間が決まっている行動をするとき開始を記録する
	/// </summary>
	float StartLiveTime;
	int MaxHp;
	bool isDraw;
	bool isUpdate;
public:
	Character();
	Character(int img);
	~Character();
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
	virtual void  Initial();
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
	void DrawCapsuleCollision();
	void UpdateCapsuleCollision();
	void UpdateCapsuleCollision(VECTOR move);
	void SetCapsuleCollisionRsize(float r);
    std::vector<Capsule> GetCapsuleCollision();
	VECTOR PushBackCapsuleCollison(Character &Move,Character &NotMove);
	bool isHitCaracters(Character A, Character B);
	VECTOR GetFramPos (const char* framName);
	Capsule SearchCapsule(const char* frameName);
	void DrawSearchCapusle(const char* frameName);
};

