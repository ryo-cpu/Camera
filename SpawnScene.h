#pragma once
#include "Scene.h"
class SpawnScene :
    public Scene
{
public:

    bool Update() override;
    SpawnScene(Camera* camera, Player* player, Enemy* enemy, int& BackModel, int& MapModel, fps* Fps, Box* Fade, Shadow* shadow);
};

