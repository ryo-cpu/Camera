#include "Capsule.h"
#include"ModelCheckers.h"

VECTOR Capsule::GetStartPos() const
{
    return StartPos;
}

VECTOR Capsule::GetEndPos() const
{
    return EndPos;
}

void Capsule::SetStartPos(VECTOR pos)
{
    StartPos = pos;
}
void Capsule::SetEndPos(VECTOR pos)
{
    EndPos = pos;
}
float Capsule::GetRSize() const
{
    return RSize;
}
void Capsule::SetRSize(float size)
{
    RSize = size;
}
bool Capsule::Survey(const Collision& C1, const Collision& C2)
{
    return false;
}
bool Capsule::Survey(const Capsule& C1, const Capsule& C2)
{
    float Rsum = C1.GetRSize() + C2.GetRSize();
    if (Segment_Segment_MinLength(C1.StartPos, C1.EndPos, C2.StartPos, C2.EndPos) >= Rsum)
    {
        return false;
    }
    return true;
}
VECTOR Capsule::PushBack(const Capsule& Move, const Capsule& Immodility)
{
    VECTOR pushback = VGet(0, 0, 0); {};

    VECTOR StartPoint, EndPoint,Norm;

    StartPoint = Move.GetStartPos();
    EndPoint =   Move.GetEndPos();
    Norm = VNorm(VSub(EndPoint, StartPoint));

    float Rsum = Move.GetRSize() + Immodility.GetRSize();
    ////線として調べため半径の合計分延長
    StartPoint = VAdd(StartPoint,VScale(Norm,Rsum));
    EndPoint = VAdd(EndPoint, VScale(Norm, -Rsum));///逆側に伸ばすのでマイナス


    
    //////並行時の分岐 二点とimmodilityの近さを比較して並行かどうか調べる
    ModelCheckers Tmp;

    VECTOR Shadow_StartPos = VAdd(Immodility.GetStartPos(), Tmp.VProject(StartPoint, Immodility.GetStartPos(), Immodility.GetEndPos()));
    VECTOR P1 = VSub(StartPoint,Shadow_StartPos);
    VECTOR Shadow_EndPos = VAdd(Immodility.GetStartPos(), Tmp.VProject(EndPoint, Immodility.GetStartPos(), Immodility.GetEndPos()));
    VECTOR P2= VSub(EndPoint, Shadow_EndPos);
    pushback = VSize(P1) >= VSize(P2) ? P1 : P2;
    if (P1.x * P2.x < 0 && P1.y * P2.y < 0 && P1.z * P2.z < 0)
    {
        pushback = VScale(pushback, -1);
    }
 
    //if (Tmp.IsParallel(Immodility.GetStartPos(), Immodility.GetEndPos(),StartPoint,EndPoint))
    //{
    //    VECTOR ImmodilityPoint = Tmp.VProject(StartPoint, Immodility.GetStartPos(), Immodility.GetEndPos());
    //    VECTOR ShadowPos = VAdd(Immodility.GetStartPos(), ImmodilityPoint);
    //    float StratShadow = VSize(VSub(StartPoint, ShadowPos));
    //    ////並行な場合垂直に返せばいいので
    //    return VSub(StartPoint, ShadowPos);
    //}
  
    

    ///外積を取り交差を確認

    ///交差しないなら分岐





    return pushback;
}
void Capsule::Update(int Model)
{
    /////フレームに追従する
    if (StartFrameName!=NULL&&EndFrameName!=NULL&&Model!=0)
    {
      
        int StartIndex = MV1SearchFrame(Model,StartFrameName);
        int EndIndex = MV1SearchFrame(Model, EndFrameName);

        if (StartIndex >= 0&&EndIndex>=0)
        {
            StartPos= MV1GetFramePosition(Model, StartIndex);
            EndPos = MV1GetFramePosition(Model, EndIndex);
        }

    }
}
void  Capsule::Update(VECTOR Move)
{
    StartPos = VAdd(StartPos, Move);
}
void Capsule::SetStartFrameName(char* Name)
{
    StartFrameName = Name;
   
}

void Capsule::SetStartFrameName(char* Name, int Model)
{
    SetStartFrameName(Name);
    int HipIndex = MV1SearchFrame(Model, Name);
    if (HipIndex >= 0)
    {
        StartPos = MV1GetFramePosition(Model, HipIndex);
    }

}



void Capsule::SetEndFrameName(char* Name)
{
    EndFrameName = Name;

}

void Capsule::SetEndFrameName(char* Name, int Model)
{
    SetEndFrameName(Name);
    int HipIndex = MV1SearchFrame(Model, Name);
    if (HipIndex >= 0)
    {
        EndPos = MV1GetFramePosition(Model, HipIndex);
    }
}

void Capsule::SetFrameName(char* StartName, char* EndName)
{
    SetStartFrameName(StartName);
    SetEndFrameName(EndName);
}
