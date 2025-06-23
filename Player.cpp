#include "Player.h"


bool Player::GetInput()
{
	return IsInput;
}

void Player::Update()
{
	
    AnimUpdate();
    ////ˆÊ’u‚ÌXV
    SetPos(VAdd(Pos, Move));

}
