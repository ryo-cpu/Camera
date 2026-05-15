#pragma once
#include "Scene.h"
class SpawnScene :
    public Scene
{
    VECTOR speed;
    float waitTime;
public:

    bool Update() override;
    SpawnScene(Camera* camera, Player* player, Enemy* enemy, int& BackModel, int& MapModel, fps* Fps, Box* Fade, Shadow* shadow);
};

