#include "Player.h"
#include<DxLib.h>
#include<cmath>



Player::Player()
{
	SetCollision(VAdd(Pos, VGet(0, 100, 0)), 40.0f);
	MaxHp = 40;
	Hp = MaxHp;
	Attack = 10;
	InSpecialMove = false;
	IsHit = false;
	InRolling = false;
	IsActiveInput = true;
	GRund = VGet(0, 0, 0);
	Move = VGet(0, 0, 0);
	InputState = new XINPUT_STATE;
	AnimSpeed = PlayerAnimSpeed;
}

Player::Player(int img):Character(img)
{
	SetCollision(VAdd(Pos, VGet(0, 100, 0)), 40.0f);
	MaxHp = 40;
	Hp = MaxHp;
	Attack = 10;
	InSpecialMove = false;
	IsHit = false;
	InRolling = false;
	IsActiveInput = true;
	GRund = VGet(0, 0, 0);
	Move = VGet(0, 0, 0);
	InputState = new XINPUT_STATE;
	AnimSpeed = PlayerAnimSpeed;

}

Player::~Player()
{
	delete InputState;
}

bool Player::Input(Camera& camera)
{
    bool isInput = false;
    isTurn = false;
	VECTOR move=VGet(0,0,0);
	float targetAngle =0.0f; // ラジアン角
	
	int* XBuf=new int;
	int* YBuf=new int;
	SetJoypadDeadZone(DX_INPUT_PAD1, 0.35f);
	if (GetJoypadNum() == 0)
	{
		SetMove(move);
		return false;////PADが繋がってないとダメだ
	}
	if (GetJoypadXInputState(DX_INPUT_PAD1,InputState))
	{
		SetMove(move);
		return false;
	}
	if (!InRolling&&AnimType!=Kick)
	{
		if (InputState->ThumbRX >= 100 || InputState->ThumbRX <= -100)
		{

			float Rot= (InputState->ThumbRX) * 0.000001f;
			Turn(VGet(0, Rot, 0));
			VECTOR F = VScale(VGet(0, 0, 1),VSize(VGet(DefaultCamera.x,0,DefaultCamera.z)));
			camera.AddTAngle(VGet(0, Rot, 0));
			VECTOR RotP = camera.GetTargetAngle();
			MATRIX RotX = MGetRotX(RotP.x); 
			MATRIX RotY = MGetRotY(RotP.y);///Zは回転しない
			MATRIX RotAll = MMult(RotX,RotY);
			camera.ResetOffset(VTransformSR(F, RotAll),VAdd(Pos,PlayerTopPoint));
		/*	camera.Look(VAdd(Pos,PlayerTopPoint));*/

		}
		if (InputState->ThumbRY >= 100 || InputState->ThumbRY <= -100)
		{
		
			float Rot = (InputState->ThumbRY) * 0.000001f;
			VECTOR F = VScale(VGet(0, 0, 1), VSize(DefaultCamera));
			VECTOR RotP = camera.GetTargetAngle();
			
			if (RotP.x+ Rot>=-0.7&&RotP.x+Rot<=-0.2)
			{
			  camera.AddTAngle(VGet(Rot, 0, 0));
			}
			

			
			MATRIX RotX = MGetRotX(camera.GetTargetAngle().x);
			MATRIX RotY = MGetRotY(camera.GetTargetAngle().y);///Zは回転しない
			MATRIX RotAll = MMult(RotX, RotY);
			camera.ResetOffset(VTransformSR(F, RotAll),VAdd(Pos, PlayerTopPoint));
			
			/*camera.Look(VAdd(Pos,PlayerTopPoint));*/

		}
		VECTOR MoveDir = VGet(-(InputState->ThumbLX), 0, -(InputState->ThumbLY));
		MoveDir =VTransformSR(MoveDir, MGetRotY(GetDir().y));
		if (VSize(MoveDir) >= 100)
		{
			isInput = true;
			if (!IsAnim || AnimType == Stop)
			{
				SetAnimType(Run);
			}
			move = VScale(MoveDir, 0.01f);
		}

		if ((InputState->Buttons[XINPUT_BUTTON_RIGHT_SHOULDER]) != 0)
		{
			if (VSize(move) == 0)
			{
				move =VTransformSR(VGet(0, 0, -1), MGetRotY(GetDir().y));
			}
			else
			{
				move = VNorm(move);
			}
			StartLiveTime = LiveTime;
			InRolling = true;
			SetAnimType(Roll);
			Collision = {};
		}
		if (isInput && VSize(move) != 0)
		{
			move = VNorm(move);         // 正規化（方向だけを抽出）
			move = VScale(move, 10);     // スピードを乗算
			float targetAngle = atan2f(-move.x, -move.z); // ラジアン角
			MV1SetRotationXYZ(Img, VGet(0, targetAngle, 0));
			MV1SetRotationXYZ(NextImg, VGet(0, targetAngle, 0));


		}
		else
		{
			MV1SetRotationXYZ(Img, VGet(0, GetDir().y, 0));
			MV1SetRotationXYZ(NextImg, VGet(0, GetDir().y, 0));


		}
		if ((InputState->Buttons[XINPUT_BUTTON_B]) != 0)
		{
		
			VECTOR Front; 
			if (VSize(move) == 0)
			{
				move = VGet(0, 0, -1);
			    Front=VTransformSR(move, MGetRotY(Dir.y));
			}
			else
			{
			    move = VScale(VNorm(move), 1);
				Front = move;
			}
			
			move =VScale(Front,AnimSpeed);
			SetAnimSpeed(50.0f);
			SetAnimType(Kick);
		}
		if (InputState->Buttons[XINPUT_BUTTON_X] != 0&&SpGauge>=MaxSpGauge)
		{
			InSpecialMove = true;
			StartLiveTime = LiveTime;
			SpGauge = 0;

		}
		if (VSize(move) == 0)
		{
			SetMove(VScale(Move,0.1f));
			isInput = false;
		}
		else
		{
			VECTOR Add = VAdd(Move, move);
			if (VSize(Add) < VSize(Move))
			{
				isTurn = true;
			}
			SetMove(Add);
		}
		if (VSize(Move) >= MaxSpeed)
		{
			Move = VScale(VNorm(Move), MaxSpeed);
		}
	}
	delete XBuf;
	delete YBuf;

	

	
    return isInput;
}

