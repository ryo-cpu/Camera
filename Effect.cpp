#include "Effect.h"



Effect::Effect(VECTOR StartPos, EffectImg Img)
{
	Move = VGet(0, 0, 0);
	Pos = StartPos;
	PlayHandle = PlayEffekseer3DEffect(Img.GetImg());
}

void Effect::Update(float deltaTime)
{
	if (PlayHandle >= 0) {
		
		Pos = VAdd(Pos, VScale(Move, deltaTime));
		// 再生中のエフェクトを移動する。
		SetPosPlayingEffekseer3DEffect(PlayHandle, Pos.x, Pos.y, Pos.z);
	
	}
	
}

int Effect::GetPlayHandle()
{
	if (PlayHandle >= 0) {

		return PlayHandle;
	}
	return -1;
}


