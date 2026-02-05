#pragma once
#include"Character.h"
#include <algorithm>
const float MaxTurn = 0.1f;
const int EnemyHP = 300;
const int EnemyAnimSpeed = 20;
class Enemy: public Character
{
    Character *Target;
    bool IsMotion;
    int MotionType;
    VECTOR KnockBack;
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
    void SetKnockBack(VECTOR knockback);
    int GetMoveType();
    ///‚±‚¤‚Ç‚¤////
    void SelectMove();
    bool TackleAttack(VECTOR targetPos);
    bool ArmSwingDown(VECTOR targetPos);
    bool Tink();
    bool Hit_Stop();
   

    void Update(float deltaTime)override;
    void Initial()override;

};

