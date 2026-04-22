#pragma once
#include<vector>
#include "DxLib.h"
class Shadow
{
private:
	int MapHandle;
	std::vector<int> Targets;
	VECTOR LightDir;
	VECTOR AreaRight, AreaLeft;
public:
	
	Shadow(VECTOR lightDir);
	~Shadow();
	void AddTarget(int targetModel);
	void Draw();
	void StartUse();
	void EndUse();
	void Test();
};

