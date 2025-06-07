#include "Character.h"
int Character::GetImg()
{
    return Img;
}

 
void Character::SetImg(int img)
{
    Img = img;
}

VECTOR Character::GetPos()
{
    return Pos;
}

void Character::SetPos(VECTOR pos)
{
    Pos = pos;
}

VECTOR Character::GetDir()
{
    return Dir;
}

void Character::SetDir(VECTOR dir)
{
    Dir = dir;
}

float Character::GetSpeed()
{
    return Speed;
}

void Character::SetSpeed(float speed)
{
    Speed = speed;
}

float Character::GetSphereSize()
{
    return SphereSize;
}

void Character::SetSphereSize(float sphereSize)
{
    SphereSize = sphereSize;
}

float Character::GetScale()
{
    return Scale;
}

void Character::SetScale(float scale)
{
    Scale = scale;
}

void Character::Update()
{
}



void Character::Draw()
{
    MV1SetPosition(Img, Pos);
}

bool Character::Collison(Character C1, Character C2)
{
    VECTOR Distance = VSub(C1.GetPos(),C2.GetPos());

    if (VSize(Distance) < C1.SphereSize+C2.SphereSize)
    {
        return true;
    }
    else
    {
        false;
    }
}
