#include "Counter.h"
const float CounterTime = 300.0f;
const float CounterHitStopTime=30.0f;
const float HitWaitTime = 10.0f;
Counter::Counter(Camera& Camera, Player& Player, Character& Enemy) : camera(Camera), player(Player), enemy(Enemy)
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
		
		
			////攻撃の再入力まち
			if (player.GetInputState()->Buttons[XINPUT_BUTTON_START] != 0)
			{
				InWait = false;
				InAttackTime = player.GetLiveTime();
			}
		
	}
	////攻撃状態 ///抜ける時は外部からSetHiｔが　呼ばれる
	else if(!IsHit)
	{
		///攻撃生成と移動力決定
		VECTOR Distance = VSub(player.GetPos(), enemy.GetPos());
		Distance.y = 0;
		//毎回同じ時間で終わりたいので攻撃開始から経過を引き　攻撃にかかる秒数から引き　その値で割ることで　大体同じ秒数で終わるはず
		VECTOR Move = VScale(Distance, (1 / (HitWaitTime - (player.GetLiveTime() - InAttackTime))));
		///攻撃の判定を作成
		VECTOR AttackPos = VGet(0, 0, 0);
		AttackPos = VTransformSR(AttackPos, MGetRotY(player.GetDir().y));
		player.SetAttackCollision(VAdd(player.GetPos(), AttackPos), 200.f);
		
	}
	///ヒットストップ
	else
	{
		if (ElapsedTime > CounterHitStopTime)
		{
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
		player.SetStartLiveTime(player.GetLiveTime());

	}
}
