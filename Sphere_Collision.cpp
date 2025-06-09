#include "Sphere_Collision.h"

Sphere_Collision::Sphere_Collision()
{
}

Sphere_Collision::Sphere_Collision(VECTOR pos)
{
    Pos = pos;
    Size = 0;
}

Sphere_Collision::Sphere_Collision(VECTOR pos, float size)
{
    Pos = pos;
    Size = size;
}

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

bool Sphere_Collision::Collison(Sphere_Collision S1, Sphere_Collision S2)
{
    
        VECTOR Distance = VSub(S1.GetPos(), S2.GetPos());

        if (VSize(Distance) < S1.Size + S2.Size)
        {
            return true;
        }
        else
        {
            false;
        }
    

}
