#pragma once
#include"Character.h"
class Player :public Character
{
    int Hp;
    int Power;

public:

    void Update() override;


};

