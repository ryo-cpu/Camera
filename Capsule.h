#pragma once
#include"DxLib.h"
#include "Collision.h"


class Capsule : public Collision
{ 
    float Size;
    VECTOR StartPos,EndPos;


public:
    VECTOR   GetStartPos()const;
    VECTOR   GetEndPos()const;
    void     SetStartPos(VECTOR pos);
    void     SetEndPos(VECTOR pos);
    float    GetSphereSize();
    void     SetSphereSize(float sphereSize);
    virtual bool Survey(const Collision& C1, const Collision& C2)override;

   
};

