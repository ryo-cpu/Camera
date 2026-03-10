#include "Counter.h"
const float CounterTime = 300.0f;
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
	///UŒ‚‚ªÄ“x‰Ÿ‚³‚ê‚È‚¢‚Ü‚ÜŠÔ‚ª‰ß‚¬‚é‚ÆI‚í‚é
	if (ElapsedTime >= CounterTime&&InWait)
	{
		return false;
	}
	else
	{
		if (InWait)
		{
			////UŒ‚‚ÌÄ“ü—Í‚Ü‚¿
			if (player.GetInputState()->Buttons[XINPUT_BUTTON_START] != 0)
			{
				InWait = false;
			}
			
		}
		else
		{
			///UŒ‚¶¬‚ÆˆÚ“®—ÍŒˆ’è

			if (IsHit)
			{
				return false;
			}

		}

	}
	
	return true;
}
