
#include<vector>
#include "DxLib.h"
#include"Arithmetic.h"


#include "fps.h"
#include"Player.h"
#include"Enemy.h"
#include"Bsr.h"
#include "SpecialMove.h"
using namespace std::chrono;
const VECTOR StartPlayerPos = VGet(0, 0, 0);


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
	int MouseX, MouseY;
	GetMousePoint(&MouseX, &MouseY);
	float BaseY = NULL;
	VECTOR JumpPower = VGet(0, 30, 0);
	Player *player=new Player();
	Enemy* enemy = new Enemy();
	int  BackModel = MV1LoadModel("data/Dome_Y902.mv1");
	MV1SetPosition(BackModel, VGet(0, 0, 0));
	MV1SetScale(BackModel, VGet(5, 5, 5));
	player->SetPos(StartPlayerPos);
	enemy->SetPos(VGet(0.0f, 0.0f, -600.0f));
	VECTOR G = VGet(0, -1, 0);
	bool isJunp = false;
	player->SetImg(MV1LoadModel("data/player.mv1"));
	player->SetDir(VGet(0, 0, 0));
	player->SetAnimSpeed(10);
	player->SetAnimType(player->Stop);
	player->SetNowAnimTime(0);
	MV1SetAttachAnimTime(player->GetImg(),player->GetAnimType(),player->GetNowAnimTime());
	int handle = player->GetImg();
	int materialNum = MV1GetMaterialNum(handle);
	for (int i = 0; i < materialNum; ++i)
	{
		MV1SetMaterialDifColor(handle, i, GetColorF(1.0f, 1.0f, 1.0f,1.0f)); // 拡散反射を最大に
		MV1SetMaterialAmbColor(handle, i, GetColorF(0.3f, 0.3f, 0.3f,0.3f)); // 環境光の反射も設定
	}
	SetUseBackCulling(FALSE);
	enemy->SetImg(MV1LoadModel("data/Monstor.mv1"));
	enemy->SetDir(VGet(0, ConversionRad(180), 0));
	enemy->SetAnimSpeed(10);
	enemy->SetAnimType(enemy->Hit);
	enemy->SetNowAnimTime(0);
	enemy->SetTarget(*player);
	
	MV1SetAttachAnimTime(enemy->GetImg(), enemy->GetAnimType(), enemy->GetNowAnimTime());

	///////
	SetCameraPositionAndTarget_UpVecY(VGet(0, 0, 0), player->GetPos());
	
	MV1SetPosition(player->GetImg(), player->GetPos());
	MV1SetPosition(enemy->GetImg(),enemy->GetPos());

	int SpotL= CreateSpotLightHandle(VGet(0.0f, 1000.0f, 0.0f), VGet(0.0f, -1.0f, 0.0f), DX_PI_F / 2.0f, DX_PI_F / 4.0f, 2000.0f,0.01f,  0.002f,		0.0f);
	player->SetScale(1.0f);// 試しに10倍
	enemy->SetScale(5.0f);  // 試しに10倍


	fps fps;
	fps.Initialization(1.0 / 60.0);
	Sphere_Collision *Collision_Measurement=new Sphere_Collision;
	
	
	Camera *camera=new Camera(100.0f,10000.0f, VAdd(PlayerPos, VGet(0.0f, 200.0f, 1000.0f)),PlayerPos);
	camera->GetAngle(PlayerPos);
	SetLightAmbColor(GetColorF(0.3f, 0.3f, 0.3f,0.3f));
	ChangeLightTypeDir(VGet(0,-1,0));
	Bar *playerHp= new Bar(player);
	Bar *enemyHpBar=new Bar(enemy);
	SpecialMove *SPMove= new SpecialMove(*camera, *player, *enemy);
	auto NowTime = std::chrono::high_resolution_clock::now();
	auto LastTime = NowTime;
	// 経過時間をミリ秒に変換して取得
	std::chrono::duration<float, std::milli> duration_ms = NowTime - LastTime;
	float deltaTime = duration_ms.count();

	VECTOR BesePoint = VGet(0, 0, 0);
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		NowTime= std::chrono::high_resolution_clock::now();
		std::chrono::duration<float, std::milli> duration_ms = NowTime - LastTime;
		deltaTime = duration_ms.count()/1000;
		LastTime = NowTime;


		SetUseLighting(true); // ライティングを有効にする

		fps.Start();
	
		ClearDrawScreen();
