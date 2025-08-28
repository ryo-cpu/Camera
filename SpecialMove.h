#pragma once
#include"DxLib.h"
#include"Camera.h"
#include"Character.h"
class SpecialMove
{

Camera& camera;
Character& player;
Character& enemy;
public:
	bool Update(float DeltaTime);
	SpecialMove (Camera& Camera, Character& Player, Character& Enemy);


};