void Player::Update(float deltaTime)
{
	
	
	//空中にいるときに重力作成
	if (GRund.y < Pos.y)
	{
		Pos = VAdd(Pos, G);

		Pos.y = Pos.y < 0 ? 0 : Pos.y;
	 }
	///ケリの時の自動移動と攻撃の作成
	if (AnimType == Kick)
	{
		if (NowAnimTime >= 30.0f && NowAnimTime <= AnimTotalTime)
		{
			VECTOR AttackPos = VGet(0, 100, -200);
			AttackPos =VTransformSR(AttackPos, MGetRotY(GetDir().y));
			SetAttackCollision(VAdd(Pos, AttackPos), 30.f);
		}
		//攻撃の時間から外れた時攻撃判定を削除
		else
		{
			AttackCollision = {};
		}
		//アニメーション終了時デフォルトアニメーションに戻す
		if (!IsAnim)
		{
			SetAnimType(Stop);
			SetAnimSpeed(PlayerAnimSpeed);
		}
	}
	else
	{
		AttackCollision = {};
		

	}
	if (Collision.GetSphereSize() == 0)
	{
		DrawSphere3D(AttackCollision.GetPos(),AttackCollision.GetSphereSize(), 16, GetColor(200, 255, 255), GetColor(0, 0, 0), TRUE);

	}
	if (AnimType == Hit &&NowAnimTime >= AnimTotalTime)
	{
		SetAnimType(Stop);
	}
	//ローリング時の自動移動更新
	if (InRolling)
	{
		SetAnimSpeed(50.0);
		InRolling = Rolling();
		//ローリング停止時
		if (!InRolling)
		{
			const char* HipName = "mixamorig:Hips";
			VECTOR test = MV1GetPosition(Img);
			int hipsIndex = MV1SearchFrame(Img, HipName);
			if (hipsIndex >= 0)
			{
				VECTOR RollingPos = MV1GetFramePosition(Img, hipsIndex);
				RollingPos.y = 0;
				SetPos(RollingPos);
			}
			SetAnimSpeed(PlayerAnimSpeed);
			SetAnimType(Stop);
			
		}
	}
	//ローリング以外の位置更新
	else
	{
		
		MoveCollision(Move);
	    SetPos(VAdd(Pos, Move));
		
	}
	
	///Spgaugeの自動増加
	if (LiveTime - LastDamageTime >= 5.0f&&GetHp()<MaxHp && fabs(fmod(LiveTime - LastDamageTime, 0.1f)) < 0.01f)
	{
	
		AddSpGauge(1);
	}
	Effect* PlayerEffect = nullptr;
	if (SpGauge >= MaxSpGauge)
	{
		
		PlayerEffect = EffectM::Search(PlayerAuraID);
		/////ないとヌルポが帰ります
		if (PlayerEffect == nullptr)
		{
			EffectImg* AuraE = new EffectImg("data/Lightning.efkefc", 10);
			EffectM::Add(*AuraE, Pos, VGet(0, 20, 0), VGet(0, 0, 0), PlayerAuraID);
		}
		else
		{
			PlayerEffect->SetPos(Pos);
		}
		////エフェクトと切り離す
		PlayerEffect = nullptr;
		
	}
	else
	{
		PlayerEffect = EffectM::Search(PlayerAuraID);
		/////ないとヌルポが帰ります
		if (PlayerEffect != nullptr)
		{
			PlayerEffect->Stop();
			PlayerEffect = nullptr;
		}

	}
	if (AnimType == Hit)
	{
		Move = VScale(VNorm(Move), AnimSpeed);
	}

	
	LiveTime+=deltaTime;
}



