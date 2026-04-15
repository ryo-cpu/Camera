#include "Counter.h"
const float CounterTime = 300.0f;
const float CounterHitStopTime=30.0f;
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
			}
		
	}
	////攻撃状態
	else if(!IsHit)
	{
		///攻撃生成と移動力決定

		

	}
	///ヒットストップ
	else
	{

		return false;

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
