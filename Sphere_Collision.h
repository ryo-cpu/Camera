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
    static bool Collison(Sphere_Collision S1, Sphere_Collision S2);
};

