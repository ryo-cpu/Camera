#pragma once
#include"Character.h"
#include<cmath>
class Player :public Character
{
    bool InJump;
    float Speed;
    VECTOR Grand;
    VECTOR G = VGet(0, -1, 0);
    VECTOR JumpPower = VGet(0, 30, 0);
public:
    bool Input();
    void Update() override;


};

