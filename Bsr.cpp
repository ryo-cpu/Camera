#include "Bsr.h"
const unsigned int BackColor = GetColor(200, 200, 100);
const unsigned int BaseColor = GetColor(200, 200, 100);
const unsigned int HalfColor = GetColor(200, 200, 100);
const unsigned int QuarterColor = GetColor(200, 200, 100);


Bar::Bar(Character Owner)
{

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


void Bar::Update(Character Owner)
{
    value = Owner.GetHp();
}

void Bar::Draw()
{
    float MaxX = position.x+backSize.x;
    DrawBox(position.x, position.y,MaxX, position.y, fillColor, false);
    DrawBox(position.x, position.y, MaxX, position.y, BackColor, false);

}
