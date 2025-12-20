#pragma once
#include"Camera.h"
#include"Character.h"
const int screenW = 1600;
const int screenH = 900;
class Bar
{
private:
    int handleColor;
    int backColor;
    int fillColor;

    bool handleEnabled;
    Character *Owner;
    VECTOR position;

    VECTOR handleSize;
    VECTOR backSize;

    VECTOR handlePosition = {};
    bool isDraw;
    float value;
    float maxValue = 1;
    float minValue = 0; 
    float Scale;

public:
    Bar(Character *owner);
    ~Bar();
    void SetValue(float setValue);
    void SetMaxValue(float setMaxValue);
    void SetMinValue(float setMinValue);
    float GetValue();
    void SetPosition(float setPositionX, float setPositionY);
    void SetBackSize(float setBackWidth, float setBackHeight);
    void SetHandleSize(float setHandleWidth, float setHandleHeight);
    void SetBackColor(unsigned int setBackColor);
    void SetFillColor(unsigned int setFillColor);
    bool inScreen();
    bool CheakIsDraw(Character CheakTarget,Camera camera);

    void Update(Camera camera);
    void Draw();
};

