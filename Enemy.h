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
    Enemy(int img);

    ~Enemy();
    enum Motion {Run,Jump, Dance, ArmSwing,Down, Bat, Hit };
    enum AttackMotion { Tackle, DownArmSwing,tink,hit_stop};
    void SetTarget(Character &target);
    VECTOR SearchTarget();
    Sphere_Collision GetAttackCollision();
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

