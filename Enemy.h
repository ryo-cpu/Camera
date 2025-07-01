#pragma once
#include"Character.h"
#include <algorithm>
class Enemy: public Character
{
    Character *Target;
public:
    enum Motion {Ran, Down, Rolling, Kick, Hit };

    void SetTarget(Character &target);
    VECTOR SearchTarget();

    void Update()override;

};

