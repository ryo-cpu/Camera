#include "Player.h"

void Player::Update()
{

    ////位置の更新
    SetPos(VAdd(Pos, Move));

}
