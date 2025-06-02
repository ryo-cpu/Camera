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



void Character::Draw()
{
    MV1SetPosition(Img, Pos);
}
