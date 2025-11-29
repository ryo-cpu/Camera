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

VECTOR ModelCheckers::VMax(VECTOR V1, VECTOR V2)
{
    return VSize(V1) > VSize(V2) ? V1 : V2;
}

VECTOR ModelCheckers::VMax(VECTOR V1, VECTOR V2, VECTOR V3)
{
    VECTOR MAX = VMax(V1, V2);
    MAX = VMax(MAX, V3);
    return MAX;
}

VECTOR ModelCheckers::VMin(VECTOR V1, VECTOR V2)
{
    return VSize(V1) < VSize(V2) ? V1 : V2;;
}

VECTOR ModelCheckers::VMin(VECTOR V1, VECTOR V2, VECTOR V3)
{
    VECTOR MIN = VMin(V1, V2);
    MIN = VMin(MIN, V3);
    return MIN;
}

VECTOR ModelCheckers::VProject(VECTOR CheckPoint, VECTOR StartGround, VECTOR EndGround)
{
    VECTOR Ground = VSub(EndGround, StartGround);
    ////CheckPintは引数と別れていると考える　変更しても引数側を改変しない
    CheckPoint = VSub(CheckPoint, StartGround);
    VECTOR  Proj = VScale(Ground, (VDot(CheckPoint, Ground) / VDot(Ground, Ground)));
    Proj = VAdd(Proj, StartGround);
    return Proj;
}

bool ModelCheckers::IsTriangle_Joint_Sphere(VECTOR T1, VECTOR T2, VECTOR T3, VECTOR SphereP, float R)
{
    ////階層分けによって計算を減らす
    bool isJoint = false;

    VECTOR PT1 = VSub(T1, SphereP);
    VECTOR PT2 = VSub(T2, SphereP);
    VECTOR PT3 = VSub(T3, SphereP);
    VECTOR Min = VMin(PT1, PT2, PT3);
    if (VSize(Min) >= R)
    {
     
        VECTOR T1T2 = VSub(SphereP,VProject(SphereP, T1, T2));
        VECTOR T1T3 = VSub(SphereP, VProject(SphereP, T1, T3));
        VECTOR T2T3 = VSub(SphereP, VProject(SphereP, T2, T3));

     
        Min = VMin(T1T2,T1T3,T2T3);
        if (VSize(Min) >= R)
        {
            ///法線ベクトル
            VECTOR N = VCross(VSub(T1, T2), VSub(T1, T3));
            float nlen = VSize(N);
            if (nlen < 1e-8f) {
                // 退化三角形（面が無い）に到達した場合、安全策としてここでは辺/頂点判定が既に終わっているので false を返す。
                // 実際の要件に応じて true/false を調整してください。
                return false;
            }
            float D = -(T1.x * N.x + T1.y * N.y + T1.z * N.z);

            float Size =fabs(SphereP.x * N.x + SphereP.y * N.y + SphereP.z * N.z + D) / VSize(N);

            return R >= Size;

        }
        else
        {
            return true;
        }
    }
    else
    {
        return true;
    }
}

