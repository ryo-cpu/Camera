#pragma once
#include"DxLib.h"
#include<cmath>
#include<vector>
#include<algorithm>
 class ModelCheckers
{
public:
   void ShowTextureName(int Model);
   void ShowFrameName(int Model);
   VECTOR VMax(VECTOR V1, VECTOR V2);
   /// @brief 三角形に使うように3つ
   /// @param V1 
   /// @param V2 
   /// @param V3 
   /// @return 
   VECTOR VMax(VECTOR V1, VECTOR V2,VECTOR V3);
   VECTOR VMin(VECTOR V1, VECTOR V2);
   VECTOR VMin(VECTOR V1, VECTOR V2, VECTOR V3);
   /// @brief 正射影ベクトルの終点を返す　垂線を下した先を示す
   /// @param CheckPoint 
   /// @param StartGround 
   /// @param EndGround 
   /// @return 
   VECTOR VProject(VECTOR CheckPoint,VECTOR StartGround,VECTOR EndGround);
   bool IsTriangle_Joint_Sphere(VECTOR T1, VECTOR T2, VECTOR T3, VECTOR SphereP, float R);
   bool IsTriangle_Joint_Triangle(VECTOR TA1, VECTOR TA2, VECTOR TA3, VECTOR TB1, VECTOR TB2, VECTOR TB3);
   void TProject(const VECTOR Triangle[3], const VECTOR& Axis, float& OutMin, float& OutMax);
};

