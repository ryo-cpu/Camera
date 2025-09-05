#pragma once
#include"DxLib.h"
#include"Camera.h"
#include"Character.h"
const VECTOR SPInitPos = VGet(0, 1000, -2000);
class SpecialMove
{

Camera& camera;
Character& player;
Character& enemy;

public:
	bool Update(float DeltaTime);
	SpecialMove (Camera& Camera, Character& Player, Character& Enemy);


};

