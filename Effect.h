#pragma once
#include<iostream>
#include"EffectImg.h"

class Effect
{
    
    int PlayHandle;
    int Id;
    VECTOR Move;
    VECTOR Pos;
    VECTOR Rot;
   
public:
  
   Effect();
   Effect(VECTOR StartPos,EffectImg Img);
   Effect(VECTOR StartPos, EffectImg Img,VECTOR StartRot);
   Effect(VECTOR StartPos, EffectImg Img, VECTOR StartRot,VECTOR move);
   Effect(VECTOR StartPos, EffectImg Img, VECTOR StartRot, VECTOR move,int id);



   void  Update(float deltaTime);
   int GetPlayHandle();
   void SetMove(VECTOR move);
   void SetRot(VECTOR rot);
   void Stop();
   int GetId();
   Effect* GetPtr();
   

};

