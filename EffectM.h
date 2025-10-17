#pragma once
#include "Effect.h"
const int MaxEffect = 20;
class EffectM 
{
	Effect *Pool[MaxEffect];
public:
	void Update(float detalTime);
	void Add(EffectImg origin);
	void Add(EffectImg origin,VECTOR StartPos);

	void Draw();
	EffectM();
};

