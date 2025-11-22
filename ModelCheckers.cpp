#include "ModelCheckers.h"

void ModelCheckers::ShowTextureName(int Model)
{
   int num= MV1GetTextureNum(Model);
   SetFontSize(12);
   for (int i = 0; i < num; i++)
   {
       DrawFormatString(0, i*10, GetColor(255, 255, 255), "Name                  %s", MV1GetTextureName(Model, i));
   }
}

void ModelCheckers::ShowFrameName(int Model)
{
    int num = MV1GetFrameNum(Model);
    SetFontSize(12);
    for (int i = 0; i < num; i++)
    {
        DrawFormatString(0, i * 10, GetColor(255, 255, 255), "Name                  %s", MV1GetFrameName(Model, i));
    }
}

