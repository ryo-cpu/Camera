#include "UIBar.h"
const unsigned int HPBackColor = GetColor(200, 200, 200);
const unsigned int HPBaseColor = GetColor(100, 240, 100);
const int DefaultUIBarSizeX = 500;
const int DefaultUIBarSizeY = 100;

UIBar::UIBar(Character* owner)
{
    Owner = owner;
    if (Owner)
    {
        value = Owner->GetHp();

        maxValue = Owner->GetMaxHp();
        minValue = 0;
        SetHandleSize(DefaultUIBarSizeX, DefaultUIBarSizeY);
        SetBackSize(DefaultUIBarSizeX, DefaultUIBarSizeY);
        SetBackColor(HPBackColor);
        SetFillColor(HPBaseColor);
    }

    else
    {
     
        SetHandleSize(100, 20);
        SetBackSize(100, 20);
        SetBackColor(HPBackColor);
        SetFillColor(HPBaseColor);
    }
}

UIBar::~UIBar()
{
}
void UIBar::SetValue(float setValue)
{
    value = setValue;
}

void UIBar::SetMaxValue(float setMaxValue)
{
    maxValue = setMaxValue;
}

void UIBar::SetMinValue(float setMinValue)
{
    minValue = setMinValue;
}

float UIBar::GetValue()
{
    return value;
}

void UIBar::SetPosition(float setPositionX, float setPositionY)
{
    position = VGet(setPositionX, setPositionX, 0);
}

void UIBar::SetBackSize(float setBackWidth, float setBackHeight)
{
    backSize = VGet(setBackWidth, setBackHeight, 0);
}

void UIBar::SetHandleSize(float setHandleWidth, float setHandleHeight)
{
    handleSize = VGet(setHandleWidth, setHandleHeight, 0);
}

void UIBar::SetBackColor(unsigned int  setBackColor)
{
    backColor = setBackColor;
}

void UIBar::SetFillColor(unsigned int setFillColor)
{
    fillColor = setFillColor;
}

bool UIBar::SetIsDraw()
{
    return false;
}

void UIBar::ResetOwner(Character* owner)
{
    Owner = owner;
    if (Owner)
    {
        value = Owner->GetHp();

        maxValue = Owner->GetMaxHp();
        minValue = 0;
        position = VGet(0, 0, 0);
        SetHandleSize(DefaultUIBarSizeX, DefaultUIBarSizeY);
        SetBackSize(DefaultUIBarSizeX, DefaultUIBarSizeY);
        SetBackColor(HPBackColor);
        SetFillColor(HPBaseColor);
    }

    else
    {
        position = VGet(0, 0, 0);
        SetHandleSize(100, 20);
        SetBackSize(100, 20);
        SetBackColor(HPBackColor);
        SetFillColor(HPBaseColor);
    }

}








void UIBar::Update()
{
    
    value = Owner->GetHp();
   
}

void UIBar::Draw()
{
    float Proportion;
    if (value > 0)
    {
        Proportion = value / maxValue;
    }
    else
    {
        Proportion = 0;
    }
   
    DrawBox(position.x, position.y, position.x + handleSize.x, position.y + handleSize.y,HPBackColor, true);
    DrawBox(position.x, position.y, position.x + handleSize.x * Proportion, position.y + handleSize.y, HPBaseColor, true);

}