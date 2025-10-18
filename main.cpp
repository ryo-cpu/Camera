
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
	MV1SetScale(TileModel, VGet(5, 1, 5));




	///////カメラの初期化
	SetCameraPositionAndTarget_UpVecY(VGet(0, 0, 0), player->GetPos());
	////スタート時のカメラ
	Camera* camera = new Camera(100.0f, 10000.0f, VAdd(enemy->GetPos(),StartCamera), enemy->GetPos());
	camera->CalculateAngle(PlayerPos);
	camera->CalculateTargetAngle(player->GetPos());
	SetLightAmbColor(GetColorF(0.3f, 0.3f, 0.3f, 0.3f));
	ChangeLightTypeDir(VGet(0, -1, 0));

	

	int SpotL= CreateSpotLightHandle(VGet(0.0f, 1000.0f, 0.0f), VGet(0.0f, -1.0f, 0.0f), DX_PI_F / 2.0f, DX_PI_F / 4.0f, 2000.0f,0.01f,  0.002f,		0.0f);
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
	///Effet
	EffectImg *ImpactE=new EffectImg("data/Shock.efkefc",100);
	
	
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
				player->SetMove(VAdd(player->GetMove(), G));

			}
			else if (!player->GetInSpecialMove())
			{
				isInput = player->Input(*camera);

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
			if (VSize(VAdd(player->GetPos(),player->GetMove())) > FieldSize)
			{
				VECTOR PassingPoint = VAdd(player->GetPos(), player->GetMove());
				VECTOR SetPoint = VNorm(PassingPoint);
				SetPoint = VScale(SetPoint, FieldSize);
				player->SetMove(VSub(SetPoint,player->GetPos()));
			}
			if (player->GetPos().y <= BaseY)
			{
				isJunp = false;
				player->SetPos(VGet(player->GetPos().x, BaseY, player->GetPos().z));
				JumpPower = VGet(0, 30, 0);
				player->SetIsHit(false);
			}


			////カメラ系///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			
			
					//必殺技時のカメラの動き
			if (player->GetInSpecialMove())
			{
				player->SetInSpecialMove(SPMove->Update(deltaTime));

			}
			///通常時
			else if(!OnWall)
			{
				if (!isInput)
				{
					
				
					camera->StartMove(VScale(VSub(VAdd(player->GetPos(), camera->GetOffset()), camera->GetPos()), 0.1f));
					
					if (VSize(player->GetMove()) <= 0)
					{
						BasePoint = player->GetPos();

					}
				}
				else if(VSize(VSub(player->GetPos(), BasePoint)) >= 500)
				{
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
				player->Update(deltaTime);
				/*enemy->Update(deltaTime);*/
			}
			////衝突////////////////////////////////////////////////////////////////////////////////////////////////////
			if (Collision_Measurement->Collison(player->GetCollison(), enemy->GetCollison()))
			{
				VECTOR Distance = VSub(player->GetPos(), enemy->GetPos());

				Sphere_Collision PlayerCollison = player->GetCollison();
				Sphere_Collision enemyCollison = enemy->GetCollison();

				VECTOR TakeDistance = VScale(VNorm(Distance), (enemyCollison.GetSphereSize() + PlayerCollison.GetSphereSize() + 1));

				TakeDistance = VSub(TakeDistance, Distance);
				player->SetMove(VAdd(player->GetMove(), TakeDistance));
				player->SetPos(VAdd(player->GetPos(), player->GetMove()));
			}


			///enemy攻撃

			if (Collision_Measurement->Collison(player->GetCollison(), enemy->GetAttackCollison()) && player->GetAnimType() != player->Hit)
			{
				VECTOR Move = VGet(0, 1, -1);
				Move = VTransformSR(Move, MGetRotY(enemy->GetDir().y));
				Move = VScale(Move, enemy->GetAttackCollison().GetSphereSize());
				player->SetMove(Move);
				player->SetAnimType(player->Hit);
				player->SetIsHit(true);
				player->SubHp(enemy->GetAttack());
				player->SetLastDamageTime();
				/////必殺キャンセル
				player->SetInSpecialMove(false);
				/*camera->ResetOffset(DefaultCamera, player->GetPos());*/
			}


			////player攻撃
			if (Collision_Measurement->Collison(player->GetAttackCollison(), enemy->GetCollison()) && enemy->GetMoveType() != enemy->hit_stop)
			{

				VECTOR Knockback = VScale(VNorm(VSub(enemy->GetPos(), player->GetPos())), player->GetAttackCollison().GetSphereSize() * deltaTime);
				if (player->GetInSpecialMove())
				{
					Knockback = VScale(VNorm(VSub(enemy->GetPos(), player->GetPos())), player->GetAttackCollison().GetSphereSize() * deltaTime * 10);
				}
				Knockback.y = 0;

				enemy->SetMove((Knockback));
				enemy->SetMoveType(enemy->hit_stop);
				enemy->SetAnimType(enemy->Hit);
				enemy->SubHp(player->GetAttack());

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
			if (enemy->GetMoveType() == enemy->hit_stop && player->GetInSpecialMove() && fabs(fmod(player->GetLiveTime(), 0.1f)) < 0.01f)
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
			if (player->GetHp() <= 0)
			{
				GameMode = Lose;
				MATRIX RotY = MGetRotY(enemy->GetDir().y);
				VECTOR Offset = VTransformSR(LoseCamera, RotY);
				camera->ResetOffset(Offset, player->GetPos());
				player->SetAnimType(player->Down);
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

			}
			MV1DrawModel(BackModel);
			MV1DrawModel(TileModel);
			player->Draw();
			enemy->Draw();              // モデルの描画
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
				camera->RotaionAxis(Axis, RotY);
				camera->Look(Axis);
				enemy->AnimUpdate(deltaTime);
				if (CheckHitKey(KEY_INPUT_W))
				{
			     
					EffectM::Add(*ImpactE);
				}
				if (!enemy->GetIsAnim())
				{
					enemy->SetNowAnimTime(0.0f);
				}
				if (CheckHitKey(KEY_INPUT_SPACE)&&GetJoypadNum() != 0)
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
				DrawString(600, 550, "NEXT SPECE", GetColor(244, 229, 17));


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

			if (CheckHitKey(KEY_INPUT_SPACE))
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
				MATRIX RotY = MGetRotY(enemy->GetDir().y);
				VECTOR Offset = VTransformSR(WinCameraFast, RotY);
				camera->ResetOffset(Offset, enemy->GetPos());
				enemy->SetPos(VGet(0.0f, 0.0f, -600.0f));

				if (!enemy->GetIsAnim())
				{
					SetFontSize(128);
					DrawString(600, 350, "YOU WIN", GetColor(244, 229, 17));
					SetFontSize(64);
					DrawString(600, 550, "NEXT SPECE", GetColor(244, 229, 17));

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
				camera->ResetOffset(StartCamera, enemy->GetPos());
				enemy->SetAnimType(enemy->Dance);
				InModeCheng = false;
			}
			break;
		case Lose:
			MV1DrawModel(BackModel);
			if (CheckHitKey(KEY_INPUT_SPACE))
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
				DrawString(600, 550, "NEXT SPECE", GetColor(244, 229, 17));
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

