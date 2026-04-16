#include "Scene.h"

bool Scene::Update()
{
    return false;
}

Scene::Scene(Camera* camera, Player* player, Enemy* enemy, int& BackModel, int& MapModel, fps* Fps, Box* Fade, Shadow* shadow):camera(camera), player(player), enemy(enemy), BackModel(BackModel), MapModel(MapModel), Fps(Fps), Fade(Fade), shadow(shadow)
{

}
