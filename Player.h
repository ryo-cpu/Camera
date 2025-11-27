#pragma once
#include"Character.h"
#include"Camera.h"

const int MaxSpGauge = 100;
const float MaxSpeed =10.0f;

class Player :public Character
{
   

    bool InJump;
    bool IsHit;
    bool IsActiveInput;
    float Speed;
    bool InSpecialMove;
    VECTOR SpecialTaget;
    VECTOR Grand;
    VECTOR G = VGet(0, -10, 0);
    VECTOR JumpPower = VGet(0, 30, 0);
    float LastDamageTime;
    bool InRolling;
    bool isTurn;
    int SpGauge = 0;
   
public:
    Player();
    enum Motion { Stop, Ran, Down, Roll, Kick, Hit };
    bool Input(Camera &camera);
    void Update(float deltaTime) override;
    void SetGrand(VECTOR grand);
    bool GetIsHit();
    void SetIsHit(bool ishit);
    bool GetInSpecialMove();
    void SpecialMove(float deltaTime);
    void SetInSpecialMove(bool inSpecialMove);
    void SetLastDamageTime();
    float GetLastDamageTime();
    bool Rolling();
    void AddSpGauge(int add);
    bool GetTurn();
};