void Player::SetGRund(VECTOR gRund)
{
	GRund = gRund;
}

bool Player::GetIsHit()
{
	return IsHit;
}

void Player::SetIsHit(bool ishit)
{
	IsHit = ishit;
}

bool Player::GetInSpecialMove()
{
	return InSpecialMove;
}

void Player::SetInSpecialMove(bool inSpecialMove)
{
	InSpecialMove = inSpecialMove;
	
}

void Player::SetLastDamageTime()
{
	LastDamageTime = GetLiveTime();
}

float Player::GetLastDamageTime()
{
	return LastDamageTime;
}

bool Player::Rolling()
{
	
	if (!IsAnim)
	{
		float move = 300;
		Move = VNorm(Move);
		SetPos(VAdd(Pos, VScale(Move,move)));	
		SetCollision(VAdd(Pos, VGet(0, 100, 0)), 40.0f);

	
	}
	return IsAnim;
}

void Player::AddSpGauge(int add)
{
	///Maxを超えたときのみ振動を鳴らしたいため元の数値がMaxいかか確認
	if (SpGauge < MaxSpGauge)
	{
		SpGauge += add;
		///値がMaxを超えたとき鳴らしとならす
		if (SpGauge >= MaxSpGauge)
		{
			SpGauge = MaxSpGauge;
			StartJoypadVibration(DX_INPUT_PAD1, 1000, 400, 1);

		}
	}
	

}

int Player::GetSpGauge()
{
	return SpGauge;
}

bool Player::GetTurn()
{
	return isTurn;
}

XINPUT_STATE* Player::GetInputState()
{
	return InputState;
}

void Player::Initial()
{
	SetCollision(VAdd(Pos, VGet(0, 100, 0)), 40.0f);
	MaxHp = 40;
	Hp = MaxHp;
	Attack = 10;
	InSpecialMove = false;
	IsHit = false;
	InRolling = false;
	IsActiveInput = true;
	GRund = VGet(0, 0, 0);
	Move = VGet(0, 0, 0);
	SpGauge = 0;
}



void Player::SpecialMove(float deltaTime)
{ 
	
	
}
