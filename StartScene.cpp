#include "StartScene.h"

bool StartScene::Update()
{
    bool InModeCheng;
	float deltaTime = Fps->GetDeltaTime();
	if (Fade->GetAlpha() > 0 && !InModeCheng)
	{

		Fade->SetAlpha(Fade->GetAlpha() - (255 / 2 * deltaTime));

	}
    return false;
}
