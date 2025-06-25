#include "Player.h"


bool Player::Input()
{
    bool isInput = false;
    if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
    {
        SetAnimType(3);
    }
    return isInput;
}

void Player::Update()
{
	
    AnimUpdate();
    ////à íuÇÃçXêV
    SetPos(VAdd(Pos, Move));

}
