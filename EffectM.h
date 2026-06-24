#pragma once
#include<iostream>
#include "Effect.h"
const int MaxEffect = 10;
const int PlayerAuraID = 111;
const int ResidentID = 2222;
class EffectM 
{
	static Effect* Pool[MaxEffect];
	static int Observer[MaxEffect];
	static EffectImg ResidentEffect;
public:
	static void Update(float deltaTime);
	static	void Add(EffectImg origin);
	static	void Add(EffectImg origin,VECTOR StartPos);
	static	void Add(EffectImg origin, VECTOR StartPos,VECTOR StartRot);
	static	void Add(EffectImg origin, VECTOR StartPos, VECTOR StartRot,VECTOR move);
	static	void Add(EffectImg origin, VECTOR StartPos, VECTOR StartRot, VECTOR move,int id);
	


	static  Effect* Search(int id);
	static	void Draw();
	static  void Clear();
   EffectM();
   ~EffectM();
};

