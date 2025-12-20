#include "Effect.h"



Effect::Effect(VECTOR StartPos, const EffectImg &Img)
{
	Move = VGet(0, 0, 0);
	Rot = VGet(0, 0, 0);
	Pos = StartPos;
	PlayHandle = PlayEffekseer3DEffect(Img.GetImg());
	Id = 0;
}

Effect::Effect(VECTOR StartPos, const EffectImg &Img, VECTOR StartRot)
{
	Move = VGet(0, 0, 0);
	Rot = StartRot;
	Pos = StartPos;
	PlayHandle = PlayEffekseer3DEffect(Img.GetImg());
	Id = 0;


}

Effect::Effect(VECTOR StartPos, const EffectImg &Img, VECTOR StartRot, VECTOR move)
{
	Move = move;
	Rot = StartRot;
	Pos = StartPos;
	PlayHandle = PlayEffekseer3DEffect(Img.GetImg());
	Id = 0;

}

Effect::Effect(VECTOR StartPos, const EffectImg &Img, VECTOR StartRot, VECTOR move, int id)
{
	Move = move;
	Rot = StartRot;
	Pos = StartPos;
	PlayHandle = PlayEffekseer3DEffect(Img.GetImg());
	
	Id = id;
}



void Effect::Update(float deltaTime)
{
	if (PlayHandle >= 0) {
		
		Pos = VAdd(Pos, Move);
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

void Effect::SetMove(VECTOR move)
{
	Move = move;
}

void Effect::SetRot(VECTOR rot)
{
	Rot = rot;
}

void Effect::Stop()
{
	////止めたい
	StopEffekseer3DEffect(PlayHandle);
}

int Effect::GetId()
{
	return Id;
}


Effect* Effect::GetPtr()
{
	return this;
}
void Effect::SetPos(VECTOR pos)
{
	Pos = pos;
}

