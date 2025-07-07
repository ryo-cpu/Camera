// 2023 Takeru Yui All Rights Reserved.
#include<vector>
#include "DxLib.h"
// 2023 Takeru Yui All Rights Reserved.

#include "fps.h"
#include "Arithmetic.h"
#include"Camera.h"
#include"Player.h"
#include"Enemy.h"
using namespace std::chrono;
const VECTOR StartPlayerPos = VGet(0, 0, 0);
const Camera InitialCamera = Camera(100.0f, 10000.0f, VAdd(StartPlayerPos, VGet(-150.0f, 250.0f, 200.0f)), StartPlayerPos);

/// <summary>
/// メイン関数
/// </summary>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{


	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;	// エラーが起きたら直ちに終了
	}

	// 画面モードのセット
	ChangeWindowMode(TRUE);
	SetGraphMode(1600, 900, 16);
	VECTOR PlayerPos = VGet(0,0,0);


	SetDrawScreen(DX_SCREEN_BACK);	// 裏画面を描画対象にする
	SetUseZBufferFlag(TRUE);		// Ｚバッファを使用する
	SetWriteZBufferFlag(TRUE);		// Ｚバッファへの書き込みを行う
	SetUseBackCulling(TRUE);		// バックカリングを行う

	int M2;
	int MouseX, MouseY;
	GetMousePoint(&MouseX, &MouseY);
	float BaseY = NULL;
	VECTOR JumpPower = VGet(0, 30, 0);
	Player *player=new Player();
	Enemy* enemy = new Enemy();
	player->SetPos(StartPlayerPos);
	enemy->SetPos(VGet(0.0f, 0.0f, -600.0f));
	VECTOR G = VGet(0, -1, 0);
	bool isJunp = false;
	player->SetImg(MV1LoadModel("data/player.mv1"));
	player->SetDir(VGet(0, 0, 0));
	player->SetAnimSpeed(0.000001);
	player->SetAnimType(player->Stop);
	player->SetNowAnimTime(0);
	MV1SetAttachAnimTime(player->GetImg(),player->GetAnimType(),player->GetNowAnimTime());
	
	enemy->SetImg(MV1LoadModel("data/Monstor.mv1"));
	enemy->SetDir(VGet(0, ConversionRad(180), 0));
	enemy->SetAnimSpeed(0.000001);
	enemy->SetAnimType(0);
	enemy->SetNowAnimTime(0);
	enemy->SetTarget(*player);
	
	MV1SetAttachAnimTime(enemy->GetImg(), enemy->GetAnimType(), enemy->GetNowAnimTime());

	///////
	SetCameraPositionAndTarget_UpVecY(VGet(0, 0, 0), player->GetPos());
	
	MV1SetPosition(player->GetImg(), player->GetPos());
	MV1SetPosition(enemy->GetImg(),enemy->GetPos());


	MV1SetScale(player->GetImg(), VGet(1.0f, 1.0f, 1.0f));  // 試しに10倍
	MV1SetScale(enemy->GetImg(), VGet(5.0f, 5.0f, 5.0f));  // 試しに10倍
	fps fps;
	fps.Initialization(1.0 / 60.0);
	Sphere_Collision *Collision_Measurement=new Sphere_Collision;
	
	float StratTime=0;
	float NowTime = 0;
	Camera *camera=new Camera(100.0f,10000.0f, VAdd(PlayerPos, VGet(0.0f, 200.0f, 300.0f)),PlayerPos);
	camera->GetAngle(PlayerPos);

	VECTOR BesePoint = VGet(0, 0, 0);
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		fps.Start();
		++NowTime;
		ClearDrawScreen();
		////マウスの回転処理
		int NowMouseX, NowMouseY;
		GetMousePoint(&NowMouseX, &NowMouseY);
		///移動量を出す
		int MoveMouseX = MouseX - NowMouseX;
		int MoveMouseY = MouseY - NowMouseY;
		if (MoveMouseX != 0 || MoveMouseY != 0)
		{
			///マウスの位置を更新
			MouseX = NowMouseX;
			MouseY = NowMouseY;
			////回転量を算出
			MATRIX RotY = MGetRotY(ConversionRad(MoveMouseX*0.1));
			camera->RotaionAxis(player->GetPos(),RotY);
			player->Turn(VGet(0, ConversionRad(MoveMouseX * 0.1),0));
			camera->Look(player->GetPos());
		}
		
		
		
		if (CheckHitKey(KEY_INPUT_SPACE) && (player->GetPos().y >= BaseY || BaseY == NULL))
		{
			if (BaseY == NULL)
			{
				BaseY = player->GetPos().y;
			}
			isJunp = true;
			


		}
		if (CheckHitKey(KEY_INPUT_W))
		{
			
		    
			camera->GetAngle(PlayerPos);
			camera->ResetOffset(VGet(100, 100, 200), PlayerPos);
			camera->GetAngle(PlayerPos);

			camera->Action(VGet(100,100,200), PlayerPos, 0.0f, 9.50000f, -0.1000000);
		
			

		}
		if (isJunp)
		{
			player->SetMove(VAdd(player->GetMove(), JumpPower));
			JumpPower = VAdd(JumpPower, G);
			
		}
		bool isInput = false;
		if (player->GetIsHit())
		{
			player->SetMove(VAdd(player->GetMove(), G));

		}
		else
		{
			isInput = player->Input();

		}
		if (player->GetPos().y <= BaseY)
		{
			isJunp = false;
			player->SetPos(VGet(player->GetPos().x, BaseY,player->GetPos().z));
			JumpPower = VGet(0, 30, 0);
			player->SetIsHit(false);

		}
		VECTOR Distans = VSub(enemy->GetPos(), player->GetPos());
		if (CheckHitKey(KEY_INPUT_A))
		{
			VECTOR CPos = VCross(VNorm(Distans), VGet(0, -1, 0));
			float rag = 60.f;
			CPos = VScale(CPos,VSize(Distans)*atan(ConversionRad(rag)));
			camera->ResetOffset(CPos,player->GetPos());
			camera->Look(VAdd(player->GetPos(), VScale(Distans, 0.75)));
		}
		float Distance = VSize(Distans);
		if (Distance <= 30.0f)
		{
		
			PlaySoundFile("data/Hit.mp3", DX_PLAYTYPE_BACK);
			////あった時の処理
		}
		
		DrawTriangle3D(VGet(-300, 0, -300), VGet(300, 0, -300), VGet(-300, 0, 300), GetColor(200, 255, 255), TRUE);
        DrawTriangle3D(VGet(300,0,300),VGet(300,0,-300), VGet(-300, 0, 300), GetColor(0, 0, 255), TRUE);

		
		if (!isInput)
		{
		/*	player->SetMove(VScale(player->GetMove(), 0.5f));*/
			camera->StartMove(VScale(VSub(VAdd(player->GetPos(), camera->GetOffset()), camera->GetPos()), 0.1f));
			if (VSize(player->GetMove()) <= 0)
			{
				BesePoint = player->GetPos();
			
			}
		}
		if (VSize(VSub(player->GetPos(), BesePoint)) >= 100.0f && isInput)
		{
			camera->StartMove(VScale(player->GetMove(), 1.0f));
		}
	
		Sphere_Collision PlayerCollison = player->GetCollison();
		PlayerCollison.SetPos(VAdd(PlayerCollison.GetPos(), player->GetMove()));
	
		
		player->Update();
		enemy->Update();
		camera->Update(player->GetPos());
		////シンプル衝突
		if (Collision_Measurement->Collison(PlayerCollison, enemy->GetCollison()))
		{
			VECTOR Distance = VSub(player->GetPos(), enemy->GetPos());

			Sphere_Collision PlayerCollison = player->GetCollison();
			Sphere_Collision enemyCollison = enemy->GetCollison();

			VECTOR TakeDistance = VScale(VNorm(Distance), (enemyCollison.GetSphereSize() + PlayerCollison.GetSphereSize()));

			TakeDistance = VSub(TakeDistance, Distance);
			player->SetMove(VAdd(player->GetMove(), TakeDistance));
			player->SetPos(VAdd(player->GetPos(), player->GetMove()));
		}
		
		
		///enemy攻撃

		if (Collision_Measurement->Collison(player->GetCollison(), enemy->GetAttackCollison()))
		{
			

			player->SetMove(VAdd(VScale( enemy->GetMove(),2),VGet(0,10,0)));
			player->SetPos(VAdd(player->GetPos(), player->GetMove()));
			player->SetIsHit(true);
		}

	
		////player攻撃
		Collision_Measurement->Collison(player->GetAttackCollison(), enemy->GetCollison());
	


		MV1SetPosition(player->GetImg(), player->GetPos());
		MV1SetPosition(enemy->GetImg(), enemy->GetPos());

		MV1DrawModel(player->GetImg());
		MV1DrawModel(enemy->GetImg());              // モデルの描画
		// モデルの描画
			   // モデルの描画

		ScreenFlip();                           // 裏画面の内容を表画面に反映
		fps.End();
	}
	MV1DeleteModel(player->GetImg());
	delete(player);
	delete(enemy);
	delete(camera);
	delete(&fps);
	delete(Collision_Measurement);



	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}

