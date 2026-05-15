#include "Enemy.h"
const float CollisionSize = 600.0f;
Enemy::Enemy()
{
	SetCollision(VAdd(Pos, VGet(0, 500, 0)), CollisionSize);
	MaxHp = 300;
	Hp = MaxHp;
	Attack = 10;
   IsInvincible = false;

}

Enemy::Enemy(int img) : Character(img)
{
	SetCollision(VAdd(Pos, VGet(0, 500, 0)), CollisionSize);
	MaxHp = 300;
	Hp = MaxHp;
	Attack = 10;
	IsInvincible = false;

}

Enemy::~Enemy()
{
	/*delete Target;*/
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




void Enemy::SelectMove()
{
	VECTOR distance = VSub(SearchTarget(), Pos);
	if (!IsMotion)///動きの切り替え
	{
		Move = VGet(0, 0, 0);
		if (MotionType == Tackle || MotionType == DownArmSwing)
		{
			MotionType = tink;
			SetStartLiveTime(LiveTime);
			SetAnimType(Dance);
		}
		else 
		{
			///この距離以上は必ずタックル
			const int  MaxArmAttackDistnce=1000;
			int TackleProbability = (static_cast<int>( VSize(distance)) / MaxArmAttackDistnce)*100;
			if (TackleProbability < 0)
			{
				TackleProbability = 0;
			}
			else if (TackleProbability > 100)
			{
				TackleProbability = 100;
			}

			if (GetRand(100)<= TackleProbability)
			{
				MotionType = Tackle;
				AttackCollision = GetCollision();
				SetStartLiveTime(LiveTime);
				SetAnimType(Jump);
				SetSpeed(20);
			}
			else
			{
				VECTOR EnemyDir = VNorm(VSub(GetPos(), Target->GetPos()));
				float Angle = atan2f(EnemyDir.x, EnemyDir.z);
				SetDir(VGet(0, Angle, 0));
				MotionType = DownArmSwing;
				SetAnimType(ArmSwing);

			}
			
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

	
}

bool Enemy::TackleAttack(VECTOR targetPos)
{
	const float EndTime=10;
	Move = VGet(0, 0, 0);
	IsInvincible = true;

	if (!IsAnim && AnimType != Run)
	{
		SetAnimType(Run);
	}
	else if (!IsAnim || AnimType == Run)
	{
		IsInvincible = false;
		VECTOR move = VNorm(targetPos);
		VECTOR Front =VTransformSR(VGet(0, 0, -1), MGetRotY(GetDir().y));
		
		float rag = VDot(move, Front) / (VSize(move) * VSize(Front));
		rag = acosf(rag);
		float crossY = Front.x * move.z - Front.z * move.x;
	

		if (rag >= MaxTurn * DX_PI / 180.0f)
		{
			////せいげんよりでかいのであればせいげんめいっぱい
			if (crossY < 0)
			{
				move =VTransformSR(VGet(0, 0, -1), MGetRotY(GetDir().y + 1.0f * DX_PI / 180.0f));

			}
			else
			{
				move =VTransformSR(VGet(0, 0, -1), MGetRotY(GetDir().y - 1.0f * DX_PI / 180.0f));
			}

		}
		move = VScale(move, GetSpeed());
		move.y = 0;
		Move = move;
		AttackCollision.SetPos(VAdd(Pos,move));

		if (!IsAnim)
		{
			SetAnimType(Run);
		}
		float targetAngle = atan2f(move.x, -move.z); // ラジアン角
		SetDir(VGet(0, -targetAngle, 0));
	}
	if (LiveTime - StartLiveTime >= EndTime)
	{
		AttackCollision = {};
		return false;
	}

	return true;
}

bool Enemy::ArmSwingDown(VECTOR targetPos)
{
	Move = VGet(0, 0, 0);
	const float EndTime = 5;
	if (NowAnimTime >= 30.0f)
	{
		IsInvincible = false;

		VECTOR AttackPos = VGet(0, 50, -400);
		AttackPos =VTransformSR(AttackPos, MGetRotY(GetDir().y));
		SetAttackCollision(VAdd(Pos, AttackPos), 300.f);
	/*	DrawSphere3D(GetPos(), 200, 16, GetColor(200, 255, 255), GetColor(0, 0, 0), TRUE);*/
		SetAnimSpeed(20);

	}
	else
	{
		IsInvincible = true;
		SetAnimSpeed(40);
	}
	
	if (LiveTime - StartLiveTime >= EndTime||NowAnimTime>=AnimTotalTime)
	{
		AttackCollision = {};
		return false;
	}

	return true;
}

bool Enemy::Tink()
{
	Move = VGet(0, 0, 0);
	const float EndTime = 3;
	IsInvincible = false;
	SetAnimSpeed(20);
	if (LiveTime - StartLiveTime >= EndTime)
	{
		return false;
	}
	
	return true;
}

bool Enemy::Hit_Stop()
{
	AttackCollision = {};
	IsInvincible = true;
	Move = KnockBack;
	SetAnimSpeed(20);
	if (!IsAnim)
	{
		const char* HipName = "mixamorig:Hips";

		int HipIndex = MV1SearchFrame(Img, HipName);
		if (HipIndex >= 0)
		{
			VECTOR CPos = MV1GetFramePosition(Img, HipIndex);
			SetCollision(CPos, CollisionSize);
			CPos.y = 0;
			Pos = CPos;
		}
		else
		{

			SetCollision(VAdd(Pos, VGet(0, 500, 0)), CollisionSize);

		}
		SetKnockBack(VGet(0, 0, 0));
	IsInvincible = false;

	 return false;
	}
	return true;
}

Sphere_Collision Enemy::GetAttackCollision()
{
	return AttackCollision;
}

void Enemy::SetMoveType(int movetype)
{
	MotionType = movetype;
}

void Enemy::SetKnockBack(VECTOR knockback)
{
	KnockBack = knockback;
}

int Enemy::GetMoveType()
{
	return MotionType;
}

bool Enemy::GetIsInvincible()
{
	return IsInvincible;
}

void Enemy::SetIsInvincible(bool isinvincible)
{

	IsInvincible = isinvincible;
}


void Enemy::Update(float deltaTime)
{
    Pos = VAdd(Pos,Move);
	
	//AnimUpdate(deltaTime);
	
	const char* HipName = "mixamorig:Hips";

	int HipIndex = MV1SearchFrame(Img, HipName);
	if (HipIndex >= 0)
	{
		VECTOR CPos = MV1GetFramePosition(Img, HipIndex);
		SetCollision(CPos, CollisionSize);
		
	}
	else
	{
	 
		SetCollision(VAdd(Pos, VGet(0, 500, 0)), CollisionSize);

	}
	//DrawSphere3D(Collision.GetPos(), Collision.GetSphereSize(), 16, GetColor(200, 255, 255), GetColor(0, 0, 0), TRUE);

	AddLiveTime(deltaTime);
	
}

void Enemy::Initial()
{
	SetCollision(VAdd(Pos, VGet(0, 500, 0)), CollisionSize);
	MaxHp = 300;
	Hp = MaxHp;
	Attack = 10;
    IsMotion = false;
}
