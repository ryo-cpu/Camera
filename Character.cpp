#include "Character.h"
#include "iostream"
#include <algorithm> 
#include<math.h>
#include <chrono>
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
    SetNextImg(Img);
}
Character::Character(int img):Character()
{
    //モデルが同じのと処理軽減のため手動
    Img = img;
    SetNextImg(Img);
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
    Capsule LeftToeBase("mixamorig:LeftToeBase", "mixamorig:LeftFoot", 100, Img);
    CapsuleCollision.push_back(LeftToeBase);
    Capsule LeftToe_End("mixamorig:LeftToeBase", "mixamorig:LeftToe_End", 100, Img);
    CapsuleCollision.push_back(LeftToe_End);
    Capsule RightUpLeg("mixamorig:Hips", "mixamorig:RightUpLeg", 100, Img);
    CapsuleCollision.push_back(RightUpLeg);
    Capsule RightLeg("mixamorig:RightLeg", "mixamorig:RightUpLeg", 100, Img);
    CapsuleCollision.push_back(RightLeg);
    Capsule RightFoot("mixamorig:RightLeg", "mixamorig:RightFoot", 100, Img);
    CapsuleCollision.push_back(RightFoot);
    Capsule RightToeBase("mixamorig:RightToeBase", "mixamorig:RightFoot", 100, Img);
    CapsuleCollision.push_back(RightToeBase);
    Capsule RightToe_End("mixamorig:RightToeBase", "mixamorig:RightToe_End", 100, Img);
    CapsuleCollision.push_back(RightToe_End);
}
Character::~Character()
{
    MV1DeleteModel(Img);
    MV1DeleteModel(NextImg);
}
int Character::GetImg()
{
    return Img;
}

 
void Character::SetImg(int img)
{
    Img = img;
    SetNextImg(Img);
}

int Character::GetNextImg()
{
    return NextImg;
}

void Character::SetNextImg(int img)
{
    NextImg =MV1DuplicateModel(img);
    MV1SetScale(NextImg,VGet(Scale,Scale,Scale));
    MV1SetRotationXYZ(NextImg, Dir);
    MV1SetPosition(NextImg, Pos);  // ← 位置も設定
    MV1SetAttachAnimTime(NextImg, AnimIndex, NowAnimTime);  // アニメーション時間を設定
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
    MV1SetRotationXYZ(NextImg, Dir);


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
    MV1SetScale(NextImg, VGet(scale, scale, scale));


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
     MV1DetachAnim(NextImg, AnimIndex);

    }
    AnimIndex =MV1AttachAnim(Img, animType);
    MV1AttachAnim(NextImg, animType);
    AnimTotalTime = MV1GetAttachAnimTotalTime(Img, AnimIndex);
    AnimType = animType;
    IsAnim = true;

    NowAnimTime = 0;
    MV1SetAttachAnimTime(Img, AnimIndex, NowAnimTime);  // アニメーション時間を設定
    MV1SetAttachAnimTime(NextImg, AnimIndex, NowAnimTime);  // アニメーション時間を設定
    
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
    MV1SetAttachAnimTime(Img,AnimIndex,NowAnimTime); 
    MV1SetAttachAnimTime(NextImg, AnimIndex, NowAnimTime);  // アニメーション時間を設定
    // アニメーション時間を設定
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

