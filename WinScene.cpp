#include "WinScene.h"

bool WinScene::Update()
{
	float deltaTime = Fps->GetDeltaTime();
	MV1DrawModel(BackModel);
	{

		if (player->GetInputState()->Buttons[XINPUT_BUTTON_START] != 0)
		{
			InModeChange = true;
			
		}
		if (InModeChange)
		{
			///画面を暗く
			Fade->SetAlpha(Fade->GetAlpha() + 255 / 2 * deltaTime);
		}
		else
		{
			///Modeチェンジが押されるまでの表現
		}

		float Time = enemy->GetLiveTime() - enemy->GetStartLiveTime();
		if (Time <= 2)
		{

		}
		else if (Time <= 4)
		{
			camera->ResetOffset(DefaultCamera, player->GetPos());
		}
		else
		{

			VECTOR Offset = WinCameraFast;
			camera->ResetOffset(Offset, enemy->GetPos());
			camera->Look(enemy->GetPos());
			if (!enemy->GetIsAnim())
			{
				SetFontSize(128);
				DrawString(600, 350, "YOU WIN", GetColor(244, 229, 17));
				SetFontSize(64);
				DrawString(600, 550, "PUSH START", GetColor(244, 229, 17));

			}


		}
	}
	camera->Apply();

	enemy->AddLiveTime(deltaTime);
	enemy->AnimUpdate(deltaTime);
	shadow->Draw();
	shadow->StartUse();
	MV1DrawModel(MapModel);
	player->Draw();
	enemy->Draw();
	shadow->EndUse();

	if (Fade->GetAlpha() == 255&&InModeChange)///画面が真っ黒になったら
	{
		enemy->SetPos(VGet(0.0f, 0.0f, 0.0f));
		camera->ResetOffset(StartCamera, enemy->GetPos());
		enemy->SetPos(VGet(0.0f, 0.0f, 0.0f));
		camera->ResetOffset(StartCamera, enemy->GetPos());
		enemy->SetAnimType(enemy->Dance);
		InModeChange = false;
		return true;
	}
	
    return false;
}

WinScene::WinScene(Camera* camera, Player* player, Enemy* enemy, int& BackModel, int& MapModel, fps* Fps, Box* Fade, Shadow* shadow) :
	Scene(camera, player, enemy, BackModel, MapModel, Fps, Fade, shadow)
{
	InModeChange = false;
}
