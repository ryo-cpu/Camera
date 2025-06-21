#include "Player.h"

void Player::Update()
{
    AnimUpdate();
    ////ˆÊ’u‚ÌXV
    SetPos(VAdd(Pos, Move));

}
