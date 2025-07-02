#pragma once
#include"Character.h"
#include <algorithm>
const float MaxTurn = 1.0f;
class Enemy: public Character
{
    Character *Target;
    bool IsMotion;
    int MotionType;
public:
    enum Motion {Ran,Junp, Down, Rolling, Kick, Hit };

    void SetTarget(Character &target);
    VECTOR SearchTarget();

    bool TackleAttack(VECTOR targetPos);
    bool ArmSwingDown(VECTOR targetPos);

    void Update()override;

};

