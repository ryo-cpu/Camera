#include "Counter.h"
const float CounterTime = 10.0f;
const float CounterHitStopTime=1.5f;
const float AttackTime = 10.0f;
const VECTOR InitCounter = VGet(0, 0, -1000);
Counter::Counter(Camera& Camera, Player& Player, Enemy& Enemy) : camera(Camera), player(Player), enemy(Enemy)
{
	InWait = true;
	IsHit = false;
}


Counter::~Counter()
{
}

bool Counter::Update(float DeltaTime)
{
	float  ElapsedTime = player.GetLiveTime() - player.GetStartLiveTime();
	///攻撃が再度押されないまま時間が過ぎると終わる
	if (ElapsedTime >= CounterTime&&InWait)
	{
		return false;
	}
	///待機状態
	else if(InWait)
	{

		    camera.EndMove();
		  			////攻撃の再入力まち
			if (player.GetInputState()->Buttons[XINPUT_BUTTON_B] != 0)
			{
				InWait = false;
			}
		
	}
	////攻撃状態 ///抜ける時は外部からSetHiｔが　呼ばれる
	else if(!IsHit)
	{
		///攻撃生成と移動力決定
	
	
		//毎回同じ時間で終わりたいので攻撃開始から経過を引き　攻撃にかかる秒数から引き　その値で割ることで　大体同じ秒数で終わるはず
		VECTOR Move = VScale(Distance,-1/AttackTime );
		///攻撃の判定を作成
		VECTOR AttackPos = VGet(0, 0, 0);
		AttackPos = VTransformSR(AttackPos, MGetRotY(player.GetDir().y));
		player.SetAttackCollision(VAdd(player.GetPos(), AttackPos), 10.f);
		player.SetMove(Move);
		camera.StartMove(VScale(Move, 0.9f));
		
	}
	///ヒットストップ
	else
	{
		if (ElapsedTime > CounterHitStopTime)
		{
			camera.ResetOffset(VTransformSR(DefaultCamera, MGetRotY(player.GetDir().y)), player.GetPos());
			camera.CalculateAngle(player.GetPos());
			camera.CalculateTargetAngle(player.GetPos());
			enemy.SetisDraw(true);
			InWait = true;
			IsHit = false;
			return false;
		}
		

	}
	
	return true;
}

void Counter::SetHit(bool isHit)
{
	////ヒット時の処理
	if (isHit)
	{
		IsHit = true;
		player.SetMove(VGet(0.0f, 0.0f, 0.0f));
		player.SetStartLiveTime(player.GetLiveTime());
		
		camera.EndMove();

		
	}

}

bool Counter::Start()
{
	///敵の正面にプレイヤーを移動
	const char* HipName = "mixamorig:Hips";
	int enemyIndex = MV1SearchFrame(enemy.GetImg(), HipName);
	VECTOR EPos = MV1GetFramePosition(enemy.GetImg(), enemyIndex);
	EPos.y = 0;
	/// ////攻撃初期位置を回転せれる
	VECTOR Init = VTransformSR(InitCounter, MGetRotY(enemy.GetDir().y));
	player.SetMove(VGet(0.0f, 0.0f, 0.0f));
	player.SetPos(VAdd(Init, EPos));
	///プレイヤーの向きを敵に向ける
	VECTOR Front = VNorm(VSub(player.GetPos(), enemy.GetPos()));
	float Angle = atan2f(Front.x, Front.z);
	player.SetDir(VGet(0, Angle, 0));
	MV1SetRotationXYZ(player.GetImg(), player.GetDir());
	MV1SetRotationXYZ(player.GetNextImg(), player.GetDir());

	/// カメラを設定
	camera.ResetOffset(VTransformSR(CounterCamera, MGetRotY(player.GetDir().y)), player.GetPos());
	camera.CalculateAngle(player.GetPos());
	camera.CalculateTargetAngle(player.GetPos());

	///無敵の解除と移動距離
	enemy.SetIsInvincible(false);
	Distance = VSub(player.GetPos(), EPos);


	return true;
}
