#pragma once
#include<iostream>
#include "EffekseerForDXLib.h"
class Effect
{
    int Model;
    int PlayHandle;
    VECTOR Move;
    VECTOR Pos;
public:
   Effect(std::string Link);
   void Play(VECTOR StratPos);
   void  Update(float deltaTime);
   void  Draw();

};

