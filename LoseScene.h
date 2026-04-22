#pragma once
#include "Scene.h"
class LoseScene : public Scene
{
private:
	bool InModeChange;
	Box * ScreenEffct;
public:
	bool Update() override;
	LoseScene(Camera* camera, Player* player, Enemy* enemy, int& BackModel, int& MapModel, fps* Fps, Box* Fade, Shadow* shadow);
	~LoseScene();
};

