#include "Enemy.h"
const float CollisonSize = 600.0f;
Enemy::Enemy()
{
	SetCollison(VAdd(Pos, VGet(0, 500, 0)), CollisonSize);
}

void Enemy::SetTarget(Character &target)
{
	Target = &target;
}

VECTOR Enemy::SearchTarget()
{
	if (Target != NULL)
	{
		return Target->GetPos();
	}
	return VGet(0,0,0);
}

bool Enemy::TackleAttack(VECTOR targetPos)
{
	const int EndCount=4*60;
	if (!IsAnim && AnimType != Ran)
	{
		SetAnimType(Ran);
	}
	else if (!IsAnim || AnimType == Ran)
	{
		VECTOR move = VNorm(targetPos);
		VECTOR Front = VTransformSR(VGet(0, 0, -1), MGetRotY(GetDir().y));
		
		float rag = VDot(move, Front) / (VSize(move) * VSize(Front));
		rag = acosf(rag);
		float crossY = Front.x * move.z - Front.z * move.x;

		if (rag >= MaxTurn * DX_PI / 180.0f)
		{
			////‚¹‚¢‚°‚ñ‚æ‚è‚Å‚©‚¢‚Ì‚Å‚ ‚ê‚Î‚¹‚¢‚°‚ñ‚ß‚¢‚Á‚Ï‚¢
			if (crossY < 0)
			{
				move = VTransformSR(VGet(0, 0, -1), MGetRotY(GetDir().y + 1.0f * DX_PI / 180.0f));

			}
			else
			{
				move = VTransformSR(VGet(0, 0, -1), MGetRotY(GetDir().y - 1.0f * DX_PI / 180.0f));
			}

		}
		move = VScale(move, GetSpeed());
		Move = move;
		Pos = VAdd(Pos, move);
		AttackCollison.SetPos(Pos);
		

		if (!IsAnim)
		{
			SetAnimType(Ran);
		}
		float targetAngle = atan2f(move.x, -move.z); // ƒ‰ƒWƒAƒ“Šp
		SetDir(VGet(0, -targetAngle, 0));
	}
	if (LiveCount - StartLiveCount >= EndCount)
	{
		return false;
	}

	return true;
}

bool Enemy::ArmSwingDown(VECTOR targetPos)
{
	const int EndCount = 4 * 60;
	if (LiveCount - StartLiveCount >= EndCount)
	{
		return false;
	}

	return true;
}

bool Enemy::Tink()
{
	const int EndCount = 4 * 60;
	if (LiveCount - StartLiveCount >= EndCount)
	{
		return false;
	}

	return true;
}

Sphere_Collision Enemy::GetAttackCollison()
{
	return AttackCollison;
}

void Enemy::Update()
{
	enum AttackMotion {Tackle,DownArmSwing,Tink};

	VECTOR distance = VSub(SearchTarget(), Pos);
	if (!IsMotion&&!IsAnim)///“®‚«‚ÌØ‚è‘Ö‚¦
	{
		if (VSize(distance) >= 300)
		{
			MotionType = Tackle;
			AttackCollison = GetCollison();
			SetAnimType(Junp);
			SetSpeed(15);
		}
		else
		{
			MotionType = DownArmSwing;
	

		}
	StartLiveCount = LiveCount;
	IsMotion = true;
	}
	else
	{
		switch (MotionType)
		{
		case Tackle:
			IsMotion = TackleAttack(distance);
			break;
		case DownArmSwing:
			IsMotion = ArmSwingDown(distance);
			break;
		default:
			IsMotion = false;
			break;
		}
		
	}
	
	
	AnimUpdate();
	SetCollison(VAdd(Pos, VGet(0, 500, 0)), CollisonSize);

	LiveCount++;
	
}
