#include "EffectM.h"




	

void EffectM::Update(float detalTime)
{
	for (int i = 0; i < MaxEffect; i++)
	{
		if (Pool[i] != nullptr)
		{
			///後ですべてにする
			Pool[i]->Update(detalTime);
			if (IsEffekseer3DEffectPlaying(Pool[i]->GetPlayHandle())!=0)
			{
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
			return ;

		}
	}
	/*if (Pool[0] != nullptr)
	{
		delete Pool[0];
		Pool[0] = nullptr;

	}*/
}

void EffectM::Add(EffectImg origin, VECTOR StartPos)
{
	///追加機能は後で
	for (int i = 0; i < MaxEffect; i++)
	{
		if (Pool[i] == nullptr)
		{
			Pool[i] = new Effect(StartPos, origin);
			return;

		}
	}
	//今は空きがないと再生しない
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
