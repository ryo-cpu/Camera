#pragma once
#include"Character.h"
#include <algorithm>
const float MaxTurn = 1.0f;
class Enemy: public Character
{
    Character *Target;
    bool IsMotion;
    int MotionType;
    Sphere_Collision AttackCollison;
public:
    Enemy();
    enum Motion {Ran,Junp, Down, Rolling, Kick, Hit };

    void SetTarget(Character &target);
    VECTOR SearchTarget();
    ///‚±‚¤‚Ç‚¤////
  
    bool TackleAttack(VECTOR targetPos);
    bool ArmSwingDown(VECTOR targetPos);
    Sphere_Collision GetAttackCollison();

    void Update()override;

};

