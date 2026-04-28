#include "Capsule.h"
#include "ModelCheckers.h"

Capsule::Capsule(char* startName, char* endName, float rsize)
{
    SetFrameName(startName, endName);
    SetRSize(rsize);
}

Capsule::Capsule(char* startName, char* endName, float rsize, int Model)
{
    SetStartFrameName(startName, Model);
    SetEndFrameName(endName, Model);
    SetRSize(rsize);

}
Capsule::Capsule(VECTOR startPos, VECTOR endPos, float rsize)
{
    StartPos = startPos;
    EndPos = endPos;
    SetRSize(rsize);
}

Capsule::Capsule()
{

}

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

    float Rsum = Move.GetRSize() + Immodility.GetRSize();


    
    //////並行時の分岐 二点とimmodilityの近さを比較して並行かどうか調べる
    ModelCheckers Tmp;

    VECTOR pA = Move.GetStartPos();
    VECTOR qA = Move.GetEndPos();

    VECTOR pB = Immodility.GetStartPos();
    VECTOR qB = Immodility.GetEndPos();

    // A始点 → B線分 最近点
    VECTOR c1 = VAdd(pB, Tmp.VProject(pA, pB, qB));
    VECTOR v1 = VSub(pA, c1);

    // A終点 → B線分 最近点
    VECTOR c2 = VAdd(pB, Tmp.VProject(qA, pB, qB));
    VECTOR v2 = VSub(qA, c2);

    // 短い方
    VECTOR diff = (VSize(v1) < VSize(v2)) ? v1 : v2;

    VECTOR dir = VNorm(diff);
    float dist = VSize(diff);

    pushback = VScale(dir, Rsum - dist);

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
    EndPos = VAdd(EndPos, Move);

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
        int T = MV1GetFrameParent(Model, HipIndex);
        
       std::string N=MV1GetFrameName(Model, T);
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

char* Capsule::GetStartName()
{
    return StartFrameName;
}
