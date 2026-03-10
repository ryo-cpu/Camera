#include "Shadow.h"



Shadow::Shadow(VECTOR lightDir)
{
	MapHandle = MakeShadowMap(2048, 2048);
	SetShadowMapLightDirection(MapHandle, lightDir);
	SetShadowMapDrawArea(
		MapHandle,
		VGet(-10000.0f, -100.0f, -10000.0f),
		VGet(10000.0f, 1000.0f, 10000.0f)
	);
	SetShadowMapAdjustDepth(MapHandle, 0.005);
}

Shadow::~Shadow()
{
	DeleteShadowMap(MapHandle);
}

void Shadow::AddTarget(int targetModel)
{
	Targets.push_back(targetModel);
}

void Shadow::Draw()
{
	///âeÇçÏÇÈ
   ShadowMap_DrawSetup(MapHandle);
   for (int i = 0; i < Targets.size(); i++)
   {
	   MV1DrawModel(Targets[i]);
   }
   ShadowMap_DrawEnd();
}

void Shadow::StartUse()
{
	SetUseShadowMap(0, MapHandle);
}

void Shadow::EndUse()
{
	SetUseShadowMap(0, -1);
}

void Shadow::Test()
{
	TestDrawShadowMap(MapHandle, 0, 0, 320, 240);
}


