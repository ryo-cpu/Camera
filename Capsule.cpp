#include "Capsule.h"
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
float Capsule::GetSize() const
{
    return Size;
}
void Capsule::SetSize(float size)
{
    Size = size;
}
bool Capsule::Survey(const Collision& C1, const Collision& C2)
{
    return false;
}
bool Capsule::Survey(const Capsule& C1, const Capsule& C2)
{
    float Rsum = C1.GetSize() + C2.GetSize();
    if (Segment_Segment_MinLength(C1.StartPos, C1.EndPos, C2.StartPos, C2.EndPos) >= Rsum)
    {
        return false;
    }
    return true;
}
void Capsule::Update(int Model)
{
    /////ƒtƒŒ[ƒ€‚É’Ç]‚·‚é
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

void Capsule::SetEndFrameName(char* Name)
{
    EndFrameName = Name;

}

void Capsule::SetFrameName(char* StartName, char* EndName)
{
    SetStartFrameName(StartName);
    SetEndFrameName(EndName);
}
