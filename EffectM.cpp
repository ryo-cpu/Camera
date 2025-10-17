#include "EffectM.h"




	

void EffectM::Update(float detalTime)
{
	if (Pool[0] != nullptr)
	{
		///後ですべてにする
		Pool[0]->Update(detalTime);
	}
}

void EffectM::Add(EffectImg origin)
{
	///追加機能は後で
	Pool[0] =new Effect(VGet(0, 0, 0),origin);
}

void EffectM::Add(EffectImg origin, VECTOR StartPos)
{
	///追加機能は後で
	Pool[0] = new Effect(StartPos, origin);

}

void EffectM::Draw()
{
	DrawEffekseer3D();
}

EffectM::EffectM()
{
	for (int i = 0; i < MaxEffect - 1; i++)
	{
		Pool[i] = nullptr;
	}
}
