#include "Effect.h"



Effect::Effect(VECTOR StartPos, EffectImg Img)
{
	Move = VGet(0, 0, 0);
	Rot = VGet(0, 0, 0);
	Pos = StartPos;
	PlayHandle = PlayEffekseer3DEffect(Img.GetImg());
}

Effect::Effect(VECTOR StartPos, EffectImg Img, VECTOR StartRot)
{
	Move = VGet(0, 0, 0);
	Rot = StartRot;
	Pos = StartPos;
	PlayHandle = PlayEffekseer3DEffect(Img.GetImg());

}

Effect::Effect(VECTOR StartPos, EffectImg Img, VECTOR StartRot, VECTOR move)
{
}



void Effect::Update(float deltaTime)
{
	if (PlayHandle >= 0) {
		
		Pos = VAdd(Pos, VScale(Move, deltaTime));
		// 再生中のエフェクトを移動する。
		SetPosPlayingEffekseer3DEffect(PlayHandle, Pos.x, Pos.y, Pos.z);
		SetRotationPlayingEffekseer3DEffect(PlayHandle, Rot.x, Rot.y, Rot.z);
	
	}
	
}

int Effect::GetPlayHandle()
{
	if (PlayHandle >= 0) {

		return PlayHandle;
	}
	return -1;
}


