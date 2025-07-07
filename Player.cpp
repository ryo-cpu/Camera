#include "Player.h"

Player::Player()
{
	SetCollison(VAdd(Pos, VGet(0, 100, 0)), 40.0f);
	IsHit = false;
}

bool Player::Input()
{
    bool isInput = false;
	VECTOR move=VGet(0,0,0);
	float targetAngle =0.0f; // ラジアン角

	if (CheckHitKey(KEY_INPUT_RIGHT))
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
	if (CheckHitKey(KEY_INPUT_LEFT))
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
	if (CheckHitKey(KEY_INPUT_UP))
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
	if (CheckHitKey(KEY_INPUT_DOWN))
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

void Player::Update()
{
	
    AnimUpdate();
    
	SetPos(VAdd(Pos, Move));
	if (AnimType == Kick)
	{
		VECTOR AttackPos = VGet(0, 100, -100);
		AttackPos=VTransformSR(AttackPos, MGetRotY(GetDir().y));
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
	MoveCollison(Move);
	LiveCount++;
}

Sphere_Collision Player::GetAttackCollison()
{
	return AttackCollison;
}

void Player::SetAttackCollison(VECTOR Pos, float size)
{
	AttackCollison.SetPos(Pos);
	AttackCollison.SetSphereSize(size);
}

bool Player::GetIsHit()
{
	return IsHit;
}

void Player::SetIsHit(bool ishit)
{
	IsHit = ishit;
}
