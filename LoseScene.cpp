#include "LoseScene.h"

bool LoseScene::Update()
{
	MV1DrawModel(BackModel);
	float deltaTime = Fps->GetDeltaTime();

	if (player->GetInputState()->Buttons[XINPUT_BUTTON_START] != 0)
	{
		InModeChange = true;

	}
	if (InModeChange)
	{
		///画面を暗く
		///画面を暗く
		Fade->SetAlpha(Fade->GetAlpha() + 255 / 2 * deltaTime);
	}
	else
	{
		///Modeチェンジが押されるまでの表現
	}
	if (Fade->GetAlpha() == 255&&InModeChange)///画面が真っ黒になったら
	{
		enemy->SetPos(VGet(0.0f, 0.0f, 0.0f));
		MV1SetPosition(enemy->GetImg(), enemy->GetPos());
		camera->ResetOffset(StartCamera, enemy->GetPos());
		InModeChange = false;
		return true;

	}
	if (!player->GetIsAnim())
	{
		SetFontSize(128);
		DrawString(500, 350, "YOU LOSE", GetColor(244, 229, 17));
		SetFontSize(64);
		DrawString(600, 550, "PUSH START", GetColor(244, 229, 17));
	}
	camera->Apply();

	player->AddLiveTime(deltaTime);
	player->AnimUpdate(deltaTime);
	shadow->Draw();
	shadow->StartUse();
	MV1DrawModel(MapModel);
	player->Draw();
	shadow->EndUse();
	ScreenEffct->Draw();
    return false;
}

LoseScene::LoseScene(Camera* camera, Player* player, Enemy* enemy, int& BackModel, int& MapModel, fps* Fps, Box* Fade, Shadow* shadow)
    : Scene(camera, player, enemy, BackModel, MapModel, Fps, Fade, shadow)
{
    InModeChange = false;
	ScreenEffct=new Box(1600,900,100);
	ScreenEffct->SetColor(200, 0, 0);
}

LoseScene::~LoseScene()
{
	delete ScreenEffct;
}
