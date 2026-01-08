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