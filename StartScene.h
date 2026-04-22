#pragma once
#include "Scene.h"
class StartScene : public Scene
{
private:
	bool InModeChange;
 public:
	 bool Update() override;
	 StartScene(Camera* camera, Player* player, Enemy* enemy, int& BackModel, int& MapModel, fps* Fps, Box* Fade, Shadow* shadow);

};

