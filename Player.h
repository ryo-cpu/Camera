#pragma once
#include"Character.h"
class Player :public Character
{
    int Hp;
    int Power;
    bool InJump;
    VECTOR Grand;
    VECTOR G = VGet(0, -1, 0);
    VECTOR JumpPower = VGet(0, 30, 0);
public:
    bool Input();
    void Update() override;


};

