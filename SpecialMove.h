#pragma once
#include"DxLib.h"
#include"Camera.h"
#include"Character.h"
const VECTOR SPInitPos = VGet(0, 1000, -2000);
struct AfterImage 
{
    int handle;
    VECTOR pos;
    VECTOR rot;
    int alpha;
    bool valid;
};
enum SpecaleMoveMode
{
	Wait,Jump,ZoomWait,Zoom,Attak
};
class SpecialMove
{
	
Camera& camera;
Character& player;
Character& enemy;

int NowMode;
AfterImage Anafrerimage[10];
public:
	bool Update(float DeltaTime);
	
	SpecialMove (Camera& Camera, Character& Player, Character& Enemy);


};

