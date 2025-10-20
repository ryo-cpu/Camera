#pragma once
#include<iostream>
#include"EffectImg.h"
class Effect
{
    
    int PlayHandle;
    VECTOR Move;
    VECTOR Pos;
    VECTOR Rot;
   
public:
  
   Effect();
   Effect(VECTOR StartPos,EffectImg Img);
   Effect(VECTOR StartPos, EffectImg Img,VECTOR StartRot);
   Effect(VECTOR StartPos, EffectImg Img, VECTOR StartRot,VECTOR move);


   void  Update(float deltaTime);
   int GetPlayHandle();
   

};

