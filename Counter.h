#pragma once
#include "SpecialMove.h"
/// <summary>
/// 動きを制御するクラス（カウンター）
/// </summary>
class Counter
{

private:
	Camera& camera;
	Player& player;
	Character& enemy;
	bool InWait;///待機状態か判断
	bool IsHit;
	/// <summary>
	/// 攻撃状態に入った時間
	/// </summary>
	float InAttackTime;
public:
	Counter(Camera& Camera,Player& Player, Character& Enemy);
	~Counter();
	/// <summary>
	/// 
	/// </summary>
	/// <param name="DeltaTime">経過時間</param>
	/// <returns>アップデートするかを返す</returns>
	bool Update(float DeltaTime);
	void SetHit(bool isHit);


};

