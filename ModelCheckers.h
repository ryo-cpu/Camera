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
   /// @brief 平行か調べる
   /// @param A1 
   /// @param A2 
   /// @param B1 
   /// @param B2 
   /// @return 
   bool IsParallel(VECTOR A1, VECTOR A2, VECTOR B1, VECTOR B2);
   /// @brief 三角形と球の検知
   /// @param T1 
   /// @param T2 
   /// @param T3 
   /// @param SphereP 
   /// @param R 
   /// @return 
   bool IsTriangle_Joint_Sphere(VECTOR T1, VECTOR T2, VECTOR T3, VECTOR SphereP, float R);
   /// @brief 三角形同士の検知
   /// @param TA1 
   /// @param TA2 
   /// @param TA3 
   /// @param TB1 
   /// @param TB2 
   /// @param TB3 
   /// @return 
   bool IsTriangle_Joint_Triangle(VECTOR TA1, VECTOR TA2, VECTOR TA3, VECTOR TB1, VECTOR TB2, VECTOR TB3);
   void TProject(const VECTOR Triangle[3], const VECTOR& Axis, float& OutMin, float& OutMax);
   bool IsModel_Joint_Model(const int& M1, const int& M2, float M1_R);

};

