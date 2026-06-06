#include "StartScene.h"

bool StartScene::Update()
{
   
	float deltaTime = Fps->GetDeltaTime();
	
	if (Fade->GetAlpha() > 0 && !InModeChange)
	{
		MV1SetPosition(enemy->GetImg(), enemy->GetPos());
		float Move = 40 * deltaTime;
		MATRIX RotY = MGetRotY(ConversionRad(Move));
		VECTOR Axis = VAdd(enemy->GetPos(), VGet(0, 0, 200));///モデルの位置とPosのずれ直し
		enemy->SetPos(VGet(0, 0, 0));
		camera->RotationAxis(Axis, RotY);
		camera->Look(Axis);
		camera->Apply();
		enemy->AnimUpdate(deltaTime);
		Fade->SetAlpha(Fade->GetAlpha() - (255 / 2 * deltaTime));

	}
	else
	{
		MV1SetPosition(enemy->GetImg(), enemy->GetPos());

		////回転量を算出
		float Move = 40 * deltaTime;
		MATRIX RotY = MGetRotY(ConversionRad(Move));
		VECTOR Axis = VAdd(enemy->GetPos(), VGet(0, 0, 200));///モデルの位置とPosのずれ直し
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
		if (Fade->GetAlpha() >= 255)///画面が真っ黒になったら
		{
			camera->ResetOffset(DefaultCamera, player->GetPos());
			InModeChange = false;
			/*player->SetPos(StartPlayerPos);*/
			player->Initial();

			bool isJump = false;
			player->SetPos(VGet(0.0f, 0.0f, 0.0f));
			player->SetDir(VGet(0.0f, 0.0f, 0));
			player->SetAnimSpeed(PlayerAnimSpeed);
			player->SetAnimType(player->Stop);
			player->SetNowAnimTime(0);
			MV1SetAttachAnimTime(player->GetImg(), player->GetAnimType(), player->GetNowAnimTime());
			MV1SetPosition(player->GetImg(), player->GetPos());
			player->SetScale(1.0f);// 試しに10倍
			player->SetHp(playerMaxHp);



			///enemy初期化

			enemy->SetPos(VGet(0.0f, 2900.0f, -600.0f));
			MV1SetPosition(enemy->GetImg(), enemy->GetPos());
			enemy->SetDir(VGet(0, ConversionRad(180), 0));
			enemy->SetAnimSpeed(EnemyAnimSpeed);
			enemy->SetAnimType(enemy->Jump);
			enemy->SetTarget(*player);
			enemy->SetScale(5.0f);  // 試しに10倍
			enemy->SetHp(EnemyHP);
			enemy->SetMove(VGet(0, 0, 0));
			enemy->Initial();

			/*enemyHpBar->ResetOwner(enemy, VGet(-400, 900, 0));*/


			MV1SetAttachAnimTime(enemy->GetImg(), enemy->GetAnimType(), enemy->GetNowAnimTime());
			camera->EndZoom();
			camera->EndMove();
			camera->ResetOffset(DefaultCamera, player->GetPos());
			camera->CalculateAngle(player->GetPos());
			camera->CalculateTargetAngle(player->GetPos());
			InModeChange = false;
			return true;
		}

		ShowFrameName(player->GetImg());
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
   InModeChange = false;
}
