#include "Player.h"

int Player::GetImg()
{
    return Img;
}

void Player::SetImg(int img)
{
    Img = img;
}

VECTOR Player::GetPos()
{
    return Pos;
}

void Player::SetPos(VECTOR pos)
{
    Pos = pos;
}

VECTOR Player::GetDir()
{
    return Dir;
}

void Player::SetDir(VECTOR dir)
{
    Dir = dir;
}

float Player::GetSpeed()
{
    return Speed;
}

void Player::SetSpeed(float speed)
{
    Speed = speed;
}

float Player::GetSphereSize()
{
    return SphereSize;
}

void Player::SetSphereSize(float sphereSize)
{
    SphereSize = sphereSize;
}

float Player::GetScale()
{
    return Scale;
}

void Player::SetScale(float scale)
{
    Scale = scale;
}

void Player::Update()
{
    ////à íuÇÃçXêV
    SetPos(VAdd(Pos, Dir));
}

void Player::Draw()
{
    MV1SetPosition(Img, Pos);
}
