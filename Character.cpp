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
    MV1SetRotationXYZ(Img,Dir);

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


float Character::GetScale()
{
    return Scale;
}

void Character::SetScale(float scale)
{
    Scale = scale;
}

void Character::SetAttack(int attack)
{
    Attack = attack;
}

int Character::GetAttack()
{
    return Attack;
}

void Character::SetHp(int hp)
{
    Hp = hp;
}

int Character::GetHp()
{
    return Hp;
}

void Character::SetAnimIndex(int animIndex)
{
    AnimIndex = animIndex;

}

int Character::GetAnimIndex()
{
    return AnimIndex;
}



void Character::SetAnimType(int animType)
{
    if (AnimIndex != -1) 
    {
       
     MV1DetachAnim(Img, AnimIndex);
    }
    AnimIndex =MV1AttachAnim(Img, animType);
    AnimTotalTime = MV1GetAttachAnimTotalTime(Img, AnimIndex);
    AnimType = animType;
    IsAnim = true;

    NowAnimTime = 0;
    MV1SetAttachAnimTime(Img, AnimIndex, NowAnimTime);  // アニメーション時間を設定

}

int Character::GetAnimType()
{
    return AnimType;
}

float Character::GetNowAnimTime()
{
    return NowAnimTime;
}

void Character::SetNowAnimTime(float nowanimtime)
{
    NowAnimTime = nowanimtime;
}

void Character::SetTotalAnimTime(float animtotalTime)
{
    AnimTotalTime = animtotalTime;
}

float Character::GetTotalAnimTime()
{
    return AnimTotalTime;
}

void Character::SetAnimSpeed(float Speed)
{
    AnimSpeed = Speed;
}

float Character::GetAnimSpeed()
{
    return AnimSpeed;
}

void Character::AnimUpdate()
{
    // 前回のフレームから経過した時間を取得
    LONGLONG nowTime = GetNowHiPerformanceCount();
    float deltaTime = (nowTime) / 10000000.0f;  // 時間を秒に変換

    NowAnimTime+= deltaTime * AnimSpeed;  // アニメーション時間を進める

    if (AnimType >= 0)
    {  // アニメーションが設定されていれば
        NowAnimTime += deltaTime * AnimSpeed;
    }
    if (NowAnimTime >= AnimTotalTime)
    {
        IsAnim=false;
    }
    MV1SetAttachAnimTime(Img,AnimIndex,NowAnimTime);  // アニメーション時間を設定
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
    // 角度をY軸回転にセット
    MV1SetRotationXYZ(Img,Dir);
}

Sphere_Collision Character::GetCollison()
{
    return Collison;
}

void Character::SetCollison(VECTOR Pos, float size)
{
    Collison.SetPos(Pos);
    Collison.SetSphereSize(size);
}

void Character::MoveCollison(VECTOR move)
{
    Collison.SetPos(VAdd(Pos, move));
}
