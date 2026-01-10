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
float Capsule::GetSize()
{
    return Size;
}
void Capsule::SetSize(float size)
{
    Size = size;
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