#pragma once
#include"DxLib.h"
#include "Collision.h"


class Capsule : public Collision
{ 
    float Size;
    VECTOR StartPos,EndPos;
    char* EndFrameName;
    char* StartFrameName;

public:
    VECTOR   GetStartPos()const;
    VECTOR   GetEndPos()const;
    void     SetStartPos(VECTOR pos);
    void     SetEndPos(VECTOR pos);
    float    GetSize();
    void     SetSize(float size);
    virtual bool Survey(const Collision& C1, const Collision& C2)override;
    /// @brief ÉÇÉfÉãÇ…Ç≠Ç¡Ç¬Ç¢ÇƒÇ¢ÇÈÇ∆Ç´Ç…í«è]Ç∑ÇÈÇÊÇ§
    /// @param Model 
    void Update(int Model);
    void Update(VECTOR Move);

    void SetStartFrameName(char* Name);
    void SetEndFrameName(char* Name);
    void SetFrameName(char* StartName,char* EndName);


   
};

