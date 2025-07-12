#include "Bsr.h"
const unsigned int BackColor = GetColor(200, 200, 200);
const unsigned int BaseColor = GetColor(200, 200, 100);
const unsigned int HalfColor = GetColor(200, 200, 100);
const unsigned int QuarterColor = GetColor(200, 200, 100);


Bar::Bar(const Character &owner)
{
    Owner = owner;
    value = Owner.GetHp();
    maxValue = Owner.GetMaxHp();
    minValue = 0;
    position=ConvWorldPosToScreenPos(Owner.GetPos());
    SetHandleSize(100, 20);
    SetBackSize(100, 20);
    SetBackColor(BackColor);
    SetFillColor(BaseColor);
    
}

void Bar::SetValue(float setValue)
{
    value = setValue;
}

void Bar::SetMaxValue(float setMaxValue)
{
    maxValue = setMaxValue;
}

void Bar::SetMinValue(float setMinValue)
{
    minValue = setMinValue;
}

float Bar::GetValue()
{
    return value;
}

void Bar::SetPosition(float setPositionX, float setPositionY)
{
    position = VGet(setPositionX, setPositionX, 0);
}

void Bar::SetBackSize(float setBackWidth, float setBackHeight)
{
    backSize = VGet(setBackWidth, setBackHeight, 0);
}

void Bar::SetHandleSize(float setHandleWidth, float setHandleHeight)
{
    handleSize= VGet(setHandleWidth, setHandleHeight, 0);
}

void Bar::SetBackColor(unsigned int  setBackColor)
{
    backColor = setBackColor;
}

void Bar::SetFillColor(unsigned int setFillColor)
{
    fillColor = setFillColor;
}

bool Bar::inScreen()
{
    VECTOR screenPos = ConvWorldPosToScreenPos(Owner.GetPos());
    
    return screenPos.z = 1.0f &&
        screenPos.x >= 0 && screenPos.x <= screenW &&
        screenPos.y >= 0 && screenPos.y <= screenH;

}


void Bar::Update(Character Owner)
{
    value = Owner.GetHp();
    position = ConvWorldPosToScreenPos(Owner.GetPos());

}

void Bar::Draw()
{
    if (inScreen())
    {
        float MaxX = position.x + backSize.x;
        DrawBox(position.x-(backSize.x/2), position.y, position.x + 1000, position.y - 200, fillColor, true);
        DrawBox(position.x, position.y, MaxX, position.y + backSize.y, BackColor, true);
    }
  

}
