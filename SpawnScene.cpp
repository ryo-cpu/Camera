#include "SpawnScene.h"

bool SpawnScene::Update()
{
	speed.y += 1.0f;
	enemy->SetPos(VAdd(enemy->GetPos(), ));
	camera->Look(enemy->GetPos());

	MV1SetPosition(enemy->GetImg(), enemy->GetPos());

	enemy->Draw();

	if (enemy->GetPos().y < 0)
	{
		enemy->SetPos(VGet(enemy->GetPos().x, 0, enemy->GetPos().z));
		return false;
	}
	return true;
}

SpawnScene::SpawnScene(Camera* camera, Player* player, Enemy* enemy, int& BackModel, int& MapModel, fps* Fps, Box* Fade, Shadow* shadow):Scene(camera, player, enemy, BackModel, MapModel, Fps, Fade, shadow)
{
	speed = VGet(0, 0, 0);
}
