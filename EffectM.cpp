#include "EffectM.h"




Effect* EffectM::Pool[MaxEffect] = { nullptr };
int EffectM::Observer[MaxEffect] = { 0 };

void EffectM::Update(float detalTime)
{
	for (int i = 0; i < MaxEffect; i++)
	{
		if (Pool[i] != nullptr)
		{
			///後ですべてにする
			Pool[i]->Update(detalTime);
			int Test = IsEffekseer3DEffectPlaying(Pool[i]->GetPlayHandle());
			if (IsEffekseer3DEffectPlaying(Pool[i]->GetPlayHandle())!=0)
			{
				for (int j = 0; j < MaxEffect; j++)
				{
					if (Observer[j] == i+1)
					{
						Observer[j] = 0;
						///for分を抜けたい
						///オブザーバーを詰める
						
						break;
					}

				}
				for (int j = 1; j < MaxEffect; j++)
				{
					if (Observer[j - 1] == 0)
					{
						Observer[j - 1] = Observer[j];
						Observer[j] = 0;
					}

				}
			delete Pool[i];
			Pool[i] = nullptr;
			}
		}
	}
	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer3D();

}

void EffectM::Add(EffectImg origin)
{
	for (int i = 0; i < MaxEffect; i++)
	{
		if (Pool[i] == nullptr)
		{
			Pool[i] = new Effect(VGet(0, 0, 0), origin);
			for (int j = 0; j < MaxEffect; j++)
			{
				if (Observer[j] == 0)
				{
					Observer[j] = i+1;

					break;
				}

			}
			return ;
			

		}
	}
	///もっとも古いものと取り替える
	delete Pool[Observer[0] - 1];
	Pool[Observer[0] - 1] = nullptr;
	Pool[Observer[0]-1]= new Effect(VGet(0, 0, 0), origin);
	///最古の場所を最新に変える
	///いったん保持
	int TNP = Observer[0];
	Observer[0] = 0;
	///０にして詰める
	for (int j = 1; j < MaxEffect; j++)
	{
		if (Observer[j - 1] == 0)
		{
			Observer[j - 1] = Observer[j];
			Observer[j] = 0;
		}

	}
	Observer[MaxEffect - 1] = TNP;

}

void EffectM::Add(EffectImg origin, VECTOR StartPos)
{
	///追加機能は後で
	for (int i = 0; i < MaxEffect; i++)
	{
		if (Pool[i] == nullptr)
		{
			Pool[i] = new Effect(StartPos, origin);
			for (int j = 0; j < MaxEffect; j++)
			{
				if (Observer[j] == 0)
				{
					Observer[j] = i+1;
					exit;
				}

			}
			return;
			

		}
	}
	
	///もっとも古いものと取り替える
	delete Pool[Observer[0] - 1];
	Pool[Observer[0] - 1] = nullptr;
	Pool[Observer[0] - 1] = new Effect(VGet(0, 0, 0), origin);
	///最古の場所を最新に変える
	///いったん保持
	int TNP = Observer[0];
	Observer[0] = 0;
	///０にして詰める
	for (int j = 1; j < MaxEffect; j++)
	{
		if (Observer[j - 1] == 0)
		{
			Observer[j - 1] = Observer[j];
			Observer[j] = 0;
		}

	}
	Observer[MaxEffect - 1] = TNP;
}

void EffectM::Draw()
{
	DrawEffekseer3D();
}

EffectM::EffectM()
{
	for (int i = 0; i < MaxEffect; i++)
	{
		Pool[i] = nullptr;
	}
}
