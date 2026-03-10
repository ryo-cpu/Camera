#pragma once
#include"Camera.h"
#include"Character.h"
const int screenW = 1600;
const int screenH = 900;
class Bar
{
/// <summary>
/// 
/// </summary>
private:
    int handleColor;
    int backColor;
    int fillColor;

    bool handleEnabled;
    Character *Owner;
    /// <summary>
    /// キャラクターの座標３D
    /// </summary>
    VECTOR position;
    /// <summary>
    /// 3Dのoffset
    /// </summary>
    VECTOR Offset;

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
    Bar(Character* owner,VECTOR offset3D);

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
    /// <summary>
    /// オーナーの変更または初期化
    /// </summary>
    /// <param name="owner"></param>
    void ResetOwner(Character* owner);
    void ResetOwner(Character* owner,VECTOR offset3d);

    void Update(Camera camera);
    void Draw();
    void SetOffset(VECTOR offset3d);
};

