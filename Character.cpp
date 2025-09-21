#include "Character.h"
#include"iostream"
Character::Character()
{
    LiveTime = 0;
    isDraw = true;
}
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
    MV1SetScale(Img, VGet(scale, scale, scale));

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

void Character::AnimUpdate(float deltaTime)
{

    NowAnimTime+= deltaTime * AnimSpeed;  // アニメーション時間を進める

    if (AnimType >= 0)
    {  // アニメーションが設定されていれば
        NowAnimTime += deltaTime * AnimSpeed;
        IsAnim = true;
    }
    if (NowAnimTime >= AnimTotalTime)
    {
        IsAnim=false;
    }
    MV1SetAttachAnimTime(Img,AnimIndex,NowAnimTime);  // アニメーション時間を設定
}

void Character::MoveUpdate(VECTOR move)
{
    Pos = VAdd(Pos, move);
    MoveCollison(move);
}

void Character::Update(float deltaTime)
{
}






void Character::Draw()
{
    if (isDraw)
    {
        MV1DrawModel(Img);
    }
}
Sphere_Collision Character::GetAttackCollison()
{
    return AttackCollison;
}

void Character::SetAttackCollison(VECTOR Pos, float size)
{
    AttackCollison.SetPos(Pos);
    AttackCollison.SetSphereSize(size);
}

bool Character::GetIsUpdate()
{
    return isUpdate;
}

void Character::SetIsUpdate(bool isupdate)
{
    isUpdate = isupdate;
}

bool Character::GetIsAnim()
{
    return IsAnim;
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

float Character::GetLiveTime()
{
    return LiveTime;
}

void Character::AddLiveTime(float PassedTime)
{
    LiveTime += PassedTime;
}

int Character::GetStartLiveTime()
{
    return StartLiveTime;
}

void Character::SetStartLiveTime(int Time)
{
    StartLiveTime = Time;
}

int Character::GetMaxHp()
{
    return MaxHp;
}

void Character::SubHp(int Damage)
{

    Hp = Hp - Damage>=0? Hp - Damage:0;
}

void Character::SetisDraw(bool Flg)
{
    isDraw = Flg;
}

bool Character::GetisDraw()
{
    return isDraw;
}
