#pragma once
#include "Scene.h"
class WinScene :
    public Scene
{
private:
	bool InModeChange;
public:
	bool Update() override;
	WinScene(Camera* camera, Player* player, Enemy* enemy, int& BackModel, int& MapModel, fps* Fps, Box* Fade, Shadow* shadow);

};

