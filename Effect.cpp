#include "Effect.h"

Effect::Effect(std::string Link)
{
	Model = LoadEffekseerEffect("Link", 1.0f);
}

void Effect::Play(VECTOR StratPos)
{
	Pos = StratPos;
	PlayHandle= PlayEffekseer3DEffect(Model);
}

void Effect::Update(float deltaTime)
{
	Pos = VAdd(Pos,VScale(Move,deltaTime));
	// 再生中のエフェクトを移動する。
	SetPosPlayingEffekseer3DEffect(PlayHandle, Pos.x, Pos.y, Pos.z);
	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer3D();
}

void Effect::Draw()
{
	DrawEffekseer3D();
}
