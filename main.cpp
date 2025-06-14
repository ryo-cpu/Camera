﻿// 2023 Takeru Yui All Rights Reserved.
#include<vector>
#include "DxLib.h"
// 2023 Takeru Yui All Rights Reserved.
#include <chrono>  // chronoを使うため]
#include<cmath>
#include "Arithmetic.h"
#include"Camera.h"
#include"Player.h"
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

	float  AnimTotalTime;
	float  AnimNowTime;
	int    AnimAttachIndex;
	int M2;
	int MouseX, MouseY;
	GetMousePoint(&MouseX, &MouseY);
	float BaseY = NULL;
	VECTOR JunpPower = VGet(0, 30, 0);
	VECTOR EnemyPos = VGet(0.0f, 0.0f, -600.0f);
	Character *player=new Player();
	player->SetPos(StartPlayerPos);
	VECTOR G = VGet(0, -1, 0);
	bool isJunp = false;
	player->SetImg(MV1LoadModel("data/walking.mv1"));
	player->SetDir(VGet(0, 0, 0));
	AnimAttachIndex = MV1AttachAnim(player->GetImg(), 0);
	AnimTotalTime = MV1GetAttachAnimTotalTime(player->GetImg(), AnimAttachIndex);
	AnimNowTime = 0.0f;
	MV1SetAttachAnimTime(player->GetImg(), AnimAttachIndex, AnimNowTime);
	
	M2 = MV1LoadModel("data/Spider.mv1");

	///////
	SetCameraPositionAndTarget_UpVecY(VGet(0, 0, 0), player->GetPos());
	
	MV1SetPosition(player->GetImg(), player->GetPos());
	MV1SetPosition(M2, VGet(300.0f, 0.0f,300.0f));


	MV1SetScale(player->GetImg(), VGet(1.0f, 1.0f, 1.0f));  // 試しに10倍
	MV1SetScale(M2, VGet(5.0f, 5.0f, 5.0f));  // 試しに10倍
	// アニメーション再生時間を進める
	static int lastTime = 0;
	static float animSpeed = 0.1f;  // アニメーションの進行速度

	float StratTime=0;
	const float ChangAnimTime = 3*60;
	float NowTime = 0;
	bool isWalk = true;
	Camera *camera=new Camera(100.0f,10000.0f, VAdd(PlayerPos, VGet(0.0f, 200.0f, 300.0f)),PlayerPos);
	camera->GetAngle(PlayerPos);
	VECTOR dir=VGet(0,0,0);
	VECTOR BesePoint = VGet(0, 0, 0);
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
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
		VECTOR EnemyMove;
		EnemyMove.x = player->GetPos().x - EnemyPos.x;
		EnemyMove.z = player->GetPos().z - EnemyPos.z;
		EnemyMove = VNorm(EnemyMove);
	
		bool isInput = false;
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{

			VECTOR R = VGet(-1, 0, 0);
			R = VTransformSR(R,MGetRotY(player->GetDir().y));
			dir=VAdd(R,dir);
			isInput = true;

		}// 画面をクリア
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			VECTOR L = VGet(1, 0, 0);
			L = VTransformSR(L, MGetRotY(player->GetDir().y));
			dir = VAdd(L, dir);

			isInput = true;
			
		}
		if (CheckHitKey(KEY_INPUT_UP))
		{
			VECTOR F = VGet(0, 0, -1);
			F = VTransformSR(F, MGetRotY(player->GetDir().y));
			dir = VAdd(F, dir);

			isInput = true;

		}
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			VECTOR D = VGet(0, 0, 1);
			D= VTransformSR(D, MGetRotY(player->GetDir().y));
			dir = VAdd(D, dir);

			isInput = true;
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
		
			isInput = true;
	

		}
		if (isJunp)
		{
			dir = VAdd(dir, JunpPower);
			JunpPower = VAdd(JunpPower, G);
			
		}
		
		
		if (player->GetPos().y <= BaseY)
		{
			isJunp = false;
			player->SetPos(VGet(player->GetPos().x, BaseY,player->GetPos().z));
			JunpPower = VGet(0, 30, 0);

		}

		if (NowTime >= ChangAnimTime)
		{
			if (isWalk)
			{
				isWalk = false;
			}
			else
			{
				isWalk = true;
			}
			
			NowTime = 0;

		}
		VECTOR Distans = VSub(EnemyPos, player->GetPos());
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
			EnemyPos =VAdd(EnemyPos,VScale(EnemyMove,-200.0f));
			PlaySoundFile("data/Hit.mp3", DX_PLAYTYPE_BACK);
			////あった時の処理
		}
		DrawSphere3D(player->GetPos(), 30.0f, 16, GetColor(200, 255, 255), GetColor(0, 0, 0), TRUE);
		DrawTriangle3D(VGet(-300, 0, -300), VGet(300, 0, -300), VGet(-300, 0, 300), GetColor(200, 255, 255), TRUE);
        DrawTriangle3D(VGet(300,0,300),VGet(300,0,-300), VGet(-300, 0, 300), GetColor(0, 0, 255), TRUE);

		
		// 前回のフレームから経過した時間を取得
		int nowTime = GetNowHiPerformanceCount();
		float deltaTime = (nowTime - lastTime) / 10000000.0f;  // 時間を秒に変換

		AnimNowTime += deltaTime * animSpeed;  // アニメーション時間を進める

		if (AnimAttachIndex >= 0&&isWalk) {  // アニメーションが設定されていれば
			AnimNowTime += deltaTime * animSpeed;
			// アニメーションが総時間を超えたらループ
			if (AnimNowTime >= AnimTotalTime) {
				AnimNowTime -= AnimTotalTime;


			}
		}
		
		MV1SetAttachAnimTime(player->GetImg(), AnimAttachIndex, AnimNowTime);  // アニメーション時間を設定
		if (!isInput)
		{
			dir =VScale(dir,0.5f);
			camera->StartMove(VScale(VSub(VAdd(player->GetPos(), camera->GetOffset()), camera->GetPos()), 0.1f));
			if (VSize(dir) <= 0)
			{
				BesePoint = player->GetPos();
			
			}
		}
		if (VSize(VSub(player->GetPos(), BesePoint)) >= 100.0f && isInput)
		{
			camera->StartMove(VScale(dir, 1.0f));
		}
	
		
		player->SetMove(dir);
		player->Update();
		camera->Update(player->GetPos());

		MV1SetPosition(player->GetImg(), player->GetPos());
		MV1SetPosition(M2, EnemyPos);

		MV1DrawModel(player->GetImg());
		MV1DrawModel(M2);              // モデルの描画
		// モデルの描画
			   // モデルの描画

		ScreenFlip();                           // 裏画面の内容を表画面に反映
	}
	MV1DeleteModel(player->GetImg());
	delete(player);
	delete(camera);



	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}

