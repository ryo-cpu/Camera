#pragma once
#include "Camera.h"
#include "Character.h"


class UIBar
{
private:
    int handleColor;
    int backColor;
    int fillColor;

    bool handleEnabled;
    Character* Owner;
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
    UIBar(Character* owner);
    UIBar(Character* owner,float posX,float posY);
    ~UIBar();
    void SetValue(float setValue);
    void SetMaxValue(float setMaxValue);
    void SetMinValue(float setMinValue);
    float GetValue();
    void SetPosition(float setPositionX, float setPositionY);
    void SetBackSize(float setBackWidth, float setBackHeight);
    void SetHandleSize(float setHandleWidth, float setHandleHeight);
    void SetBackColor(unsigned int setBackColor);
    void SetFillColor(unsigned int setFillColor);
    bool SetIsDraw();
    /// <summary>
    /// オーナーの変更または初期化
    /// </summary>
    /// <param name="owner"></param>
    void ResetOwner(Character* owner);
    void Update();
    /// <summary>
	/// 値をHPでないときに更新するための関数
    /// </summary>
    /// <param name="value"></param>
    void Update(int value);
    void Draw();

};

