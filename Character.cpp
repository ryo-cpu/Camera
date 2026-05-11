#include "Character.h"
#include "iostream"
#include <algorithm> 
 
Character::Character()
{
    LiveTime = 0.0f;
    StartLiveTime = 0.0f;
    isDraw = true;
    isUpdate = true;

    Img = -1;
    Hp = 0;
    MaxHp = 0;

    AnimTotalTime = 0;
    Attack = 0;

    AnimIndex = -1;
    AnimType = -1;
    AnimSpeed = 1.0f;
    IsAnim = false;
    MV1SetupCollInfo(Img, 0, -1, -1);
}
Character::Character(int img)
{
    //モデルが同じのと処理軽減のため手動
    Img = img;
    isDraw = true;
    Capsule Body("mixamorig:Hips", "mixamorig:Neck", 100, Img);
    CapsuleCollision.push_back(Body);
    Capsule LeftArm("mixamorig:LeftArm", "mixamorig:Neck", 100, Img);
    CapsuleCollision.push_back(LeftArm); 
    Capsule LeftForeArm("mixamorig:LeftArm", "mixamorig:LeftForeArm", 100, Img);
    CapsuleCollision.push_back(LeftForeArm);
    Capsule LeftHand("mixamorig:LeftHand", "mixamorig:LeftForeArm", 100, Img);
    CapsuleCollision.push_back(LeftHand);
    Capsule LeftHandIndex("mixamorig:LeftHand", "mixamorig:LeftHandIndex3", 100, Img);
    CapsuleCollision.push_back(LeftHandIndex);
    Capsule RightArm("mixamorig:RightArm", "mixamorig:Neck", 100, Img);
    CapsuleCollision.push_back(RightArm);
    Capsule RightForeArm("mixamorig:RightArm", "mixamorig:RightForeArm", 100, Img);
    CapsuleCollision.push_back(RightForeArm);
    Capsule RightHand("mixamorig:RightHand", "mixamorig:RightForeArm", 100, Img);
    CapsuleCollision.push_back(RightHand);
    Capsule RightHandIndex("mixamorig:RightHand", "mixamorig:RightHandIndex3", 100, Img);
    CapsuleCollision.push_back(RightHandIndex);
    Capsule LeftUpLeg("mixamorig:Hips", "mixamorig:LeftUpLeg", 100, Img);
    CapsuleCollision.push_back(LeftUpLeg);
    Capsule LeftLeg("mixamorig:LeftLeg", "mixamorig:LeftUpLeg", 100, Img);
    CapsuleCollision.push_back(LeftLeg);
    Capsule LeftFoot("mixamorig:LeftLeg", "mixamorig:LeftFoot", 100, Img);
    CapsuleCollision.push_back(LeftFoot);
    Capsule LeftToeBase("mixamorig:LeftToBase", "mixamorig:LeftFoot", 100, Img);
    CapsuleCollision.push_back(LeftFoot);
    Capsule RightUpLeg("mixamorig:Hips", "mixamorig:RightUpLeg", 100, Img);
    CapsuleCollision.push_back(RightUpLeg);
    Capsule RightLeg("mixamorig:RightLeg", "mixamorig:RightUpLeg", 100, Img);
    CapsuleCollision.push_back(RightLeg);
    Capsule RightFoot("mixamorig:RightLeg", "mixamorig:RightFoot", 100, Img);
    CapsuleCollision.push_back(RightFoot);
    Capsule RightToeBase("mixamorig:RightToBase", "mixamorig:RightFoot", 100, Img);
    CapsuleCollision.push_back(RightFoot);
}
Character::~Character()
{
    MV1DrawModel(Img);
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

    IsAnim = true;

    if (NowAnimTime >= AnimTotalTime)
    {
        IsAnim=false;
    }
    MV1SetAttachAnimTime(Img,AnimIndex,NowAnimTime);  // アニメーション時間を設定
}

void Character::MoveUpdate(VECTOR move)
{
    Pos = VAdd(Pos, move);
    MoveCollision(move);
}

void Character::Update(float deltaTime)
{
}

void Character::Initial()
{
}






void Character::Draw()
{
    if (isDraw)
    {
        MV1DrawModel(Img);
    }
}
Sphere_Collision Character::GetAttackCollision()
{
    return AttackCollision;
}

