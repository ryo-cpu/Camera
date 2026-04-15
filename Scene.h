#pragma once
#include"Camera.h"
#include"Player.h"
#include"Box.h"
#include"fps.h"
#include"Shadow.h"
class Scene
{
protected:
	Camera* camera;
	Player* player;
	Enemy* enemy;
	int& BackModel;
	int& MapModel;
	fps* Fps;
	Box* Fade;
public:
	virtual bool Update();



};

