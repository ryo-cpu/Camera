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
    VECTOR GRund;
    VECTOR G = VGet(0, -10, 0);
    VECTOR JumpPower = VGet(0, 30, 0);
    float LastDamageTime;
    bool InRolling;
    bool isTurn;
    int SpGauge = 0;
    XINPUT_STATE* InputState;

   
public:
    Player();
    Player(int img);

    ~Player();
    enum Motion { Stop, Run, Down, Roll, Kick, Hit };
    bool Input(Camera &camera);
    void Update(float deltaTime) override;
    void SetGRund(VECTOR gRund);
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
    XINPUT_STATE* GetInputState();
};

