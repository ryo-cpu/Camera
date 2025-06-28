#include "Enemy.h"

void Enemy::Update()
{
	AnimUpdate();
	SetCollison(VAdd(Pos, VGet(0, 500, 0)), 100.0f);
	
}
