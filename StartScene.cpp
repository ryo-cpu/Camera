#include "StartScene.h"

bool StartScene::Update()
{
    bool InModeCheng=false;
	float deltaTime = Fps->GetDeltaTime();
	
	if (Fade->GetAlpha() > 0 && !InModeCheng)
	{

		Fade->SetAlpha(Fade->GetAlpha() - (255 / 2 * deltaTime));

	}
	else
	{
		MV1SetPosition(enemy->GetImg(), enemy->GetPos());

		////‰ñ“]—Ê‚ðŽZo
		float Move = 40 * deltaTime;
		MATRIX RotY = MGetRotY((Move));
		VECTOR Axis = VAdd(enemy->GetPos(), VGet(0, 0, 200));///ƒ‚ƒfƒ‹‚ÌˆÊ’u‚ÆPos‚Ì‚¸‚ê’¼‚µ
		enemy->SetPos(VGet(0, 0, 0));
		camera->RotationAxis(Axis, RotY);
		camera->Look(Axis);
		camera->Apply();
		enemy->AnimUpdate(deltaTime);
		if (!enemy->GetIsAnim())
		{
			enemy->SetNowAnimTime(0.0f);
		}
		if (player->GetInputState()->Buttons[XINPUT_BUTTON_START] != 0 && GetJoypadNum() != 0)
		{
			InModeCheng = true;


		}
		if (InModeCheng)
		{
			///‰æ–Ê‚ðˆÃ‚­
			Fade->SetAlpha(Fade->GetAlpha() + 255 / 2 * deltaTime);
		}
		else
		{
			///Modeƒ`ƒFƒ“ƒW‚ª‰Ÿ‚³‚ê‚é‚Ü‚Å‚Ì•\Œ»
		}
		if (Fade->GetAlpha() >= 255)///‰æ–Ê‚ª^‚Á•‚É‚È‚Á‚½‚ç
		{
			camera->ResetOffset(DefaultCamera, player->GetPos());
			InModeCheng = false;
			/*player->SetPos(StartPlayerPos);*/
			player->Initial();

			bool isJump = false;
			player->SetDir(VGet(0, 0, 0));
			player->SetAnimSpeed(PlayerAnimSpeed);
			player->SetAnimType(player->Stop);
			player->SetNowAnimTime(0);
			MV1SetAttachAnimTime(player->GetImg(), player->GetAnimType(), player->GetNowAnimTime());
			MV1SetPosition(player->GetImg(), player->GetPos());
			player->SetScale(1.0f);// ŽŽ‚µ‚É10”{
			player->SetHp(playerMaxHp);



			///enemy‰Šú‰»

			enemy->SetPos(VGet(0.0f, 0.0f, -600.0f));
			MV1SetPosition(enemy->GetImg(), enemy->GetPos());
			enemy->SetDir(VGet(0, -1, 0));
			enemy->SetAnimSpeed(EnemyAnimSpeed);
			enemy->SetAnimType(enemy->Dance);
			enemy->SetNowAnimTime(0);
			enemy->SetTarget(*player);
			enemy->SetScale(5.0f);  // ŽŽ‚µ‚É10”{
			enemy->SetHp(EnemyHP);
			enemy->SetMove(VGet(0, 0, 0));
			enemy->Initial();

			/*enemyHpBar->ResetOwner(enemy, VGet(-400, 900, 0));*/


			MV1SetAttachAnimTime(enemy->GetImg(), enemy->GetAnimType(), enemy->GetNowAnimTime());
			camera->ResetOffset(DefaultCamera, player->GetPos());
			camera->CalculateAngle(player->GetPos());
			camera->CalculateTargetAngle(player->GetPos());

			return true;
		}


		SetFontSize(256);
		DrawString(100, 250, "KILL ME", GetColor(244, 229, 17));
		SetFontSize(64);
		DrawString(600, 550, "PUSH START", GetColor(244, 229, 17));

	}
	SetUseBackCulling(FALSE);
	shadow->Draw();
	shadow->StartUse();
	MV1DrawModel(BackModel);
	MV1DrawModel(MapModel);
	EffectM::Update(deltaTime);
	EffectM::Draw();
	enemy->Draw();
	shadow->EndUse();
    return false;
}

StartScene::StartScene(Camera* camera, Player* player, Enemy* enemy, int& BackModel, int& MapModel, fps* Fps, Box* Fade, Shadow* shadow) :
	Scene(camera, player, enemy, BackModel, MapModel,  Fps, Fade,  shadow)
{
}
