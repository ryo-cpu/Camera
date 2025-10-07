#include "Enemy.h"
const float CollisonSize = 600.0f;
Enemy::Enemy()
{
	SetCollison(VAdd(Pos, VGet(0, 500, 0)), CollisonSize);
	MaxHp = 3000;
	Hp = MaxHp;
	Attack = 10;

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
	const float EndTime=5;
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
	if (LiveTime - StartLiveTime >= EndTime)
	{
		AttackCollison = {};
		return false;
	}

	return true;
}

bool Enemy::ArmSwingDown(VECTOR targetPos)
{
	const float EndTime = 5;
	if (LiveTime - StartLiveTime >= EndTime)
	{
		return false;
	}

	return true;
}

bool Enemy::Tink()
{
	const float EndTime = 3;
	if (LiveTime - StartLiveTime >= EndTime)
	{
		return false;
	}
	
	return true;
}

bool Enemy::Hit_Stop()
{
	if (!IsAnim)
	{
	 return false;
	}
	Pos=VAdd(Pos, Move);

	return true;
}

Sphere_Collision Enemy::GetAttackCollison()
{
	return AttackCollison;
}

void Enemy::SetMoveType(int movetype)
{
	MotionType = movetype;
}

int Enemy::GetMoveType()
{
	return MotionType;
}


void Enemy::Update(float deltaTime)
{
	

	VECTOR distance = VSub(SearchTarget(), Pos);
	if (!IsMotion&&!IsAnim)///“®‚«‚ÌØ‚è‘Ö‚¦
	{
		if (MotionType == Tackle || MotionType == DownArmSwing)
		{
			MotionType = tink;
			SetAnimType(Dance);
		}
		else if (VSize(distance) >= 1000)
		{
			MotionType = Tackle;
			AttackCollison = GetCollison();
			SetAnimType(Junp);
			SetSpeed(10);
		}
		else
		{
			MotionType = DownArmSwing;
			SetAnimType(ArmSwing);
	
		}
	StartLiveTime = LiveTime;
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
		case tink:
			IsMotion = Tink();
			break;
		case hit_stop:
			IsMotion = Hit_Stop();
			break;
		default:
			IsMotion = false;
			break;
		}
		
	}
	
	
	AnimUpdate(deltaTime);
	SetCollison(VAdd(Pos, VGet(0, 500, 0)), CollisonSize);
	//DrawSphere3D(Collison.GetPos(), Collison.GetSphereSize(), 16, GetColor(200, 255, 255), GetColor(0, 0, 0), TRUE);

	AddLiveTime(deltaTime);
	
}
