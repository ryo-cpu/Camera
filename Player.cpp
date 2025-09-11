#include "Player.h"
#include<cmath>

Player::Player()
{
	SetCollison(VAdd(Pos, VGet(0, 100, 0)), 40.0f);
	MaxHp = 300;
	Hp = MaxHp;
	Attack = 10;
	InSpecialMove = false;
	IsHit = false;
	InRolling = false;
	IsActiveInput = true;
	Grand = VGet(0, 0, 0);
}

bool Player::Input()
{
    bool isInput = false;
	VECTOR move=VGet(0,0,0);
	float targetAngle =0.0f; // ラジアン角

	if (CheckHitKey(KEY_INPUT_D))
	{

		VECTOR R = VGet(-1, 0, 0);
		R = VTransformSR(R, MGetRotY(GetDir().y));
		if (AnimType!=Ran||!IsAnim)
		{
			SetAnimType(Ran);
		}
		move = VAdd(R, move);
		isInput = true;

	}// 画面をクリア
	if (CheckHitKey(KEY_INPUT_A))
	{
		VECTOR L = VGet(1, 0, 0);
		L = VTransformSR(L, MGetRotY(GetDir().y));
		move = VAdd(L, move);
		if (AnimType != Ran || !IsAnim)
		{
			SetAnimType(Ran);
		}

		isInput = true;

	}
	if (CheckHitKey(KEY_INPUT_W))
	{
		VECTOR F = VGet(0, 0, -1);
		F = VTransformSR(F, MGetRotY(GetDir().y));
		move = VAdd(F, move);
		if (AnimType != Ran || !IsAnim)
		{
			SetAnimType(Ran);
		}

		isInput = true;

	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		VECTOR D = VGet(0, 0, 1);
		D = VTransformSR(D, MGetRotY(GetDir().y));
		move = VAdd(D, move);
		if (AnimType != Ran || !IsAnim)
		{
			SetAnimType(Ran);
		}

		isInput = true;
	}
	if (CheckHitKey(KEY_INPUT_J))
	{
		InRolling = true;
		SetAnimType(Roll);
	}
	if (isInput&&VSize(move)!=0) 
	{
		move = VNorm(move);         // 正規化（方向だけを抽出）
		move = VScale(move,10);     // スピードを乗算
		float targetAngle = atan2f(move.x, -move.z); // ラジアン角
		MV1SetRotationXYZ(Img, VGet(0, -targetAngle, 0));
		
	}
	else
	{
		MV1SetRotationXYZ(Img, VGet(0, Dir.y, 0));

	}
    if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
    {
        SetAnimType(Kick);
    }
	
	SetMove(move);
	
    return isInput;
}

void Player::Update(float deltaTime)
{
	
	
	
	if (Grand.y < Pos.y)
	{
		Pos = VAdd(Pos, G);

		Pos.y = Pos.y < 0 ? 0 : Pos.y;
	 }

	if (AnimType == Kick && (NowAnimTime >= 30.0f && NowAnimTime <= AnimTotalTime))
	{
		VECTOR AttackPos = VGet(0, 100, -200);
		AttackPos = VTransformSR(AttackPos, MGetRotY(GetDir().y));
		SetAttackCollison(VAdd(Pos, AttackPos), 30.f);
		DrawSphere3D(AttackCollison.GetPos(), AttackCollison.GetSphereSize(), 16, GetColor(200, 255, 255), GetColor(0, 0, 0), TRUE);

	}
	else
	{
		AttackCollison = {};
	}
	if (Collison.GetSphereSize() == 0)
	{
		DrawSphere3D(AttackCollison.GetPos(), AttackCollison.GetSphereSize(), 16, GetColor(200, 255, 255), GetColor(0, 0, 0), TRUE);

	}
	if (AnimType == Hit &&NowAnimTime >= AnimTotalTime)
	{
		SetAnimType(Stop);
	}
	if (InRolling)
	{
		InRolling = Rolling();
	}
	AnimUpdate(deltaTime);
	MoveCollison(Move);
	SetPos(VAdd(Pos, Move));
	if (LiveTime - LastDamageTime >= 5.0f&&GetHp()<MaxHp && fabs(fmod(LiveTime - LastDamageTime, 0.1f)) < 0.01f)
	{
	
		SetHp(GetHp() +5);
	}
	LiveTime+=deltaTime;
}



void Player::SetGrand(VECTOR grand)
{
	Grand = grand;
}

bool Player::GetIsHit()
{
	return IsHit;
}

void Player::SetIsHit(bool ishit)
{
	IsHit = ishit;
}

bool Player::GetInSpecialMove()
{
	return InSpecialMove;
}

void Player::SetInSpecialMove(bool inSpecialMove)
{
	InSpecialMove = inSpecialMove;
	
}

void Player::SetLastDamageTime()
{
	LastDamageTime = GetLiveTime();
}

float Player::GetLastDamageTime()
{
	return LastDamageTime;
}

bool Player::Rolling()
{
	if (VSize(Move) == 0)
	{
		
		Move = VTransformSR(VGet(0, 0, 1), MGetRotY(GetDir().y));
	}
	else
	{
		Move = VNorm(Move);
		Move = VTransformSR(Move, MGetRotY(GetDir().y));
	}
	return IsAnim;
}



void Player::SpecialMove(float deltaTime)
{ 
	
	
}
