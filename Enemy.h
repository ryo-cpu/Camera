#pragma once
#include"Character.h"
#include <algorithm>
const float MaxTurn = 0.1f;
class Enemy: public Character
{
    Character *Target;
    bool IsMotion;
    int MotionType;
public:
    Enemy();
    enum Motion {Ran,Junp, Dance, ArmSwing,Dwon, bat, Hit };
    enum AttackMotion { Tackle, DownArmSwing, tink, hit_stop };
    void SetTarget(Character &target);
    VECTOR SearchTarget();
    Sphere_Collision GetAttackCollison();
    void SetMoveType(int movetype);
    int GetMoveType();
    ///‚±‚¤‚Ç‚¤////
    void SelectMove();
    bool TackleAttack(VECTOR targetPos);
    bool ArmSwingDown(VECTOR targetPos);
    bool Tink();
    bool Hit_Stop();
   

    void Update(float deltaTime)override;

};

