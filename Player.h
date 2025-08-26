#pragma once
#include"Character.h"



class Player :public Character
{
   

    bool InJump;
    bool IsHit;
    float Speed;
    bool InSpecialMove;
    VECTOR SpecialTaget;
    VECTOR Grand;
    VECTOR G = VGet(0, -10, 0);
    VECTOR JumpPower = VGet(0, 30, 0);
    Sphere_Collision AttackCollison;
public:
    Player();
    enum Motion { Stop, Ran, Down, Rolling, Kick, Hit };
    bool Input();
    void Update(float deltaTime) override;
    Sphere_Collision GetAttackCollison();
    void SetAttackCollison(VECTOR Pos, float size);
    void SetGrand(VECTOR grand);
    bool GetIsHit();
    void SetIsHit(bool ishit);
    bool GetInSpecialMove();
    void SpecialMove(float deltaTime);
    void SetInSpecialMove(bool inSpecialMove,VECTOR Taget);
  



};

