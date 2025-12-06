#pragma once
#include"DxLib.h"
#include"Camera.h"
#include"Character.h"
#include<vector>
const VECTOR SPInitPos = VGet(0, 1000, -2000);
const int SpEffctID = 2034;
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
std::vector< AfterImage> Afterimages;
public:
	bool Update(float DeltaTime);
	
	SpecialMove (Camera& Camera, Character& Player, Character& Enemy);


};

