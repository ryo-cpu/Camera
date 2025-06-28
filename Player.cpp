#include "Player.h"

bool Player::Input()
{
    bool isInput = false;
	VECTOR move=VGet(0,0,0);
	float targetAngle =0.0f; // ラジアン角

	if (CheckHitKey(KEY_INPUT_RIGHT))
	{

		VECTOR R = VGet(-1, 0, 0);
		R = VTransformSR(R, MGetRotY(GetDir().y));
		if (NowAnimTime >= AnimTotalTime)
		{
			SetAnimType(1);
		}
		move = VAdd(R, move);
		isInput = true;

	}// 画面をクリア
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		VECTOR L = VGet(1, 0, 0);
		L = VTransformSR(L, MGetRotY(GetDir().y));
		move = VAdd(L, move);
		if (NowAnimTime >= AnimTotalTime)
		{
			SetAnimType(1);
		}

		isInput = true;

	}
	if (CheckHitKey(KEY_INPUT_UP))
	{
		VECTOR F = VGet(0, 0, -1);
		F = VTransformSR(F, MGetRotY(GetDir().y));
		move = VAdd(F, move);
		if (NowAnimTime >= AnimTotalTime)
		{
			SetAnimType(1);
		}

		isInput = true;

	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		VECTOR D = VGet(0, 0, 1);
		D = VTransformSR(D, MGetRotY(GetDir().y));
		move = VAdd(D, move);
		if (NowAnimTime >= AnimTotalTime)
		{
			SetAnimType(1);
		}

		isInput = true;
	}
	if (isInput&&VSize(move)!=0) 
	{
		move = VNorm(move);         // 正規化（方向だけを抽出）
		move = VScale(move,20);     // スピードを乗算
		float targetAngle = atan2f(move.x, -move.z); // ラジアン角
		MV1SetRotationXYZ(Img, VGet(0, -targetAngle, 0));

	}
	else
	{
		MV1SetRotationXYZ(Img, VGet(0, Dir.y, 0));

	}
    if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
    {
        SetAnimType(4);
    }
	
	
	SetMove(move);
    return isInput;
}

void Player::Update()
{
	
    AnimUpdate();
    ////位置の更新
    SetPos(VAdd(Pos, Move));
	if (AnimType == 4)
	{
		SetAttackCollison(VAdd(Pos, VGet(0, 100, 0)), 30.f);
		DrawSphere3D(AttackCollison.GetPos(), AttackCollison.GetSphereSize(), 16, GetColor(200, 255, 255), GetColor(0, 0, 0), TRUE);

	}
	SetCollison(VAdd(Pos,VGet(0,100,0)), 40.0f);


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
