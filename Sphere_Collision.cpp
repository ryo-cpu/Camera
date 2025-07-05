#include "Sphere_Collision.h"


VECTOR Sphere_Collision::GetPos()
{
    return Pos;
}

void Sphere_Collision::SetPos(VECTOR pos)
{
    Pos = pos;
}

float Sphere_Collision::GetSphereSize()
{
    return Size;
}

void Sphere_Collision::SetSphereSize(float sphereSize)
{
    Size = sphereSize;
}

bool Sphere_Collision::Collison(const Sphere_Collision& S1, const Sphere_Collision& S2)
{
    VECTOR Distance = VSub(S1.Pos, S2.Pos);
    
    if (VSize(Distance) <= (S1.Size + S2.Size))
    {
        return true;
    }
    else
    {
       return false;
    }
}


