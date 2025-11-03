#pragma once
#include"DxLib.h"
class Sound
{
private:
	int Source;
	int Volume;
	int PlayingSound;
public:
	/// <summary>
	/// 音データの読み込み（メイン側でINTにする番）
	/// </summary>
	/// <param name="SoundSource">音データ(ステレオはできない）</param>
	Sound(int SoundSource);
	/// <summary>
	/// 音データ読み込み（ファイル名で渡す）
	/// </summary>
	/// <param name="FileName">音ファイル(ステレオはできない）</param>
	Sound(char* FileName);
	/// <summary>
	/// 何もいじっていない音を出す
	/// </summary>
	void Play();
	/// <summary>
	/// まっすぐ前を向いているときの音を出す
	/// </summary>
	/// <param name="SoundPos"></param>
	/// <param name="ListenerPos"></param>
	void Play(VECTOR SoundPos ,VECTOR ListenerPos);
	/// <summary>
	/// 聞き手の方向に応じて音を出す
	/// </summary>
	/// <param name="SoundPos">音の発生源</param>
	/// <param name="ListenerPos">聞き手の位置</param>
	/// <param name="ListenerXAxis">聞き手の左</param>
	/// <param name="ListenerYAxis">聞き手の上</param>
	/// <param name="ListenerZAxis">聞き手の前</param>
	void Play(VECTOR SoundPos, VECTOR ListenerPos,VECTOR ListenerXAxis,VECTOR ListenerYAxis,VECTOR ListenerZAxis);
	void Stop();
	void Loop();
	/// <summary>
	/// 元になっている音のボリュームを設定する
	/// </summary>
	/// <param name="volume">０～２５５</param>
	void SetVolume(int volume);

};

