#pragma once
#include "Arithmetic.h"
#include "Camera.h"
#include "Player.h"
#include "Box.h"
#include "fps.h"
#include "Shadow.h"
#include "EffectM.h"

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
	Shadow* shadow;
	EffectM* effectM;
public:
	virtual bool Update();
 	Scene(Camera* camera,Player* player,Enemy* enemy,int& BackModel,int& MapModel,fps* Fps,Box* Fade,Shadow* shadow);



};

