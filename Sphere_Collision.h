#pragma once
#include"DxLib.h"

class Sphere_Collision
{
    float Size;
    VECTOR Pos;
  

public:
    VECTOR   GetPos();
    void     SetPos(VECTOR pos);
    float    GetSphereSize();
    void     SetSphereSize(float sphereSize);
    static bool Collison( const Sphere_Collision &S1,const Sphere_Collision &S2);
};

