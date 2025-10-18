#pragma once
#include<iostream>
#include "Effect.h"
const int MaxEffect = 20;
class EffectM 
{
	static Effect* Pool[MaxEffect];
	static int Observer[MaxEffect];
public:
	static void Update(float detalTime);
	static	void Add(EffectImg origin);
	static	void Add(EffectImg origin,VECTOR StartPos);

	static	void Draw();
   EffectM();
};

