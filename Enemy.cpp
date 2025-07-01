#include "Enemy.h"
template <typename T>
T Clamp(const T& value, const T& minVal, const T& maxVal) {
	return (value < minVal) ? minVal : (value > maxVal) ? maxVal : value;
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

void Enemy::Update()
{
	VECTOR distance=VSub(SearchTarget(),Pos);
	if (VSize(distance)>=200)
	{
		VECTOR move = VNorm(distance);
		VECTOR Front =VTransformSR(VGet(0,0,-1), MGetRotY(GetDir().y));
		
		float rag = VDot(move, Front) / (VSize(move) * VSize(Front));
		rag = acosf(rag);
		float crossY = Front.x * move.z - Front.z * move.x;
		if (crossY < 0) rag = -rag;
		if (rag >= 1.0f * DX_PI / 180.0f|| rag <= -1.0f * DX_PI / 180.0f)
		{
			////‚¹‚¢‚°‚ñ‚æ‚è‚Å‚©‚¢‚Ì‚Å‚ ‚ê‚Î‚¹‚¢‚°‚ñ‚ß‚¢‚Á‚Ï‚¢
			if (rag > 0)
			{
				move = VTransformSR(VGet(0, 0, -1), MGetRotY(GetDir().y + 10.0f * DX_PI / 180.0f));

			}
			else
			{
				move = VTransformSR(VGet(0, 0, -1), MGetRotY(GetDir().y+ -10.0f * DX_PI / 180.0f));
			}
			
		}
		Pos = VAdd(Pos, move);
		if (!IsAnim)
		{
			SetAnimType(Ran);
		}
		float targetAngle = atan2f(move.x, -move.z); // ƒ‰ƒWƒAƒ“Šp
		SetDir(VGet(0, -targetAngle, 0));
		
		
	}
	AnimUpdate();
	SetCollison(VAdd(Pos, VGet(0, 500, 0)), 100.0f);
	
}