/////入力およびその対応///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (!player->GetInSpecialMove()&&player->GetAnimType()!=player->Hit)
		{
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
				MATRIX RotY = MGetRotY(ConversionRad(MoveMouseX * 0.1));
				camera->RotaionAxis(player->GetPos(), RotY);
				player->Turn(VGet(0, ConversionRad(MoveMouseX * 0.1), 0));
				camera->Look(player->GetPos());
				
			}
		}
		
		
		////////////////////必殺技スタート///////////////////////////////////////////////////////////
		if (CheckHitKey(KEY_INPUT_G)&&!player->GetInSpecialMove())
		{
			SPMove = new SpecialMove(*camera, *player, *enemy);
			player->SetStartLiveTime(player->GetLiveTime());
			player->SetInSpecialMove(true);
		}
		//////////////////////////////////////////////////////////////////////////////////////////
		if (CheckHitKey(KEY_INPUT_M))
		{
			
		    
			camera->GetAngle(PlayerPos);
			camera->ResetOffset(VGet(100, 100, 200), PlayerPos);
			camera->GetAngle(PlayerPos);

			camera->Action(VGet(100,100,200), PlayerPos, 0.0f, 9.50000f, -0.1000000);
		
			

		}
		bool isInput = false;
		if (player->GetIsHit())
		{
		 player->SetMove(VAdd(player->GetMove(), G));

		}
		else if(!player->GetInSpecialMove())
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
		if (CheckHitKey(KEY_INPUT_C))
		{
			VECTOR CPos = VCross(VNorm(Distans), VGet(0, -1, 0));
			float rag = 60.f;
			CPos = VScale(CPos,VSize(Distans)*atan(ConversionRad(rag)));
			camera->ResetOffset(CPos,player->GetPos());
			camera->Look(VAdd(player->GetPos(), VScale(Distans, 0.75)));
		}
		float Distance = VSize(Distans); 
	
		
////カメラ系///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//必殺技時のカメラの動き
		if (player->GetInSpecialMove())
		{
		 player->SetInSpecialMove(SPMove->Update(deltaTime));

		}
		///通常時
		else
		{
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
		}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		Sphere_Collision PlayerCollison = player->GetCollison();
		PlayerCollison.SetPos(VAdd(PlayerCollison.GetPos(), player->GetMove()));
	
//////更新///////////////////////////////////////////////////////////////////////////////////////////////////////	
		if (!player->GetInSpecialMove())
		{
			player->Update(deltaTime);
			enemy->Update(deltaTime);
		}
		
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

		
/////衝突////////////////////////////////////////////////////////////////////////////////////////////////////
		if (Collision_Measurement->Collison(PlayerCollison, enemy->GetCollison()))
		{
			VECTOR Distance = VSub(player->GetPos(), enemy->GetPos());

			Sphere_Collision PlayerCollison = player->GetCollison();
			Sphere_Collision enemyCollison = enemy->GetCollison();

			VECTOR TakeDistance = VScale(VNorm(Distance), (enemyCollison.GetSphereSize() + PlayerCollison.GetSphereSize()+1));

			TakeDistance = VSub(TakeDistance, Distance);
			player->SetMove(VAdd(player->GetMove(), TakeDistance));
			player->SetPos(VAdd(player->GetPos(), player->GetMove()));
		}
		
		
		///enemy攻撃

		if (Collision_Measurement->Collison(player->GetCollison(), enemy->GetAttackCollison())&&player->GetAnimIndex()!=player->Hit)
		{
			player->SetMove(VAdd(VScale( enemy->GetMove(),3),VGet(0,30,0)));
			player->SetAnimType(player->Hit);
			player->SetIsHit(true);
			player->SubHp(enemy->GetAttack());
			player->SetLastDamageTime();
			/////必殺キャンセル
			player->SetInSpecialMove(false);
		}
		
	
		////player攻撃
		if (Collision_Measurement->Collison(player->GetAttackCollison(), enemy->GetCollison())&&enemy->GetMoveType()!=enemy->hit_stop)
		{
			
			VECTOR Knockback = VScale(VNorm(VSub(enemy->GetPos(), player->GetPos())), player->GetAttackCollison().GetSphereSize() * deltaTime);
			if (player->GetInSpecialMove())
			{
				Knockback=VScale(VNorm(VSub(enemy->GetPos(), player->GetPos())), player->GetAttackCollison().GetSphereSize() * deltaTime*10);
			}
			Knockback.y = 0;
			
			enemy->SetMove((Knockback));
			enemy->SetMoveType(enemy->hit_stop);
			enemy->SetAnimType(enemy->Hit);
			enemy->SubHp(player->GetAttack());
			
		}
		camera->Update(player->GetPos());
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HPバーの更新//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
		playerHp->Update(*camera);
		enemyHpBar->Update(*camera);
/////描画//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	

		MV1SetPosition(player->GetImg(), player->GetPos());
		MV1SetPosition(enemy->GetImg(), enemy->GetPos());
		if (!player->GetInSpecialMove())
		{
			if (enemyHpBar->CheakIsDraw(*player, *camera))
			{
				enemyHpBar->Draw();
			}
			playerHp->Draw();
		}
		////エネミーの点滅
		if (enemy->GetMoveType() == enemy->hit_stop && player->GetInSpecialMove()&& fabs(fmod(player->GetLiveTime(), 0.1f)) < 0.01f)
		{
			enemy->SetisDraw( !enemy->GetisDraw());
			if (camera->GetisZoom())
			{
				camera->EndZoom();
			}
			else
			{
				camera->StartZoom(200.0f);
			}
		}
		MV1DrawModel(BackModel);
		player->Draw();
		enemy->Draw();              // モデルの描画
		// モデルの描画
			   // モデルの描画
		
		ScreenFlip();// 裏画面の内容を表画面に反映 
///////fps調整///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

