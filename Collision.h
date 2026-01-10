#pragma once
#include<iostream>
 class Collision
{
  public:
   virtual bool Survey(const Collision& C1, const Collision& C2)=0;
};

