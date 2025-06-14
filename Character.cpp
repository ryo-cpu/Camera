#include "Character.h"
#include"iostream"
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

VECTOR Character::GetMove()
{
    return Move;
}

void Character::SetMove(VECTOR move)
{
    Move = move;
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



void Character::Turn(VECTOR Power)
{
   
    Dir = VAdd(Dir,Power);
    // Šp“x‚ðYŽ²‰ñ“]‚ÉƒZƒbƒg
    MV1SetRotationXYZ(Img,Dir);
}
