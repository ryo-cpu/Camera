#pragma once
#include"DxLib.h"
#include "Collision.h"


class Capsule : public Collision
{ 
    float RSize;
    VECTOR StartPos,EndPos;
    char* EndFrameName;
    char* StartFrameName;

public:
    Capsule(char* startName, char* endName, float rsize);
    Capsule(char* startName, char* endName, float rsize,int Model);

    VECTOR   GetStartPos()const;
    VECTOR   GetEndPos()const;
    void     SetStartPos(VECTOR pos);
    void     SetEndPos(VECTOR pos);
    float    GetRSize()const;
    void     SetRSize(float size);
    virtual bool Survey(const Collision& C1, const Collision& C2)override;
    bool Survey(const Capsule&C1, const Capsule& C2);
    VECTOR PushBack(const Capsule& Move, const Capsule& Immodility);
        
    /// @brief ÉÇÉfÉãÇ…Ç≠Ç¡Ç¬Ç¢ÇƒÇ¢ÇÈÇ∆Ç´Ç…í«è]Ç∑ÇÈÇÊÇ§
    /// @param Model 
    void Update(int Model);
    void Update(VECTOR Move);

    void SetStartFrameName(char* Name);
    void SetStartFrameName(char* Name ,int Model);
    void SetEndFrameName(char* Name);
    void SetEndFrameName(char* Name,int Model);

    void SetFrameName(char* StartName,char* EndName);


   
};

