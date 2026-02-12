#include "Bar.h"
#include<iostream>
const unsigned int BackColor = GetColor(200, 200, 200);
const unsigned int BaseColor = GetColor(100, 240, 100);
const unsigned int HalfColor = GetColor(200, 200, 100);
const unsigned int QuarterColor = GetColor(200, 200, 100);
const int DefaultBarSizeX = 500;
const int DefaultBarSizeY = 100;


Bar::Bar(Character *owner)
{
    Owner = owner;
    if (Owner)
    {
        value = Owner->GetHp();

        maxValue = Owner->GetMaxHp();
        minValue = 0;
        position = ConvWorldPosToScreenPos(Owner->GetPos());
        SetHandleSize(DefaultBarSizeX , DefaultBarSizeY);
        SetBackSize(DefaultBarSizeX , DefaultBarSizeY);
        SetBackColor(BackColor);
        SetFillColor(BaseColor);
    }
   
    else
    {
        position =VGet(0,0,0);
        SetHandleSize(100, 20);
        SetBackSize(100, 20);
        SetBackColor(BackColor);
        SetFillColor(BaseColor);
    }
    
}

Bar::~Bar()
{
    delete Owner;
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
    VECTOR screenPos = ConvWorldPosToScreenPos(Owner->GetPos());
    
    return screenPos.z = 1.0f &&
        screenPos.x >= 0 && screenPos.x <= screenW &&
        screenPos.y >= 0 && screenPos.y <= screenH;

}

bool Bar::CheakIsDraw(Character CheakTarget,Camera camera)
{
    float distance = VSize(VSub(camera.GetPos(), CheakTarget.GetPos()));
    float scale = 1.0f / (distance / 100);  // 遠くなると小さく
    // モデルの大きさに応じて調整
    float Mscale = scale *CheakTarget.GetScale();
    VECTOR C1=CheakTarget.GetPos(), C2=CheakTarget.GetPos();
   

    C1= ConvWorldPosToScreenPos(C1);
    C2 = ConvWorldPosToScreenPos(C2);
    C1 = VAdd(C1, VGet(-500*Mscale, -1500*Mscale, 0));////大体の大きさ
    C2 = VAdd(C2, VGet(500*Mscale, 50*Mscale, 0));////大体の大きさ
    

    // UIの矩形座標（2D）
    float uiLeft = position.x - (backSize.x / 2);
    float uiRight = position.x + (backSize.x / 2);
    float uiTop = position.y;
    float uiBottom = position.y + backSize.y;

    // モデルの2Dスクリーン上の矩形
    float modelLeft = C1.x;
    float modelRight = C2.x;
    float modelTop = C1.y;
    float modelBottom = C2.y;

    return (modelRight < uiLeft || modelLeft > uiRight || modelBottom < uiTop || modelTop > uiBottom);
}

void Bar::ResetOwner(Character* owner)
{
    Owner = owner;
    if (Owner)
    {
        value = Owner->GetHp();

        maxValue = Owner->GetMaxHp();
        minValue = 0;
        position = ConvWorldPosToScreenPos(Owner->GetPos());
        SetHandleSize(DefaultBarSizeX, DefaultBarSizeY);
        SetBackSize(DefaultBarSizeX, DefaultBarSizeY);
        SetBackColor(BackColor);
        SetFillColor(BaseColor);
    }

    else
    {
        position = VGet(0, 0, 0);
        SetHandleSize(100, 20);
        SetBackSize(100, 20);
        SetBackColor(BackColor);
        SetFillColor(BaseColor);
    }

}






void Bar::Update(Camera camera)
{
    float distance =VSize(VSub(camera.GetPos() ,Owner->GetPos()));
    float scale = 1.0f /(distance/100);  // 遠くなると小さく
      // モデルの大きさに応じて調整
    float Mscale = scale * Owner->GetScale();
   
    Scale = Mscale;
    
    SetHandleSize(DefaultBarSizeX  * Mscale, DefaultBarSizeY * Mscale);
    SetBackSize(DefaultBarSizeX  * Mscale, DefaultBarSizeY * Mscale);
    value = Owner->GetHp();
    position = ConvWorldPosToScreenPos(Owner->GetPos());
   
}

void Bar::Draw()
{
    if (inScreen())
    {
        float Proportion;
        if (value>0)
        {
            Proportion = value / maxValue;
        }
        else
        {
            Proportion = 0;
        }
        
        float StartX = position.x - (backSize.x / 2);
        float MaxX = position.x + backSize.x;
        DrawBox(StartX, position.y, StartX+backSize.x, position.y + backSize.y, BackColor, true);
        DrawBox(StartX, position.y,StartX+(backSize.x*Proportion), position.y + backSize.y, fillColor, true);

    }
  

}
