#include "Sound.h"
/// <summary>
/// 減衰力
/// </summary>
const float Attenuation = 0.03f;
Sound::Sound(int SoundSource)
{
 Source = SoundSource;
 PlayingSound = Source;
 Volume = 255;
}

Sound::Sound(char* FileName)
{
 Source = LoadSoundMem(FileName);
 PlayingSound = Source;
 Volume = 255;

}

void Sound::Play()
{
	int Playing = CheckSoundMem(Source);
	///音の再生が重ならないように
	if (Playing==0)
	{
		PlaySoundMem(Source, DX_PLAYTYPE_BACK);
	}
	else if (Playing < 0)
	{
		///err
	}
}

void Sound::Play(VECTOR SoundPos, VECTOR ListenerPos, VECTOR ListenerXAxis, VECTOR ListenerYAxis, VECTOR ListenerZAxis)
{
	

	
	///変換用行列作成
	MATRIX Matrix= MGetAxis2(ListenerXAxis,ListenerYAxis,ListenerZAxis,ListenerPos);
	
	///変換
	 VECTOR Distance = VTransformSR(SoundPos, Matrix);
	 ////1メートルを定義する関数が動かないためこちらで無理やり近づけます
	 float Scale = 1 / 1000;
	 SoundPos = VScale(SoundPos, Scale);
	 ListenerPos = VScale(ListenerPos, Scale);
	 VECTOR frontPos = VAdd(ListenerPos, ListenerZAxis);
	 Set3DSoundListenerPosAndFrontPos_UpVecY(ListenerPos, frontPos);

	 // 音源の位置をそのまま渡す（リスナー基準で何もしなくても可）
	 Set3DPositionSoundMem(SoundPos, PlayingSound);

	///ボリューム調整
	float NowVolume = Volume - VSize(Distance) * Attenuation;
	
	///ゼロより未満にしない
	NowVolume = NowVolume < 0 ? 0 : NowVolume;
	ChangeVolumeSoundMem(static_cast<int>(NowVolume), PlayingSound);
	
	///再生
	if (!CheckSoundMem(PlayingSound))
	{
		int err = PlaySoundMem(PlayingSound, DX_PLAYTYPE_BACK, true);
	}
}

void Sound::Stop()
{
   int err = StopSoundMem(Source);
   if (err < 0)
   {
	   ///err
   }
}

void Sound::Loop()
{
	///音の再生が重ならないように
	if (!CheckSoundMem(Source))
	{
		PlaySoundMem(Source, DX_PLAYTYPE_BACK);
	}
	else
	{
		Play();
	}
}

void Sound::SetVolume(int volume)
{
	Volume = volume;
	ChangeVolumeSoundMem(Volume, Source);
}

void Sound::Play(VECTOR SoundPos, VECTOR ListenerPos)
{
	
	VECTOR Distance = VSub(SoundPos, ListenerPos);
	///ボリューム調整
	float NowVolume = Volume - VSize(Distance) * Attenuation;

	ChangeVolumeSoundMem(static_cast<int>(NowVolume), PlayingSound);
	Distance = VNorm(Distance);
	Set3DPositionSoundMem(Distance,PlayingSound);
	///再生
	if (!CheckSoundMem(PlayingSound))
	{
		int err = PlaySoundMem(PlayingSound, DX_PLAYTYPE_BACK, true);
	}
	

}