VECTOR Character::PushBackCapsuleCollison(Character &Move, Character &NotMove)
{
    VECTOR pushBack = VGet(0, 0, 0);
    std::vector<Capsule> M = Move.GetCapsuleCollision();
    std::vector<Capsule> N =NotMove.GetCapsuleCollision();
    Capsule Jag;
    float MaxPenetration = 0.0f; ///貫通量
    std::vector<int> HitCapusuleListN;
    int count = 0;
    bool isfastTouch = false;
    float Min = 1000.0f;
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "処理時間: " << duration_ms << " ms" << std::endl;
    
    for (int i = 0; i <M.size(); i++)
    {
        for (int j = 0; j < N.size(); j++)
        {
            if (Jag.Survey(M[i], N[j]))
            {
                 count++;
                 VECTOR p= Jag.PushBack(M[i], N[j]);
                 HitCapusuleListN.push_back(j);
                 const char* HipName =M[i].GetStartName();
              
            
                 if (!isfastTouch)
                 {
                     MV1RefreshCollInfo(NotMove.NextImg, -1);
                     MV1RefreshCollInfo(Move.NextImg, -1);
                     isfastTouch = true;
                 }
              
               

				 ///相手のカプセルにモデルの部分を取得
                MV1_COLL_RESULT_POLY_DIM MovePolys=MV1CollCheck_Capsule(Move.GetNextImg(), -1, N[j].GetStartPos(), N[j].GetEndPos(), N[j].GetRSize());
                MV1_COLL_RESULT_POLY_DIM NotMovePolys = MV1CollCheck_Capsule(NotMove.GetNextImg(), -1, M[i].GetStartPos(), M[i].GetEndPos(), M[i].GetRSize());
                
              

                if (NotMovePolys.HitNum<=0||MovePolys.HitNum<=0)
                {
                    MV1CollResultPolyDimTerminate(MovePolys);
                    MV1CollResultPolyDimTerminate(NotMovePolys);
                    continue;
                }
                MV1_COLL_RESULT_POLY MovePoly;
                MV1_COLL_RESULT_POLY NotMovePoly;
                VECTOR MoveCenterPoint;
                VECTOR NotMoveCenterPoint;
                start = std::chrono::high_resolution_clock::now();
                for (int m = 0; m < MovePolys.HitNum; m++)
                {
                    MovePoly = MovePolys.Dim[m];
                    ///適当な辺の長さを求める(MovePoly.Position[0]
                    MoveCenterPoint = VSub(MovePoly.Position[1], MovePoly.Position[0]);
                    ///その長さの半分を求める
                    MoveCenterPoint = VScale(MoveCenterPoint, 1 / 2.0f);
                    ///辺のスタート位置をあわせ座標化
                    MoveCenterPoint = VAdd(MoveCenterPoint, MovePoly.Position[0]);
                    ///辺に入っていない残りの点への長さを求める これは後で MovePoly.Position[2]からの座標にするのでこの形
                    MoveCenterPoint = VSub(MoveCenterPoint, MovePoly.Position[2]);
                    ///その長さの半分を求める
                    MoveCenterPoint = VScale(MoveCenterPoint, 1 / 2.0f);
                    ///辺のスタート位置をあわせ座標化
                    MoveCenterPoint = VAdd(MoveCenterPoint, MovePoly.Position[2]);

                    float MR = Vsize(VMax(VSub(MoveCenterPoint, MovePoly.Position[1]), VSub(MoveCenterPoint, MovePoly.Position[2]), VSub(MoveCenterPoint, MovePoly.Position[0])));
                    int count = 0;
                    for(int n = 0; n < NotMovePolys.HitNum; n++)
                    {
                        ////////////////////////////////////////////////
						
                        NotMovePoly= NotMovePolys.Dim[n];


                      

                        ///適当な辺の長さを求める(MovePoly.Position[0]
                        NotMoveCenterPoint = VSub(NotMovePoly.Position[1], NotMovePoly.Position[0]);
                        ///その長さの半分を求める
                        NotMoveCenterPoint = VScale(NotMoveCenterPoint, 1 / 2.0f);
                        ///辺のスタート位置をあわせ座標化
                        NotMoveCenterPoint = VAdd(NotMoveCenterPoint, NotMovePoly.Position[0]);
                        ///辺に入っていない残りの点への長さを求める これは後で MovePoly.Position[2]からの座標にするのでこの形
                        NotMoveCenterPoint = VSub(NotMoveCenterPoint, NotMovePoly.Position[2]);
                        ///その長さの半分を求める
                        NotMoveCenterPoint = VScale(NotMoveCenterPoint, 1 / 2.0f);
                        ///辺のスタート位置をあわせ座標化
                        NotMoveCenterPoint = VAdd(NotMoveCenterPoint, NotMovePoly.Position[2]);


                        ///センターから最も離れたてんを半径とした球体を作る
                        float NR = Vsize(VMax(VSub(NotMoveCenterPoint, NotMovePoly.Position[1]), VSub(NotMoveCenterPoint, NotMovePoly.Position[2]), VSub(NotMoveCenterPoint, NotMovePoly.Position[0])));
                      
                        if (Vsize(VSub(NotMoveCenterPoint, MoveCenterPoint))<(MR+NR))
                        {
                            count++;
                            NR = sqrtf(NR);
                            MR = sqrtf(MR);
                          
                                for (int i = 0; i < 3; i++)
                                {
                                    ///ポイントが三角形状にあるか調べる
                                    if (IsPointInTriangle(MovePoly.Position[i], NotMovePoly.Position[0], NotMovePoly.Position[1], NotMovePoly.Position[2]))
                                    { 
                                        VECTOR dir = VSub(MoveCenterPoint, NotMoveCenterPoint);
                                        float dist = VSize(dir);

                                        if (dist < 0.0001f)  continue;

                                         dir = VNorm(dir);

                                         // -----------------------------
                                         // 侵食量（めり込み量）
                                         // -----------------------------
                                        
                                         float penetration = (MR + NR) - dist;

                                         if (penetration <= 0.0f) continue;

                                         if (penetration > MaxPenetration)
                                         {
                                             MaxPenetration = penetration;

                                             VECTOR dir = VSub(MoveCenterPoint, NotMoveCenterPoint);
                                             pushBack = VNorm(dir);
                                         }
                                       


                                    }
                                }

                        }
                      

					}
                    int anananfnana=count;
                 
                }

                MV1CollResultPolyDimTerminate(MovePolys);
                MV1CollResultPolyDimTerminate(NotMovePolys);
              /*  int ans = count;
                */
               // pushBack = VSize(p) > VSize(pushBack) ? p : pushBack;
                end = std::chrono::high_resolution_clock::now();
                duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                
            }
        }
    }

    return VScale(pushBack,MaxPenetration);
}

