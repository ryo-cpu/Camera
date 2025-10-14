#include "Player.h"
#include<DxLib.h>

#include<cmath>



Player::Player()
{
	SetCollison(VAdd(Pos, VGet(0, 100, 0)), 40.0f);
	MaxHp = 40;
	Hp = MaxHp;
	Attack = 10;
	InSpecialMove = false;
	IsHit = false;
	InRolling = false;
	IsActiveInput = true;
	Grand = VGet(0, 0, 0);
}

bool Player::Input(Camera& camera)
{
    bool isInput = false;
	VECTOR move=VGet(0,0,0);
	float targetAngle =0.0f; // ƒ‰ƒWƒAƒ“Šp
	XINPUT_STATE* InputState=new XINPUT_STATE;
	int* XBuf=new int;
	int* YBuf=new int;
	SetJoypadDeadZone(DX_INPUT_PAD1, 0.35f);
	if (GetJoypadNum() == 0)
	{
		SetMove(move);
		return false;////PAD‚ªŒq‚ª‚Á‚Ä‚È‚¢‚Æƒ_ƒ‚¾
	}
	if (GetJoypadXInputState(DX_INPUT_PAD1,InputState))
	{
		SetMove(move);
		return false;
	}
	if (!InRolling)
	{
		if (InputState->ThumbRX >= 100 || InputState->ThumbRX <= -100)
		{

			float Rot= (InputState->ThumbRX) * 0.00001f;
			Turn(VGet(0, Rot, 0));
			VECTOR F = VScale(VGet(0, 0, 1),VSize(DefaultCamera));
			camera.AddTAngle(VGet(0, Rot, 0));
			VECTOR RotP = camera.GetTagetAngle();
			MATRIX RotX = MGetRotX(RotP.x);
			MATRIX RotY = MGetRotY(RotP.y);///Z‚Í‰ñ“]‚µ‚È‚¢
			MATRIX RotAll = MMult(RotX,RotY);
			camera.ResetOffset( VTransformSR(F, RotAll),Pos);
			camera.Look(Pos);

		}
		if (InputState->ThumbRY >= 100 || InputState->ThumbRY <= -100)
		{
		
			/*float Rot = (InputState->ThumbRY) * 0.00001f;
			VECTOR F = VScale(VGet(0, 0, 1), VSize(DefaultCamera));
			camera.GetTAngle(Pos);
			VECTOR RotP = camera.GetTagetAngle();
			
			camera.AddTAngle(VGet(Rot, 0, 0));
			if (RotP.x > 0&&RotP.x<1.75)
			{
				RotP = camera.GetTagetAngle();
			}
			
			MATRIX RotX = MGetRotX(RotP.x);
			MATRIX RotY = MGetRotY(RotP.y);///Z‚Í‰ñ“]‚µ‚È‚¢
			MATRIX RotAll = MMult(RotX, RotY);
			camera.ResetOffset(VTransformSR(F, RotAll),Pos);
			camera.Look(Pos);*/

		}
		VECTOR Dir = VGet(-(InputState->ThumbLX), 0, -(InputState->ThumbLY));
		Dir = VTransformSR(Dir, MGetRotY(GetDir().y));
		if (VSize(Dir) >= 100)
		{
			isInput = true;
			if (!IsAnim || AnimType == Stop)
			{
				SetAnimType(Ran);
			}
			move = VScale(Dir, 0.01f);
		}

		if ((InputState->Buttons[XINPUT_BUTTON_RIGHT_SHOULDER]) != 0)
		{
			if (VSize(move) == 0)
			{
				move = VTransformSR(VGet(0, 0, -1), MGetRotY(GetDir().y));
			}
			else
			{
				move = VNorm(move);
			}
			StartLiveTime = LiveTime;
			InRolling = true;
			SetAnimType(Roll);
			Collison = {};
		}
		if (isInput && VSize(move) != 0)
		{
			move = VNorm(move);         // ³‹K‰»i•ûŒü‚¾‚¯‚ð’Šoj
			move = VScale(move, 10);     // ƒXƒs[ƒh‚ðæŽZ
			float targetAngle = atan2f(-move.x, -move.z); // ƒ‰ƒWƒAƒ“Šp
			MV1SetRotationXYZ(Img, VGet(0, targetAngle, 0));

		}
		else
		{
			MV1SetRotationXYZ(Img, VGet(0, GetDir().y, 0));

		}
		if ((InputState->Buttons[XINPUT_BUTTON_B]) != 0)
		{

			SetAnimType(Kick);
		}
		if (InputState->Buttons[XINPUT_BUTTON_X] != 0)
		{
			InSpecialMove = true;
			StartLiveTime = LiveTime;
		}
		SetMove(move);
	}
	
	
	
	
    return isInput;
}

void Player::Update(float deltaTime)
{
	
	
	
	if (Grand.y < Pos.y)
	{
		Pos = VAdd(Pos, G);

		Pos.y = Pos.y < 0 ? 0 : Pos.y;
	 }

	if (AnimType == Kick)
	{
		if (NowAnimTime >= 30.0f && NowAnimTime <= AnimTotalTime)
		{
			VECTOR AttackPos = VGet(0, 100, -200);
			AttackPos = VTransformSR(AttackPos, MGetRotY(GetDir().y));
			SetAttackCollison(VAdd(Pos, AttackPos), 30.f);
		}
		else
		{
			AttackCollison = {};
		}
		SetAnimSpeed(30.0f);
	}
	else
	{
		AttackCollison = {};
		SetAnimSpeed(10.0f);

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
		SetAnimSpeed(20.0);
		InRolling = Rolling();
		if (!InRolling)
		{
			SetAnimType(Stop);
		}
	}
	else
	{
		SetAnimSpeed(10.0);
		MoveCollison(Move);
	    SetPos(VAdd(Pos, Move));

	}
	AnimUpdate(deltaTime);
	
	if (LiveTime - LastDamageTime >= 5.0f&&GetHp()<MaxHp && fabs(fmod(LiveTime - LastDamageTime, 0.1f)) < 0.01f)
	{
	
		SetHp(GetHp() +5);
	}
	DrawSphere3D(GetPos(), 20, 16, GetColor(200, 255, 255), GetColor(0, 0, 0), TRUE);

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
	
	if (!IsAnim)
	{
		float move = 300;
		Move = VNorm(Move);
		SetPos(VAdd(Pos, VScale(Move,move)));	
		SetCollison(VAdd(Pos, VGet(0, 100, 0)), 40.0f);

	
	}
	return IsAnim;
}



void Player::SpecialMove(float deltaTime)
{ 
	
	
}
