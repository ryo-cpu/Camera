
#include <vector>
#include "DxLib.h"
#include "Box.h"
#include "fps.h"
#include "Counter.h"
#include "Bar.h"
#include "EffectM.h"
#include "Sound.h"
#include "ModelCheckers.h"
#include "Capsule.h"
#include "UIBar.h"
#include "Shadow.h"
#include "Scene's.h"
#include"Counter.h"
#include"UI.h"
#include"UIArrow.h"
//#include "Arithmetic.h"
using namespace std::chrono;
const VECTOR StartPlayerPos = VGet(0.0f, 0.0f, 0.0f);
const float HitStopTime = 0.4f;
enum GameModeType { Start, Win, Lose, Game,Spawn };
const char* LeftHand = "mixamorig:LeftHand";
const int HPFontSize = 100;

const char* HipName = "mixamorig:Hips";
/// メイン関数
/// </summary>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// 確実に存在


  // ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;	// エラーが起きたら直ちに終了
	}

	//// 画面モードのセット
	//ChangeWindowMode(TRUE);
	ChangeWindowMode(TRUE);
	SetGraphMode(1600, 900, 16);

	VECTOR PlayerPos = VGet(0, 0.0f, 0.0f);


	SetDrawScreen(DX_SCREEN_BACK);	// 裏画面を描画対象にする
	SetUseZBufferFlag(TRUE);		// Ｚバッファを使用する
	SetWriteZBufferFlag(TRUE);		// Ｚバッファへの書き込みを行う
	SetUseBackCulling(TRUE);		// バックカリングを行う
	SetWriteZBuffer3D(TRUE);

	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	///player初期化
	float BaseY = NULL;
	VECTOR JumpPower = VGet(0.0f, 30.0f, 0.0f);
	VECTOR G = VGet(0.0f, -1, 0.0f);

	Player* player = new Player(MV1LoadModel("data/player.mv1"));
	player->SetNextImg(MV1LoadModel("data/playerLow.mv1"));
	player->SetCapsuleCollisionRsize(30.0f);
	player->SetPos(StartPlayerPos);
	bool isJump = false;
	player->SetDir(VGet(0.0f, 0.0f, 0.0f));
	player->SetAnimSpeed(PlayerAnimSpeed);
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
	player->SetScale(1.0f);


	///enemy初期化
	Enemy* enemy = new Enemy(MV1LoadModel("data/Monstor.mv1"));
	enemy->SetNextImg(MV1LoadModel("data/MonstorLow.mv1"));
	enemy->SetPos(VGet(0.0f, 0.0f, -600.0f));
	MV1SetPosition(enemy->GetImg(), enemy->GetPos());
	enemy->SetDir(VGet(0.0f, ConversionRad(180), 0.0f));
	enemy->SetAnimSpeed(EnemyAnimSpeed);
	enemy->SetAnimType(enemy->Dance);
	enemy->SetNowAnimTime(0);
	enemy->SetTarget(*player);
	enemy->SetScale(5.0f);
	enemy->SetCapsuleCollisionRsize(80.0f);



	MV1SetAttachAnimTime(enemy->GetImg(), enemy->GetAnimType(), enemy->GetNowAnimTime());



	///背景
	SetUseBackCulling(FALSE);
	int  BackModel = MV1LoadModel("data/Dome_Y902.mv1");
	int  TileModel = MV1LoadModel("data/map3d/room-wide.mv1");
	int  ShadowImg = LoadGraph("data/TmpField.jpg");
	MV1SetPosition(BackModel, VGet(0, 0.0f, 0.0f));
	MV1SetPosition(TileModel, VGet(0.0f, 0.0f, 0.0f));
	MV1SetScale(BackModel, VGet(5, 5, 5));
	MV1SetScale(TileModel, VGet(150, 15.0f, 150.0f));





	///////カメラの初期化
	SetCameraPositionAndTarget_UpVecY(VGet(0, 0.0f, 0.0f), player->GetPos());
	////スタート時のカメラ
	Camera* camera = new Camera(100.0f, 10000.0f, VAdd(enemy->GetPos(), StartCamera), enemy->GetPos());
	camera->CalculateAngle(PlayerPos);
	camera->CalculateTargetAngle(player->GetPos());


	SetUseLighting(TRUE);
	SetLightAmbColor(GetColorF(0.3f, 0.3f, 0.3f, 0.3f));
	ChangeLightTypeDir(VGet(0, -1, 0.0f));
	VECTOR Light = VGet(0.5f, -1, 0.5f);
	SetLightDirection(Light);
	///影
	Shadow* shadow = new Shadow(Light);

	shadow->AddTarget(player->GetImg());
	shadow->AddTarget(enemy->GetImg());


	fps* Fps = new fps();
	Fps->Initialization(1.0 / 60.0);

	float HitStopStratTime = 0.0f;
	bool InHitStop = false;


	Sphere_Collision* Collision_Measurement = new Sphere_Collision;


	//Bar *playerHp= new Bar(player);
	Bar* enemyHpBar = new Bar(enemy);
	UIBar* playerHP = new UIBar(player, 100, 700);
	UIBar* playerSP = new UIBar(player, 100, 800);
	playerSP->SetMaxValue(MaxSpGauge);
	playerSP->SetFillColor(GetColor(255, 200, 0));
	playerSP->SetHandleSize(500, 20);
	SpecialMove* SPMove = new SpecialMove(*camera, *player, *enemy);
	UI* ui = new UI();
	ui->SetMessage("HP");
	ui->SetMessagePos(100, 600);
	ui->SetMessageSize(HPFontSize);
	UI* Explanation = new UI();	
	Explanation->SetMessage("B :ATTACK \nX :Special\nRB:Rolling");
	Explanation->SetMessagePos(1000, 0);
	Explanation->SetMessageSize(80);	
	Counter* counter = new Counter(*camera, *player, *enemy);

	float deltaTime = Fps->GetDeltaTime();
	float TotalTime = 0.0f;

	///ゲームモード設定
	int GameMode = Start;
	bool isInput = false;

	//fedein.out用　の透明化できるボックス
	Box* Fade = new Box(1600.0f, 900.0f, 255);
	bool OnWall = false;
	VECTOR BasePoint = VGet(0, 0.0f, 0.0f);
	float FieldSize = 4000.0f;
	Sphere_Collision Field;
	Sphere_Collision NextPlayer;
	Sphere_Collision NextEnemy;
	Field.SetPos(VGet(0.0f, 0, 0.0f));
	Field.SetSphereSize(FieldSize);
	///Effet
	
	EffectImg* RingE = new EffectImg("data/Ring.efkefc", 100.0f);
	EffectImg* ImpactE = new EffectImg("data/Shock.efkefc", 100);

	EffectM::Add(*RingE);
	////音
	SetCreate3DSoundFlag(TRUE);
	Set3DSoundOneMetre(200.0f);
	Sound* HitSound = new Sound("data/Hit.wav");
	Sound* AttackSound = new Sound("data/Attack.wav");
	Sound* SpSound = new Sound("data/SpAttack.wav");
	Sound* BGM = new Sound("data/Thunderstorm.wav");


	StartScene* start = new StartScene(camera, player, enemy, BackModel, TileModel, Fps, Fade, shadow);
	WinScene* win = new WinScene(camera, player, enemy, BackModel, TileModel, Fps, Fade, shadow);
	LoseScene* lose = new LoseScene(camera, player, enemy, BackModel, TileModel, Fps, Fade, shadow);
	SpawnScene* spawn = new SpawnScene(camera, player, enemy, BackModel, TileModel, Fps, Fade, shadow);

	UIArrow* Arrow = new UIArrow();

	bool InCounter = false;

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		isInput = false;
		Effekseer_Sync3DSetting();


		SetUseLighting(true); // ライティングを有効にする

		Fps->Start();

		ClearDrawScreen();
		deltaTime = Fps->GetDeltaTime();

		GetJoypadXInputState(DX_INPUT_PAD1, player->GetInputState());

		switch (GameMode)
		{
		case Game:
		{
			///画面をフェードイン
			if (Fade->GetAlpha() > 0)
			{
				Fade->SetAlpha(Fade->GetAlpha() - (static_cast<int> (255 / 2 * deltaTime)));
			}

			//playerの状態による更新
			if (player->GetIsHit())
			{
				float Checker = player->GetPos().y + G.y;
				if (Checker >= 0)
				{

					player->SetMove(VAdd(player->GetMove(), G));

				}


				if (StunTime <= player->GetNowAnimTime() + deltaTime)
				{

					camera->ResetOffset(VTransformSR(DefaultCamera, MGetRotY(player->GetDir().y)), player->GetPos());
					camera->CalculateAngle(player->GetPos());
					camera->CalculateTargetAngle(player->GetPos());
					player->SetIsHit(false);

					const char* HipName = "mixamorig:Hips";
					VECTOR test = player->GetFramPos("mixamorig:Hips");
					int HipIndex = MV1SearchFrame(player->GetImg(), HipName);
					if (HipIndex >= 0)
					{
						VECTOR SetPos = MV1GetFramePosition(player->GetImg(), HipIndex);
						SetPos.y = 0;
						player->SetPos(SetPos);
					}

				}

			}
			else if (InCounter)
			{
				InCounter = counter->Update(deltaTime);
			}
			///インプットを止め映像の更新のみをおこなう
			else if (InHitStop)
			{
				if (HitStopTime < TotalTime - HitStopStratTime)
				{
					InHitStop = false;
				}
			}
			else if (!player->GetInSpecialMove())
			{
				isInput = player->Input(*camera);
				//enemy->SelectMove();
			}

			////入力された移動を調整
			if (VSize(VGet(camera->GetPos().x, 0, camera->GetPos().z)) > FieldSize+20)
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
				isJump = false;
				player->SetPos(VGet(player->GetPos().x, BaseY, player->GetPos().z));
				JumpPower = VGet(0, 30, 0);

			}

			////衝突////////////////////////////////////////////////////////////////////////////////////////////////////
			///次の動きの判定
			if (!InHitStop)
			{
				NextPlayer.SetPos(VAdd(player->GetFramPos(HipName), player->GetMove()));
				NextPlayer.SetSphereSize(player->GetCollision().GetSphereSize());
				NextEnemy.SetPos(VAdd(enemy->GetCollision().GetPos(), enemy->GetMove()));
				NextEnemy.SetPos(VGet(NextEnemy.GetPos().x, 0, NextEnemy.GetPos().z));
				NextPlayer.SetPos(VGet(NextPlayer.GetPos().x, 0, NextPlayer.GetPos().z));
				NextEnemy.SetSphereSize(enemy->GetCollision().GetSphereSize());
				player->AnimUpdate(deltaTime);
				enemy->AnimUpdate(deltaTime);
				/*///モデルでも判定取りたいのでここで一時更新
				player->SetNextImg(player->GetImg());
				enemy->SetNextImg(enemy->GetImg());*/

				MV1SetPosition(player->GetNextImg(), NextPlayer.GetPos());
				MV1SetPosition(enemy->GetNextImg(), NextEnemy.GetPos());
				player->UpdateCapsuleCollision();
				player->UpdateCapsuleCollision(player->GetMove());
				enemy->UpdateCapsuleCollision();
				enemy->UpdateCapsuleCollision(enemy->GetMove());
				MV1DrawModel(enemy->GetNextImg());
				MV1DrawModel(player->GetNextImg());
			
			}
					
			/*const char* HipName = "mixamorig:Hips";
			int PlayerIndex = MV1SearchFrame(player->GetImg(), HipName);
			VECTOR WallPlayer = VGet(0, 0, 0);
			if (PlayerIndex >= 0)
			{
				WallPlayer = MV1GetFramePosition(player->GetImg(), PlayerIndex);
			}*/
			
			///かべとplayer
			if (VSize(VSub(Field.GetPos(),NextPlayer.GetPos())) >= Field.GetSphereSize() - player->GetCollision().GetSphereSize() && !player->GetInSpecialMove())
			{

				////1中心から
				VECTOR AddMove = VSub(NextPlayer.GetPos(), Field.GetPos());
				///中心から敵の最長
				AddMove = VAdd(AddMove, VScale(VNorm(AddMove), (player->GetCollision().GetSphereSize() / 2)));
				///フィールドの端から敵の最長（フィールドの長さを引く）
				AddMove = VSub(AddMove, VScale(VNorm(AddMove), Field.GetSphereSize()));
				///反転（敵の最奥から中心から）
				AddMove = VScale(AddMove, -1);

				///fieldの半径
				///ヒットじの特殊処理
				if (player->GetAnimType() == player->Hit)
				{
					AddMove = VScale(AddMove, 2);
				}

				player->SetMove(VAdd(player->GetMove(), AddMove));
				player->UpdateCapsuleCollision(AddMove);
				///再更新　ほかの判定でも使うので
				NextPlayer.SetPos(VAdd(player->GetPos(), player->GetMove()));
				NextPlayer.SetSphereSize(player->GetCollision().GetSphereSize());
			}

			///かべとenemy
			if (VSize(VSub(Field.GetPos(),NextEnemy.GetPos())) >= Field.GetSphereSize() - enemy->GetCollision().GetSphereSize() / 2 && !player->GetInSpecialMove())
			{

				VECTOR AddMove = VSub(NextEnemy.GetPos(), Field.GetPos());
				///中心から敵の最長
				AddMove = VAdd(AddMove, VScale(VNorm(AddMove), (enemy->GetCollision().GetSphereSize() / 2)));
				///フィールドの端から敵の最長（フィールドの長さを引く）
				AddMove = VSub(AddMove, VScale(VNorm(AddMove), Field.GetSphereSize()));
				///反転（敵の最奥から中心から）
				AddMove = VScale(AddMove, -1);
				if (enemy->GetAnimType() == enemy->Hit)
				{
					VECTOR HipPos = enemy->GetFramPos(HipName);
					HipPos.y = AddMove.y;
					AddMove = VAdd(AddMove, VSub(enemy->GetPos(), HipPos));
				}
				enemy->SetMove(VAdd(enemy->GetMove(), AddMove));
				enemy->UpdateCapsuleCollision(AddMove);
				///再更新　ほかの判定でも使うので
				NextEnemy.SetPos(VAdd(enemy->GetPos(), enemy->GetMove()));
				NextEnemy.SetSphereSize(enemy->GetCollision().GetSphereSize());
			}
			///enemy攻撃
			////player攻撃
			if (Collision_Measurement->Collision(player->GetAttackCollision(), NextEnemy))
			{
				////敵の方向
				if (!enemy->GetIsInvincible() || (player->GetInSpecialMove()))
				{
					VECTOR EnemyDir = VNorm(VSub(NextEnemy.GetPos(), player->GetPos()));
					float Angle = atan2f(EnemyDir.x, EnemyDir.z);
					enemy->SetDir(VGet(0, Angle, 0));
					VECTOR Knockback = VScale(VNorm(VSub(NextEnemy.GetPos(), NextPlayer.GetPos())), player->GetAttackCollision().GetSphereSize() * deltaTime);
					if (player->GetInSpecialMove())
					{
						Knockback = VScale(VNorm(VSub(NextEnemy.GetPos(), NextPlayer.GetPos())), player->GetAttackCollision().GetSphereSize() * deltaTime * 10);
						if (SPMove->GetWasHit() == false)
						{
							enemy->SubHp(player->GetAttack());
							SPMove->Hit();
							player->SetMove(VGet(0, 0, 0));
							AttackSound->Play();
							player->AddSpGauge(ChargeSpPowerAttack);

							Knockback.y = 0;
							enemy->SetKnockBack((Knockback));
							enemy->SetMove((Knockback));
							enemy->SetMoveType(enemy->hit_stop);
							enemy->SetAnimType(enemy->Hit);


							enemy->SetAnimSpeed(EnemyAnimSpeed);

							const char* HipName = "mixamorig:Hips";
							VECTOR test = MV1GetPosition(enemy->GetImg());
							int enemyIndex = MV1SearchFrame(enemy->GetImg(), HipName);
							int PlayerIndex = MV1SearchFrame(player->GetImg(), HipName);


							if (enemyIndex >= 0 && PlayerIndex >= 0)
							{
								VECTOR EffctPos;
								VECTOR EPos = MV1GetFramePosition(enemy->GetImg(), enemyIndex);
								VECTOR PPos = MV1GetFramePosition(player->GetImg(), PlayerIndex);
								EffctPos = VAdd(PPos, VScale(VSub(EPos, PPos), 0.25));


								VECTOR EffectMove = VSub(EffctPos, player->GetPos());
								EffectMove = VNorm(EffectMove);
								EffectM::Add(*ImpactE, EffctPos, VGet(0, 0, 0), EffectMove);
							}
						}

					}
					else if(!InCounter)
					{
						InHitStop = true;
						HitStopStratTime = TotalTime;
						enemy->SubHp(player->GetAttack());
						AttackSound->Play();
						player->AddSpGauge(ChargeSpPowerAttack);
						const char* HipName = "mixamorig:Hips";
						VECTOR test = MV1GetPosition(enemy->GetImg());
						int enemyIndex = MV1SearchFrame(enemy->GetImg(), HipName);
						int PlayerIndex = MV1SearchFrame(player->GetImg(), HipName);
						if (enemy->GetAnimType() == enemy->ArmSwing)
						{
							VECTOR EPos = MV1GetFramePosition(enemy->GetImg(), enemyIndex);
							camera->Look(EPos);
							InCounter= counter->Start();
							InHitStop = false;
						}
						enemy->SetKnockBack((Knockback));
						enemy->SetMove((Knockback));
						enemy->SetMoveType(enemy->hit_stop);
						enemy->SetAnimType(enemy->Hit);


						enemy->SetAnimSpeed(EnemyAnimSpeed);
						Knockback.y = 0;
						
						
						player->SetAttackCollision(player->GetPos(), 0.0f);
					
						
						
						if (enemyIndex >= 0 && PlayerIndex >= 0)
						{
							VECTOR EffctPos;
							VECTOR EPos = MV1GetFramePosition(enemy->GetImg(), enemyIndex);
							VECTOR PPos = MV1GetFramePosition(player->GetImg(), PlayerIndex);
							EffctPos = VAdd(PPos, VScale(VSub(EPos, PPos), 0.25));


							VECTOR EffectMove = VSub(EffctPos, player->GetPos());
							EffectMove = VNorm(EffectMove);
							EffectM::Add(*ImpactE, EffctPos, VGet(0, 0, 0), EffectMove);
						}
					}
					else
					{
						counter->SetHit(true);

						enemy->SubHp(player->GetAttack());
						AttackSound->Play();
						player->AddSpGauge(ChargeSpPowerAttack);
						enemy->SetMoveType(enemy->hit_stop);
						enemy->SetAnimType(enemy->Hit);
						const char* HipName = "mixamorig:Hips";
						int enemyIndex = MV1SearchFrame(enemy->GetImg(), HipName);
						int PlayerIndex = MV1SearchFrame(player->GetImg(), HipName);

						player->SetAttackCollision(player->GetPos(), 0.0f);
						enemy->SetKnockBack((Knockback));
						enemy->SetMove((Knockback));
						enemy->SetMoveType(enemy->hit_stop);
						enemy->SetAnimType(enemy->Hit);
						
						if (enemyIndex >= 0 && PlayerIndex >= 0)
						{
							VECTOR EffctPos;
							VECTOR EPos = MV1GetFramePosition(enemy->GetImg(), enemyIndex);
							VECTOR PPos = MV1GetFramePosition(player->GetImg(), PlayerIndex);
							EffctPos = VAdd(PPos, VScale(VSub(EPos, PPos), 0.25));


							VECTOR EffectMove = VSub(EffctPos, player->GetPos());
							EffectMove = VNorm(EffectMove);
							EffectM::Add(*ImpactE, EffctPos, VGet(0, 0, 0), EffectMove);

						}
					}



					StartJoypadVibration(DX_INPUT_PAD1, 500, 400, -1);
				}
				else///無敵中攻撃判定
				{
					StartJoypadVibration(DX_INPUT_PAD1, 1000, 100, 1);
				}


			}


			else if (player->isHitCaracters(*player, *enemy) && player->GetAnimType() != player->Hit && (enemy->GetAnimType() == enemy->ArmSwing || enemy->GetAnimType() == enemy->Run) && player->GetAnimType() != player->Roll&&player->GetAnimType() != player->Kick)
			{
				bool isHit = true;

                if (enemy->GetAnimType() == enemy->ArmSwing)
				{
					Capsule ArmCapule = enemy->SearchCapsule(LeftHand);
					std::vector<Capsule> PlayerCapsule = player->GetCapsuleCollision();
					isHit = false;
					for (int i = 0; i < PlayerCapsule.size(); i++)
					{
						
						isHit= ArmCapule.Survey(ArmCapule, PlayerCapsule[i]);

						if (isHit)
						{
							break;
						}
					}

				}
				if(isHit)
				{
					VECTOR Move = VGet(0, 0, -100);
					Move = VTransformSR(Move, MGetRotY(enemy->GetDir().y));
					Move.y = 10.0f;
					Move = VScale(VNorm(Move), enemy->GetAttackCollision().GetSphereSize());
					player->SetMove(Move);
					player->SetAnimType(player->Hit);
					player->SetIsHit(true);
					player->SubHp(enemy->GetAttack());
					player->SetLastDamageTime();
					/////必殺キャンセル
					player->SetInSpecialMove(false);
					AttackSound->Play();

					/*///playerの正面に移動
					VECTOR FRONT = VGet(0, 100, -1000);
					FRONT =VTransformSR(FRONT, MGetRotY(player->GetDir().y));
					camera->ResetOffset(FRONT, player->GetPos());
					camera->CalculateAngle(player->GetPos());
					camera->CalculateTargetAngle(player->GetPos());*/

					/*					camera->ResetOffset(DefaultCamera, VAdd( player->GetPos(),PlayerTopPos));*/
					StartJoypadVibration(DX_INPUT_PAD1, 1000, 400, -1);
				}
			}

			else if (VSize(VSub(player->GetPos(), enemy->GetPos())) <= 2000 && (enemy->GetAnimType() != enemy->Hit || player->GetAnimType() != player->Hit))
			{
				VECTOR P = player->PushBackCapsuleCollison(*player, *enemy);

				player->SetMove(VAdd(player->GetMove(), P));
				player->UpdateCapsuleCollision(P);


			}


			////カメラ系///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


					//必殺技時のカメラの動き
			if (player->GetInSpecialMove())
			{
				player->SetInSpecialMove(SPMove->Update(deltaTime));

			}
			else if (InCounter)
			{
					
			}
			///通常時
			else if (!OnWall)
			{
				if (player->GetAnimType() == player->Roll)
				{
					float RollZoom = 500.0f;
					camera->StartZoom(RollZoom);
					const char* HipName = "mixamorig:Hips";
					VECTOR test = MV1GetPosition(player->GetImg());
					int HipIndex = MV1SearchFrame(player->GetImg(), HipName);
					if (HipIndex >= 0)
					{
						VECTOR SetPos = MV1GetFramePosition(player->GetImg(), HipIndex);

						camera->StartMove(VSub(VAdd(SetPos, camera->GetOffset()), camera->GetPos()));
						camera->Look(SetPos);
					}


				}
				else if (camera->GetisZoom())
				{
					camera->ZoomOut(1.0f);
					camera->Look(VAdd(player->GetPos(), PlayerTopPoint));

				}

				if (!isInput || player->GetAnimType() != player->Roll)
				{
					camera->StartMove(VScale(VSub(VAdd(VAdd(player->GetPos(), PlayerTopPoint), camera->GetOffset()), camera->GetPos()), 0.1f));

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
				VECTOR  Proj = VScale(Line, (VDot(Move, Line) / VDot(Line, Line)));
				VECTOR PassingPoint = VAdd(player->GetPos(), Move);
				VECTOR SetPoint = VNorm(PassingPoint);
				SetPoint = VScale(SetPoint, FieldSize);
				float Rate = VSize(SetPoint) / VSize(VGet(camera->GetPos().x, 0, camera->GetPos().z));///Yの高さは比率でとる
				SetPoint.y = 100;
				SetPoint.y=Rate;
				VECTOR Offset = VSub(SetPoint, player->GetPos());
				camera->ResetOffset(Offset, VAdd(player->GetPos(), PlayerTopPoint));
				/*	camera->Look(VAdd(player->GetPos(),PlayerTopPoint));*/

					/////ちかちかする理由
				if (VSize(DefaultCamera) < VSize(camera->GetOffset()))
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

				}/*
			*//*	camera->Look(VAdd(player->GetPos(),PlayerTopPoint));*/
			}
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			Sphere_Collision PlayerCollision = player->GetCollision();
			PlayerCollision.SetPos(VAdd(PlayerCollision.GetPos(), player->GetMove()));
			//////更新///////////////////////////////////////////////////////////////////////////////////////////////////////	
			if (!player->GetInSpecialMove())
			{
				BGM->Loop();
				if (!InHitStop)
				{
					player->Update(deltaTime);
					if (player->GetAnimType() != player->Hit && !InCounter)
					{
						enemy->Update(deltaTime);
					}
				}
			}
			else
			{
				BGM->Stop();
			}
			//////カメラの押し戻し
			camera->Update(VAdd(player->GetPos(), PlayerTopPoint));
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// HPバーの更新//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	

			playerHP->Update();
			playerSP->Update(player->GetSpGauge());
			enemyHpBar->Update(*camera);
			/////描画//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	

			MV1SetPosition(player->GetImg(), player->GetPos());
			MV1SetPosition(player->GetNextImg(), player->GetPos());

			
			MV1SetPosition(enemy->GetImg(), enemy->GetPos());
			MV1SetPosition(enemy->GetNextImg(), enemy->GetPos());

			if (!player->GetInSpecialMove())
			{ 
				if (!InCounter)
				{
					ui->DrawMessage();
					playerHP->Draw();
					playerSP->Draw();
					if (enemyHpBar->CheakIsDraw(*player, *camera))
					{
						enemyHpBar->Draw();

					}
				}
				

				
			}
			////エネミーの点滅
			if (enemy->GetMoveType() == enemy->hit_stop && player->GetInSpecialMove() && fabs(fmod(player->GetLiveTime(), 0.1f)) < 0.01f && player->GetAttackCollision().GetSphereSize() > 0)
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
				//enemy->SetisDraw(true);
			}

			if (VSize(enemy->GetPos()) > FieldSize)
			{
				enemy->SetPos(VScale(VNorm(enemy->GetPos()), FieldSize));
			}
			//////勝ち判定
			if (player->GetHp() <= 0 && player->GetAnimType() != player->Hit)
			{
				GameMode = Lose;
				player->SetAnimSpeed(10);
				MATRIX RotY = MGetRotY(enemy->GetDir().y);
				VECTOR Offset = VTransformSR(LoseCamera, RotY);
				camera->ResetOffset(Offset, player->GetPos());
				player->SetAnimType(player->Down);
				BGM->Stop();
				EffectM::Clear();
			}
			if (enemy->GetHp() <= 0 && !player->GetInSpecialMove())
			{
				GameMode = Win;
				MATRIX RotY = MGetRotY(enemy->GetDir().y);
				VECTOR Offset = VTransformSR(WinCameraFast, RotY);
				enemy->SetisDraw(true);
				enemy->SetAnimType(enemy->Down);
				camera->ResetOffset(Offset, enemy->GetPos());
				enemy->SetStartLiveTime(enemy->GetLiveTime());
				BGM->Stop();
				EffectM::Clear();


			}
			if(!player->GetInSpecialMove())
			{
				if (!InCounter)
				{
					ui->DrawMessage();
					Explanation->DrawMessage();
					Arrow->Make(enemy->GetPos(), player->GetPos());
					Arrow->Draw();
				}

			}
		/*	shadow->Draw();*/
		/*	shadow->StartUse();*/
			MV1DrawModel(BackModel);
			MV1DrawModel(TileModel);
			EffectM::Update(deltaTime);
			EffectM::Draw();
			if (player->GetisDraw())
			{
				player->Draw();
			}
		
			if (player->GetAnimType() != player->Hit)
			{
				enemy->Draw();
			}
		/*	shadow->EndUse();*/
			// モデルの描画
		   // モデルの描画
				  // モデルの描画
		   /*player->DrawCapsuleCollision();
		   enemy->DrawCapsuleCollision();*/
			DrawFormatString(1000,200,GetColor(255,0,0),"%f",1/Fps->GetDeltaTime());
			
		}

		break;

		case  Win:

			if (win->Update())
			{
				GameMode = Start;
			}

			break;

		case Lose:

			if (lose->Update())
			{
				GameMode = Start;
			}

			break;

		case Start:

			if (start->Update())
			{
				GameMode = Spawn;
				enemyHpBar->ResetOwner(enemy, VGet(-400, 900, 0));
				playerHP->ResetOwner(player);
				
			}
			

			break;

		case Spawn:

			if (spawn->Update())
			{
				GameMode = Game;
				enemyHpBar->ResetOwner(enemy, VGet(-400, 900, 0));
				playerHP->ResetOwner(player);

			}

			break;

		}


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////	
		Fade->Draw();



		ScreenFlip();// 裏画面の内容を表画面に反映 
		///////fps調整///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		TotalTime += deltaTime;
		Fps->End();
	}
	MV1DeleteModel(BackModel);
	MV1DeleteModel(TileModel);
	delete shadow;
	delete enemyHpBar;
	delete playerHP;
	delete(player);
	delete(enemy);
	delete(camera);
	delete Fps;
	delete(Collision_Measurement);
	delete(ImpactE);
	delete(RingE);
	delete(HitSound);
	delete(SpSound);
	delete(BGM);
	delete(Fade);
	delete(start);
	delete(win);
	delete(lose);
	delete(spawn);


	Effkseer_End();

	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}

