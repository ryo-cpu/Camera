#pragma once
#include"DxLib.h"
#include"Character.h"
class Bar
{
private:
    int handleColor;
    int backColor;
    int fillColor;

    bool handleEnabled;

    VECTOR position;

    VECTOR handleSize;
    VECTOR backSize;

    VECTOR handlePosition = {};

    float value;
    float maxValue = 1;
    float minValue = 0;
public:
    void SetValue(float setValue);
    void SetMaxValue(float setMaxValue);
    void SetMinValue(float setMinValue);
    float GetValue();
    void SetPosition(float setPositionX, float setPositionY);
    void SetBackSize(float setBackWidth, float setBackHeight);
    void SetBackColor(int setBackColor);
    void SetFillColor(int setFillColor);

    void Update(Character Owner);
    void Draw();
};

