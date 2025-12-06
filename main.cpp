
#include<vector>
#include "DxLib.h"
#include"Arithmetic.h"
#include"Effect.h"
#include "fps.h"
#include"Player.h"
#include"Enemy.h"
#include"Bsr.h"
#include "SpecialMove.h"
#include "EffectM.h"
#include "Sound.h"
#include "ModelCheckers.h"
using namespace std::chrono;
const VECTOR StartPlayerPos = VGet(0, 0, 0);
enum GameModeType{Start,Win,Lose,Game};

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
	SetWriteZBuffer3D(TRUE);

	if(Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	////マウス系の初期化　宣言
	int MouseX, MouseY;
	GetMousePoint(&MouseX, &MouseY);
	///player初期化
	float BaseY = NULL;
	VECTOR JumpPower = VGet(0, 30, 0);
	VECTOR G = VGet(0, -1, 0);

	Player *player=new Player();
	player->SetPos(StartPlayerPos);
	bool isJunp = false;
	player->SetImg(MV1LoadModel("data/player.mv1"));
	player->SetDir(VGet(0, 0, 0));
	player->SetAnimSpeed(10);
	player->SetAnimType(player->Stop);
	player->SetNowAnimTime(0);
	MV1SetAttachAnimTime(player->GetImg(), player->GetAnimType(), player->GetNowAnimTime());
	int handle = player->GetImg();
	int materialNum = MV1GetMaterialNum(handle);
	for (int i = 0; i < materialNum; ++i)
	{
		MV1SetMaterialDifColor(handle, i, GetColorF(1.0f, 1.0f, 1.0f, 1.0f)); // 拡散反射を最大に
		MV1SetMaterialAmbColor(handle, i, GetColorF(0.3f, 0.3f, 0.3f, 0.3f)); // 環境光の反射も設定
	}
	SetUseBackCulling(FALSE);
	MV1SetPosition(player->GetImg(), player->GetPos());
	player->SetScale(1.0f);// 試しに10倍
	

	///enemy初期化
	Enemy* enemy = new Enemy();
	enemy->SetPos(VGet(0.0f, 0.0f, -600.0f));
	MV1SetPosition(enemy->GetImg(), enemy->GetPos());
	enemy->SetImg(MV1LoadModel("data/Monstor.mv1"));
	enemy->SetDir(VGet(0, ConversionRad(180), 0));
	enemy->SetAnimSpeed(10);
	enemy->SetAnimType(enemy->Dance);
	enemy->SetNowAnimTime(0);
	enemy->SetTarget(*player);
	enemy->SetScale(5.0f);  // 試しに10倍


	MV1SetAttachAnimTime(enemy->GetImg(), enemy->GetAnimType(), enemy->GetNowAnimTime());



	///背景
	int  BackModel = MV1LoadModel("data/Dome_Y902.mv1");
	int  TileModel = MV1LoadModel("data/Tile.mv1");
	MV1SetPosition(BackModel, VGet(0, 0, 0));
	MV1SetScale(BackModel, VGet(5, 5, 5));
	MV1SetScale(TileModel, VGet(5, 0.01f, 5));




	///////カメラの初期化
	SetCameraPositionAndTarget_UpVecY(VGet(0, 0, 0), player->GetPos());
	////スタート時のカメラ
	Camera* camera = new Camera(100.0f, 10000.0f, VAdd(enemy->GetPos(),StartCamera), enemy->GetPos());
	camera->CalculateAngle(PlayerPos);
	camera->CalculateTargetAngle(player->GetPos());
	SetUseLighting(TRUE);
	SetLightAmbColor(GetColorF(0.3f, 0.3f, 0.3f, 0.3f));
	ChangeLightTypeDir(VGet(0, -1, 0));
	SetLightDirection(VGet(0.5f, 1, 0));

	

	int SpotL= CreateSpotLightHandle(VGet(0.0f, 1000.0f, 0.0f), VGet(0.0f, -1.0f, 0.0f), DX_PI_F / 2.0f, DX_PI_F / 4.0f, 2000.0f,0.01f,  0.002f,0.0f);
	fps fps;
	fps.Initialization(1.0 / 60.0);

	
	Sphere_Collision *Collision_Measurement=new Sphere_Collision;
	
	
	Bar *playerHp= new Bar(player);
	Bar *enemyHpBar=new Bar(enemy);
	SpecialMove *SPMove= new SpecialMove(*camera, *player, *enemy);
	///時間系の初期化宣言
	auto NowTime = std::chrono::high_resolution_clock::now();
	auto LastTime = NowTime;
	// 経過時間をミリ秒に変換して取得
	std::chrono::duration<float, std::milli> duration_ms = NowTime - LastTime;
	float deltaTime = duration_ms.count();
	float TotalTime = 0.0f;
	///ゲームモード設定
	int GameMode = Start;
	bool isInput = false;
	bool InModeCheng = false;
	int FadeAlpha = 0;
	bool OnWall = false;
	XINPUT_STATE* InputState=new XINPUT_STATE;
	VECTOR BasePoint = VGet(0, 0, 0);
	float FieldSize = 4000.0f;
	Sphere_Collision Field;
	Sphere_Collision NextPlayer;
	Sphere_Collision NextEnemy;
	Field.SetPos(VGet(0, 0, 0));
	Field.SetSphereSize(FieldSize);
	///Effet
	EffectImg* ImpactE = new EffectImg("data/Shock.efkefc", 100);
	EffectImg* RingE = new EffectImg("data/Ring.efkefc",100);
	EffectM::Add(*RingE);
	////音
	SetCreate3DSoundFlag(TRUE);
	Set3DSoundOneMetre(200);
	Sound* HitSound = new Sound("data/Hit.wav");
	Sound* AttackSound = new Sound("data/Attack.wav");
	Sound* SpSound = new Sound("data/SpAttack.wav");
	Sound* BGM = new Sound("data/Thunderstorm.wav");

	XINPUT_STATE* Input = new XINPUT_STATE;

	
	
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		NowTime= std::chrono::high_resolution_clock::now();
		std::chrono::duration<float, std::milli> duration_ms = NowTime - LastTime;
		deltaTime = duration_ms.count()/1000;
		LastTime = NowTime; 
		isInput = false;
		Effekseer_Sync3DSetting();


		SetUseLighting(true); // ライティングを有効にする

		fps.Start();
	
 		ClearDrawScreen();

		GetJoypadXInputState(DX_INPUT_PAD1, Input);

		switch (GameMode)
		{
		case Game:
		{

if (FadeAlpha > 0 && !InModeCheng)
{
	FadeAlpha -= 255 / 2 * deltaTime;
	if (FadeAlpha > 0)
	{
		FadeAlpha = 0;
	}
}


if (player->GetIsHit())
{
	float Checker = player->GetPos().y + G.y;
	if (Checker >= 0)
	{

	player->SetMove(VAdd(player->GetMove(), G));

	}	
	/////
	if (player->GetTotalAnimTime() <= player->GetNowAnimTime() + deltaTime)
	{

		camera->ResetOffset(VTransformSR(DefaultCamera,MGetRotY(player->GetDir().y)), player->GetPos());
		camera->CalculateAngle(player->GetPos());
		camera->CalculateTargetAngle(player->GetPos());
		player->SetIsHit(false);
	}

}
else if (!player->GetInSpecialMove())
{
	isInput = player->Input(*camera);
	enemy->SelectMove();
}

////入力された移動を調整
if (VSize(VGet(camera->GetPos().x, 0, camera->GetPos().z)) > FieldSize)
{
	OnWall = true;
}
else
{
	OnWall = false;
}
if (VSize(VAdd(player->GetPos(), player->GetMove())) > FieldSize)
{
	VECTOR PassingPoint = VAdd(player->GetPos(), player->GetMove());
	VECTOR SetPoint = VNorm(PassingPoint);
	SetPoint = VScale(SetPoint, FieldSize);
	player->SetMove(VSub(SetPoint, player->GetPos()));
}
if (player->GetPos().y <= BaseY)
{
	isJunp = false;
	player->SetPos(VGet(player->GetPos().x, BaseY, player->GetPos().z));
	JumpPower = VGet(0, 30, 0);

}

////衝突////////////////////////////////////////////////////////////////////////////////////////////////////
///次の動きの判定
NextPlayer.SetPos(VAdd(player->GetPos(), player->GetMove()));
NextPlayer.SetSphereSize(player->GetCollison().GetSphereSize());
NextEnemy.SetPos(VAdd(enemy->GetCollison().GetPos(), enemy->GetMove()));
NextEnemy.SetSphereSize(enemy->GetCollison().GetSphereSize());
///かべとplayer
if (VSize(VSub(Field.GetPos(), VAdd(player->GetPos(), player->GetMove()))) >= Field.GetSphereSize() - player->GetCollison().GetSphereSize()/2)
{
	

	////1中心から
	VECTOR AddMove = VSub(NextPlayer.GetPos(), Field.GetPos());

	///fieldの半径
	AddMove = VScale(VNorm(AddMove),(Field.GetSphereSize()-NextPlayer.GetSphereSize()/2));
	AddMove = VSub(AddMove,NextPlayer.GetPos());
	player->SetMove(VAdd(player->GetMove(), AddMove));
	///再更新　ほかの判定でも使うので
	NextPlayer.SetPos(VAdd(player->GetPos(), player->GetMove()));
	NextPlayer.SetSphereSize(player->GetCollison().GetSphereSize());
}
///かべとenemy
if (VSize(VSub(Field.GetPos(), VAdd(enemy->GetPos(), enemy->GetMove()))) >= Field.GetSphereSize() - enemy->GetCollison().GetSphereSize()/2)
{
	
	VECTOR AddMove = VSub(NextEnemy.GetPos(),Field.GetPos());
	AddMove = VScale(VNorm(AddMove),Field.GetSphereSize()-enemy->GetCollison().GetSphereSize() / 2);
	AddMove = VSub(AddMove,NextEnemy.GetPos());
	enemy->SetMove(VAdd(enemy->GetMove(), AddMove));
	///再更新　ほかの判定でも使うので
	NextEnemy.SetPos(VAdd(enemy->GetPos(), enemy->GetMove()));
	NextEnemy.SetSphereSize(enemy->GetCollison().GetSphereSize());
}
///enemy攻撃

if (Collision_Measurement->Collison(NextPlayer, enemy->GetAttackCollison()) && player->GetAnimType() != player->Hit)
{
	VECTOR Move = VSub(NextPlayer.GetPos(),NextEnemy.GetPos());
	Move = VTransformSR(Move, MGetRotY(enemy->GetDir().y));
	Move = VScale(VNorm(Move), enemy->GetAttackCollison().GetSphereSize() / 4);
	player->SetMove(Move);
	player->SetAnimType(player->Hit);
	player->SetIsHit(true);
	player->SubHp(enemy->GetAttack());
	player->SetLastDamageTime();
	/////必殺キャンセル
	player->SetInSpecialMove(false);
	
	///playerの正面に移動
	VECTOR FRONT = VGet(0, 100, -1000);
	FRONT = VTransformSR(FRONT, MGetRotY(player->GetDir().y));
	camera->ResetOffset(FRONT, player->GetPos());
	camera->CalculateAngle(player->GetPos());
	camera->CalculateTargetAngle(player->GetPos());

	/*camera->ResetOffset(DefaultCamera, player->GetPos());*/
	StartJoypadVibration(DX_INPUT_PAD1, 1000, 400, -1);
}

 else if (VSize(VSub(player->GetPos(), enemy->GetPos())) <= 2000)
{

	
	///衝突検査（ここでするとSphereを持ち越さない）
	if (Collision_Measurement->Collison(NextEnemy, NextPlayer))
	{
		VECTOR Distance = VSub(NextPlayer.GetPos(), NextEnemy.GetPos());

		VECTOR TakeDistance = VScale(VNorm(Distance), (NextEnemy.GetSphereSize() + NextPlayer.GetSphereSize() + 1));

		TakeDistance = VSub(TakeDistance, Distance);
		player->SetMove(VAdd(player->GetMove(), TakeDistance));

	}



}


////カメラ系///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		//必殺技時のカメラの動き
if (player->GetInSpecialMove())
{
	player->SetInSpecialMove(SPMove->Update(deltaTime));

}
///通常時
else if (!OnWall)
{

	if (!isInput)
	{
		camera->StartMove(VScale(VSub(VAdd(player->GetPos(), camera->GetOffset()), camera->GetPos()), 0.1f));

		if (VSize(player->GetMove()) <= 0)
		{
			BasePoint = player->GetPos();

		}
	}
	else if (VSize(VSub(player->GetPos(), BasePoint)) >= 200)
	{
		/////切り替えし。ターンの処理
		if (player->GetTurn())
		{
			BasePoint = player->GetPos();
		}
		 camera->StartMove(VScale(player->GetMove(), 1.0f));
	}
			}
			/////カメラが壁に触れているときは動きと同じ大きさの壁ー＞中心のベクトルを足したものをカメラにつける
			else
			{
				VECTOR Move = player->GetMove();
				////////0からかめらまで
				VECTOR Line = camera->GetPos();
				Line.y = 0;
				////カメラに近づく力を求める
				VECTOR  Proj = VScale(Line,( VDot(Move, Line) / VDot(Line,Line)));
				VECTOR PassingPoint = VAdd(player->GetPos(), Move);
				VECTOR SetPoint = VNorm(PassingPoint);
				SetPoint = VScale(SetPoint, FieldSize);
				float Rate = VSize(SetPoint) / VSize(VGet(camera->GetPos().x, 0, camera->GetPos().z));///Yの高さは比率でとる
				SetPoint.y = camera->GetPos().y * Rate;
				VECTOR Offset = VSub(SetPoint, player->GetPos());
				camera->ResetOffset(Offset, player->GetPos());
				camera->Look(player->GetPos());

				/////ちかちかする理由
				if (VSize(DefaultCamera)<VSize(camera->GetOffset()))
				{
					camera->StartMove(player->GetMove());
				}
				else
				{
					
					
				
					
					/////壁からの横移動.
					//Move = VSub(Move, Proj);
					/////回転移動　軸を中心にして
					//camera->StartMove(Move);
					/////もし超えていたら戻すよう

				}
				camera->Look(player->GetPos());
			}
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			Sphere_Collision PlayerCollison = player->GetCollison();
			PlayerCollison.SetPos(VAdd(PlayerCollison.GetPos(), player->GetMove()));
			//////更新///////////////////////////////////////////////////////////////////////////////////////////////////////	
			if (!player->GetInSpecialMove())
			{
				BGM->Loop();
				player->Update(deltaTime);
				enemy->Update(deltaTime);
			}
			else
			{
				BGM->Stop();
			}
			


		
		
			////player攻撃
			if (Collision_Measurement->Collison(player->GetAttackCollison(), enemy->GetCollison()) && enemy->GetMoveType() != enemy->hit_stop)
			{
				////敵の方向
				VECTOR EnemyDir = VNorm(VSub(enemy->GetPos(),player->GetPos()));
				float Angle = atan2f(EnemyDir.x, EnemyDir.z); 
				enemy->SetDir(VGet(0,Angle,0));
				VECTOR Knockback = VScale(VNorm(VSub(enemy->GetPos(), player->GetPos())), player->GetAttackCollison().GetSphereSize() * deltaTime);
				if (player->GetInSpecialMove())
				{
				 Knockback = VScale(VNorm(VSub(enemy->GetPos(), player->GetPos())), player->GetAttackCollison().GetSphereSize() * deltaTime * 10);
				}
				Knockback.y = 0;
				const char* HipName = "mixamorig:LeftToe_End_end";
				VECTOR test = MV1GetPosition(player->GetImg());
				int LegIndex = MV1SearchFrame(player->GetImg(), HipName);
				if (LegIndex >= 0)
				{
					VECTOR EffctPos = MV1GetFramePosition(player->GetImg(), LegIndex);
					EffectM::Add(*ImpactE,EffctPos);
				}
				
				AttackSound->Play();
				player->AddSpGauge(20);
				enemy->SetMove((Knockback));
				enemy->SetMoveType(enemy->hit_stop);
				enemy->SetAnimType(enemy->Hit);
				enemy->SubHp(player->GetAttack());
				StartJoypadVibration(DX_INPUT_PAD1, 1000, 400, -1);


			}
			//////カメラの押し戻し
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
			if (enemy->GetMoveType() == enemy->hit_stop && player->GetInSpecialMove()&& fabs(fmod(player->GetLiveTime(), 0.1f)) < 0.01f&&player->GetAttackCollison().GetSphereSize()>0)
			{
				enemy->SetisDraw(!enemy->GetisDraw());
				if (camera->GetisZoom())
				{
					camera->EndZoom();
				} 
				else
				{
					camera->StartZoom(200.0f);
				}
			}
			else
			{
				camera->EndZoom();
				enemy->SetisDraw(true);
			}
			/*if (VSize(VGet(camera->GetPos().x,0,camera->GetPos() .z))> FieldSize)
			{
				camera->SetPos(VScale(VNorm(camera->GetPos()), FieldSize));
				OnWall = true;
			}
			else
			{
				OnWall = false;
			}
			*/
		
			if (VSize(enemy->GetPos()) > FieldSize)
			{
				enemy->SetPos(VScale(VNorm(enemy->GetPos()), FieldSize));
			}
			//////勝ち判定
			if (player->GetHp() <= 0&&player->GetAnimType()!=player->Hit)
			{
				GameMode = Lose;
				player->SetAnimSpeed(10);
				MATRIX RotY = MGetRotY(enemy->GetDir().y);
				VECTOR Offset = VTransformSR(LoseCamera, RotY);
				camera->ResetOffset(Offset, player->GetPos());
				player->SetAnimType(player->Down);
				BGM->Stop();
			}
			if (enemy->GetHp() <= 0&&!player->GetInSpecialMove())
			{
				GameMode = Win;
				MATRIX RotY = MGetRotY(enemy->GetDir().y);
				VECTOR Offset = VTransformSR(WinCameraFast, RotY);
				enemy->SetisDraw(true);
				enemy->SetAnimType(enemy->Dwon);
				camera->ResetOffset(Offset, enemy->GetPos());
				enemy->SetStartLiveTime(enemy->GetLiveTime());
				BGM->Stop();
			

			}
			MV1DrawModel(BackModel);
			MV1DrawModel(TileModel);
			EffectM::Update(deltaTime);
			EffectM::Draw();
			player->Draw();
			if (player->GetAnimType() != player->Hit)
			{
				enemy->Draw();
			}
			 // モデルの描画
			// モデルの描画
				   // モデルの描画
		}
		break;
		case Start:
			if (FadeAlpha > 0 && !InModeCheng)
			{
			
				FadeAlpha -= 255 / 2 * deltaTime;
				if (FadeAlpha < 0)
				{
					FadeAlpha = 0;
				}

			}
			else
			{
				////回転量を算出
				float Move = 40 * deltaTime;
				MATRIX RotY = MGetRotY(ConversionRad(Move));
				VECTOR Axis = VAdd(enemy->GetPos(), VGet(0, 0, 200));///モデルの位置とPosのずれ直し
				enemy->SetPos(VGet(0, 0, 0));
				camera->RotaionAxis(Axis, RotY);
				camera->Look(Axis);
				enemy->AnimUpdate(deltaTime);
				if (CheckHitKey(KEY_INPUT_W))
				{
					HitSound->Play(VGet(0,0,0),VGet(6000,0,0),VGet(1,0,0),VGet(0,1,0),VGet(0,0,1));
					/*EffectM::Add(*ImpactE);*/
					EffectM::Add(*RingE);

				}
				if (!enemy->GetIsAnim())
				{
					enemy->SetNowAnimTime(0.0f);
				}
				if (Input->Buttons[XINPUT_BUTTON_START]!=0 && GetJoypadNum() != 0)
				{
					InModeCheng = true;


				}
				if (InModeCheng)
				{
					///画面を暗く
					FadeAlpha += 255 / 2 * deltaTime;
				}
				else
				{
					///Modeチェンジが押されるまでの表現
				}
				if (FadeAlpha >= 255)///画面が真っ黒になったら
				{
					GameMode = Game;
					camera->ResetOffset(DefaultCamera, player->GetPos());
					InModeCheng = false;
					player = new Player();
					player->SetPos(StartPlayerPos);
					bool isJunp = false;
					player->SetImg(MV1LoadModel("data/player.mv1"));
					player->SetDir(VGet(0, 0, 0));
					player->SetAnimSpeed(10);
					player->SetAnimType(player->Stop);
					player->SetNowAnimTime(0);
					MV1SetAttachAnimTime(player->GetImg(), player->GetAnimType(), player->GetNowAnimTime());
					MV1SetPosition(player->GetImg(), player->GetPos());
					player->SetScale(1.0f);// 試しに10倍
					
					///enemy初期化
					enemy = new Enemy();
					enemy->SetPos(VGet(0.0f, 0.0f, -600.0f));
					MV1SetPosition(enemy->GetImg(), enemy->GetPos());
					enemy->SetImg(MV1LoadModel("data/Monstor.mv1"));
					enemy->SetDir(VGet(0, ConversionRad(180), 0));
					enemy->SetAnimSpeed(10);
					enemy->SetAnimType(enemy->Dance);
					enemy->SetNowAnimTime(0);
					enemy->SetTarget(*player);
					enemy->SetScale(5.0f);  // 試しに10倍

					playerHp = new Bar(player);
					enemyHpBar = new Bar(enemy);


					MV1SetAttachAnimTime(enemy->GetImg(), enemy->GetAnimType(), enemy->GetNowAnimTime());

					SPMove = new SpecialMove(*camera, *player, *enemy);
				}
				
			
				SetFontSize(256);
				DrawString(100, 250, "KILL ME", GetColor(244, 229, 17));
				SetFontSize(64);
				DrawString(600, 550, "NEXT STSRT", GetColor(244, 229, 17));
				ModelCheckers test;
				test.ShowFrameName(player->GetImg());

			}
			MV1DrawModel(BackModel);
			MV1DrawModel(TileModel);
			EffectM::Update(deltaTime);
			EffectM::Draw();
			enemy->Draw();
			break;
		case  Win:
			MV1DrawModel(BackModel);
			{

			if (Input->Buttons[XINPUT_BUTTON_START] != 0)
			{
				InModeCheng = true;

			}
			if (InModeCheng)
			{
				///画面を暗く
				FadeAlpha += 255 / 2 * deltaTime;
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
				enemy->SetPos(VGet(0.0f, 0.0f, 0.0f));
				
				if (!enemy->GetIsAnim())
				{
					SetFontSize(128);
					DrawString(600, 350, "YOU WIN", GetColor(244, 229, 17));
					SetFontSize(64);
					DrawString(600, 550, "NEXT STSRT", GetColor(244, 229, 17));

				}
				

			}
		}
			enemy->AddLiveTime(deltaTime);
			enemy->AnimUpdate(deltaTime);
			player -> Draw();
			enemy->Draw();
			MV1DrawModel(TileModel);
			if (FadeAlpha >= 255)///画面が真っ黒になったら
			{
				GameMode = Start;
				enemy->SetPos(VGet(0.0f, 0.0f, 0.0f));
				camera->ResetOffset(StartCamera, enemy->GetPos());
				enemy->SetAnimType(enemy->Dance);
				InModeCheng = false;
			}
			break;
		case Lose:
			MV1DrawModel(BackModel);
			if (Input->Buttons[XINPUT_BUTTON_START] != 0)
			{
				InModeCheng = true;

			}
			if (InModeCheng)
			{
				///画面を暗く
				///画面を暗く
				FadeAlpha += 255 / 2 * deltaTime;
			}
			else
			{
				///Modeチェンジが押されるまでの表現
			}
			if (FadeAlpha >= 255)///画面が真っ黒になったら
			{
				GameMode = Start;
				enemy->SetPos(VGet(0.0f, 0.0f, -600.0f));
				MV1SetPosition(enemy->GetImg(), enemy->GetPos());
				camera->ResetOffset(StartCamera, enemy->GetPos());
				InModeCheng = false;

			}
			if (!player->GetIsAnim())
			{
				SetFontSize(128);
				DrawString(500, 350, "YOU LOSE", GetColor(244, 229, 17));
				SetFontSize(64);
				DrawString(600, 550, "NEXT STSRT", GetColor(244, 229, 17));
			}
			player->AddLiveTime(deltaTime);
			player->AnimUpdate(deltaTime);
			player->Draw();
			MV1DrawModel(TileModel);

			// アルファ値（透明度）の設定（0〜255）
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 20);  // ← 透明度80（調整可能）
			DrawBox(0, 0, 1600, 1200, GetColor(255, 0, 0), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			break;
	
		
		}
		
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, FadeAlpha);
		DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		

		
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
	

	Effkseer_End();

	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}

