#include "SpawnScene.h"

bool SpawnScene::Update()
{
	float deltaTime = Fps->GetDeltaTime();
	if (Fade->GetAlpha() > 0)
	{
		MV1SetPosition(enemy->GetImg(), enemy->GetPos());
		enemy->AnimUpdate(deltaTime);
		Fade->SetAlpha(Fade->GetAlpha() - (255 / 2 * deltaTime));

	}
	else
	{
		camera->Look(enemy->GetPos());

		if (enemy->GetPos().y <= 0.0f)
		{
		  
		  enemy->SetPos(VGet(enemy->GetPos().x, 0, enemy->GetPos().z));
		  waitTime += deltaTime;
		}
		else
		{
			speed.y -= 1.0f;
			enemy->SetPos(VAdd(enemy->GetPos(), speed));
		}
		MV1SetPosition(enemy->GetImg(), enemy->GetPos());

	}
	if (waitTime >= 1.0f)
	{
		speed = VGet(0, 0, 0);
		enemy->SetAnimType(enemy->Dance);
		waitTime = 0;
		return true;

	}
	enemy->AnimUpdate(deltaTime);
	shadow->Draw();
	shadow->StartUse();
	MV1DrawModel(BackModel);
	MV1DrawModel(MapModel);
	EffectM::Update(deltaTime);
	EffectM::Draw();
	enemy->Draw();
	player->Draw();
	shadow->EndUse();
	camera->Update(enemy->GetPos());
	return false;
}

SpawnScene::SpawnScene(Camera* camera, Player* player, Enemy* enemy, int& BackModel, int& MapModel, fps* Fps, Box* Fade, Shadow* shadow):Scene(camera, player, enemy, BackModel, MapModel, Fps, Fade, shadow)
{
	speed = VGet(0, 0, 0);
	waitTime = 0;
}