void Character::SetAttackCollision(VECTOR Pos, float size)
{
   AttackCollision.SetPos(Pos);
   AttackCollision.SetSphereSize(size);
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

void Character::DrawCapsuleCollision()
{
    for (int i = 0; i < CapsuleCollision.size(); i++)
    {
        Capsule DrawCapsule = CapsuleCollision[i];

        DrawCapsule3D(DrawCapsule.GetStartPos(), DrawCapsule.GetEndPos(), DrawCapsule.GetRSize(), 8, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
    }
}

void Character::UpdateCapsuleCollision()
{
    for (int i = 0; i < CapsuleCollision.size(); i++)
    {
        CapsuleCollision[i].Update(Img);
    }
}

void Character::UpdateCapsuleCollision(VECTOR move)
{
    for (int i = 0; i < CapsuleCollision.size(); i++)
    {
        CapsuleCollision[i].Update(move);
    }
}

void Character::SetCapsuleCollisionRsize(float r)
{
    for (int i = 0; i < CapsuleCollision.size(); i++)
    {
        CapsuleCollision[i].SetRSize(r);
    }
}

std::vector<Capsule> Character::GetCapsuleCollision()
{
    return CapsuleCollision;
}

VECTOR Character::PushBackCapsuleCollison(Character Move, Character NotMove)
{
    VECTOR pushBack = VGet(0, 0, 0);
    std::vector<Capsule> M = Move.GetCapsuleCollision();
    std::vector<Capsule> N =NotMove.GetCapsuleCollision();
    Capsule Jag;
    std::vector<int> HitCapusuleListN;
	ModelCheckers Checkers;

    for (int i = 0; i <M.size(); i++)
    {
        for (int j = 0; j < N.size(); j++)
        {
            if (Jag.Survey(M[i], N[j]))
            {
                 VECTOR p= Jag.PushBack(M[i], N[j]);
                 HitCapusuleListN.push_back(j);
                 const char* HipName =M[i].GetStartName();
                 // ✅ デバッグ出力（確認用）
                //DrawCapsule3D(M[i].GetStartPos(), M[i].GetEndPos(), M[i].GetRSize()+20, 8,GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
                 //DrawCapsule3D(N[j].GetStartPos(), N[j].GetEndPos(), N[j].GetRSize() + 20, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);

                 int HipIndex = MV1SearchFrame(Move.GetImg(), HipName);
				 ///相手のカプセルにモデルの部分を取得
                MV1_COLL_RESULT_POLY_DIM MovePolys=MV1CollCheck_Capsule(Move.GetImg(), -1, N[j].GetStartPos(), N[j].GetEndPos(), N[j].GetRSize());
                MV1_COLL_RESULT_POLY_DIM NotMovePolys = MV1CollCheck_Capsule(NotMove.GetImg(), -1, M[i].GetStartPos(), M[i].GetEndPos(), M[i].GetRSize());

                if (NotMovePolys.HitNum>0&&MovePolys.HitNum>0)
                {
                  VSize(p) > VSize(pushBack) ? p : pushBack;
                }
                
                for (int m = 0; m < MovePolys.HitNum; m++)
                {
                    for(int n = 0; n < NotMovePolys.HitNum; n++)
                    {
						MV1_COLL_RESULT_POLY MoveP = MovePolys.Dim[m];
						MV1_COLL_RESULT_POLY NotMoveP = NotMovePolys.Dim[n];
                        float MR = VSize(Checkers.VMax(VSub(MoveP.Position[0], MoveP.Position[1]), VSub(MoveP.Position[0], MoveP.Position[2])));
                        float NR = VSize(Checkers.VMax(VSub(NotMoveP.Position[0], NotMoveP.Position[1]), VSub(NotMoveP.Position[0], NotMoveP.Position[2])));

                        if (VSize(VSub(NotMoveP.Position[0], MoveP.Position[0]))<(MR+NR))
                        {
                            DrawSphere3D(NotMoveP.Position[0], NR, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
                          
                            ///ポリゴン同士のの当たり判定かつ押し返し
                            if (Checkers.IsTriangle_Joint_Triangle(MoveP.Position[0], MoveP.Position[1], MoveP.Position[2], NotMoveP.Position[0], NotMoveP.Position[1], NotMoveP.Position[2]))
                            {
                                ///////////////
                                pushBack = VSize(p) > VSize(pushBack) ? p : pushBack;

                            }
                        }
                      
					}
                }
                   //pushBack = VSize(p) > VSize(pushBack) ? p : pushBack;
            }
        }
    }
    std::sort(HitCapusuleListN.begin(), HitCapusuleListN.end());
    auto it = std::unique(HitCapusuleListN.begin(), HitCapusuleListN.end());
    HitCapusuleListN.erase(it, HitCapusuleListN.end());
    for (int i = 0; i < HitCapusuleListN.size(); i++)
    {
       

     

    }

    return pushBack;
}

bool Character::isHitCaracters(Character A, Character B)
{
    Capsule Jag;
    for (int i = 0; i < A.GetCapsuleCollision().size(); i++)
    {
        for (int j = 0; j < B.GetCapsuleCollision().size(); j++)
        {
            if (Jag.Survey(A.GetCapsuleCollision()[i], B.GetCapsuleCollision()[j]))
            {
                return true;
            }
        }

    }
    return false;
}

VECTOR Character::GetFramPos(const char* framName)
{
    VECTOR Pos=VGet(0,0,0);
    const char* FramName = framName;
    
    if (Img != 0)
    {
        int FramIndex = MV1SearchFrame(Img, FramName);
        if (FramIndex >= 0)
        {
            Pos = MV1GetFramePosition(Img, FramIndex);
        }

    }
    
    return Pos;
}

Capsule Character::SearchCapsule(const char* frameName)
{
    for (int i = 0; i > CapsuleCollision.size(); i++)
    {
       if(CapsuleCollision[i].GetStartName() == frameName)
       {
           return CapsuleCollision[i];
       }
    }
}



void Character::Turn(VECTOR RotatePower)
{
   
    Dir = VAdd(Dir, RotatePower);
    // 角度をY軸回転にセット
    MV1SetRotationXYZ(Img,Dir);
}

Sphere_Collision Character::GetCollision()
{
    return Collision;
}

void Character::SetCollision(VECTOR Pos, float size)
{
    Collision.SetPos(Pos);
    Collision.SetSphereSize(size);
}

void Character::MoveCollision(VECTOR move)
{
    Collision.SetPos(VAdd(Pos, move));
}

float Character::GetLiveTime()
{
    return LiveTime;
}

void Character::AddLiveTime(float PassedTime)
{
    LiveTime += PassedTime;
}

float Character::GetStartLiveTime()
{
    return StartLiveTime;
}

void Character::SetStartLiveTime(float Time)
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
