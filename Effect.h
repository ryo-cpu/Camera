#pragma once
#include<iostream>
#include"EffectImg.h"
class Effect
{
    
    int PlayHandle;
    VECTOR Move;
    VECTOR Pos;
   
public:
  
   Effect();
   Effect(VECTOR StartPos,EffectImg Img);
   void  Update(float deltaTime);
   

};