bool Character::isHitCaracters(Character &A, Character &B)
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

bool Character::isHitCaracter(Character& A, Character& B, Capsule HitSpease)
{
    MV1RefreshCollInfo(A.NextImg, -1);
    MV1RefreshCollInfo(B.NextImg, -1);
    MV1_COLL_RESULT_POLY_DIM APolys = MV1CollCheck_Capsule(A.GetNextImg(), -1, HitSpease.GetStartPos(), HitSpease.GetEndPos(), HitSpease.GetRSize());
    MV1_COLL_RESULT_POLY_DIM BPolys = MV1CollCheck_Capsule(B.GetNextImg(), -1, HitSpease.GetStartPos(), HitSpease.GetEndPos(), HitSpease.GetRSize());
    VECTOR ACenterPoint;
    VECTOR BCenterPoint;
    MV1_COLL_RESULT_POLY APoly;
    MV1_COLL_RESULT_POLY BPoly;
    float AR;
    float BR;
    for (int i = 0; i < APolys.HitNum; i++)
    {
        APoly = APolys.Dim[i];
        ///適当な辺の長さを求める(MovePoly.Position[0]
        ACenterPoint = VSub(APoly.Position[1], APoly.Position[0]);
        ///その長さの半分を求める
        ACenterPoint = VScale(ACenterPoint, 1 / 2.0f);
        ///辺のスタート位置をあわせ座標化
        ACenterPoint = VAdd(ACenterPoint, APoly.Position[0]);
        ///辺に入っていない残りの点への長さを求める これは後で APoly.Position[2]からの座標にするのでこの形
        ACenterPoint = VSub(ACenterPoint, APoly.Position[2]);
        ///その長さの半分を求める
        ACenterPoint = VScale(ACenterPoint, 1 / 2.0f);
        ///辺のスタート位置をあわせ座標化
        ACenterPoint = VAdd(ACenterPoint, APoly.Position[2]);
        AR = VSize(VMax(VSub(ACenterPoint, APoly.Position[1]), VSub(ACenterPoint, APoly.Position[2]), VSub(ACenterPoint, APoly.Position[0])));

        for (int j = 0; j < BPolys.HitNum; j++)
        {
            BPoly = BPolys.Dim[j];
            ///適当な辺の長さを求める(MovePoly.Position[0]
           BCenterPoint = VSub(BPoly.Position[1],BPoly.Position[0]);
            ///その長さの半分を求める
           BCenterPoint = VScale(BCenterPoint, 1 / 2.0f);
            ///辺のスタート位置をあわせ座標化
           BCenterPoint = VAdd(BCenterPoint,BPoly.Position[0]);
            ///辺に入っていない残りの点への長さを求める これは後でBPoly.Position[2]からの座標にするのでこの形
           BCenterPoint = VSub(BCenterPoint,BPoly.Position[2]);
            ///その長さの半分を求める
           BCenterPoint = VScale(BCenterPoint, 1 / 2.0f);
            ///辺のスタート位置をあわせ座標化
           BCenterPoint = VAdd(BCenterPoint,BPoly.Position[2]);
           BR = VSize(VMax(VSub(BCenterPoint, BPoly.Position[1]), VSub(BCenterPoint, BPoly.Position[2]), VSub(BCenterPoint, BPoly.Position[0])));

           if (VSize(VSub(ACenterPoint, BCenterPoint)) < (AR + BR))
           {
               
               /*///ポリゴン同士のの当たり判定かつ押し返し
               if (IsTriangle_Joint_Triangle(MovePoly.Position[0], MovePoly.Position[1], MovePoly.Position[2], NotMovePoly.Position[0], NotMovePoly.Position[1], NotMovePoly.Position[2]))
               {
                   return true;
             
                }*/

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
    for (int i = 0; i < CapsuleCollision.size(); i++)
    {
       if(CapsuleCollision[i].GetStartName() == frameName)
       {
           return CapsuleCollision[i];
       }
    }
    return Capsule();
}

void Character::DrawSearchCapusle(const char* frameName)
{
    for (int i = 0; i < CapsuleCollision.size(); i++)
    {
        if (CapsuleCollision[i].GetStartName() == frameName)
        {
            DrawCapsule3D(CapsuleCollision[i].GetStartPos(), CapsuleCollision[i].GetEndPos(), CapsuleCollision[i].GetRSize(), 8, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
            break;
        }
    }
}



void Character::Turn(VECTOR RotatePower)
{
   
    Dir = VAdd(Dir, RotatePower);
    // 角度をY軸回転にセット
    MV1SetRotationXYZ(Img,Dir);
    MV1SetRotationXYZ(NextImg, Dir);

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
