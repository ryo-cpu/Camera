#include "ModelCheckers.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
struct Triangle {
    VECTOR v[3];
};

// OBJ読み込み用
struct Vertex {
    float x, y, z;
};
bool LoadOBJTriangles(const std::string& filename, std::vector<Triangle>& tris)
{
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::vector<Vertex> vertices;
    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v")  // 頂点座標
        {
            Vertex v;
            ss >> v.x >> v.y >> v.z;
            vertices.push_back(v);
        }
        else if (prefix == "f") // 三角形面
        {
            int idx[3];
            ss >> idx[0] >> idx[1] >> idx[2];

            Triangle tri;
            for (int i = 0; i < 3; i++)
            {
                Vertex& v = vertices[idx[i] - 1]; // OBJは1始まり
                tri.v[i] = VGet(v.x, v.y, v.z);
            }
            tris.push_back(tri);
        }
    }

    return true;
}


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

bool ModelCheckers::IsTriangle_Joint_Triangle(VECTOR TA1, VECTOR TA2, VECTOR TA3, VECTOR TB1, VECTOR TB2, VECTOR TB3)
{
    VECTOR Triangle_A[3] = {TA1,TA2,TA3};
    VECTOR Triangle_B[3] = {TB1,TB2,TB3};

	VECTOR EdgesA[3] = { VSub(Triangle_A[1],Triangle_A[0]),VSub(Triangle_A[2],Triangle_A[1]),VSub(Triangle_A[0],Triangle_A[2]) };
	VECTOR EdgesB[3] = { VSub(Triangle_B[1],Triangle_B[0]),VSub(Triangle_B[2],Triangle_B[1]),VSub(Triangle_B[0],Triangle_B[2]) };
     
	std::vector<VECTOR> Axes;

	Axes.push_back(VCross(EdgesA[0], EdgesA[1]));
	Axes.push_back(VCross(EdgesB[0], EdgesB[1]));

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {

            Axes.push_back(VCross(EdgesA[i], EdgesB[j]));
        }
    }

    for(const auto& Axis : Axes)
    {
		float MinA=0, MinB=0, MaxA=0, MaxB=0;

		TProject(Triangle_A, Axis, MinA, MaxA);
		TProject(Triangle_B, Axis, MinB, MaxB);

        if (MaxA < MinB || MaxB < MinA)
        {
            return false; 
        }
	}

    return false;
}

void ModelCheckers::TProject(const VECTOR Triangle[3], const VECTOR& Axis, float& OutMin, float &OutMax)
{
	float p0 = VDot(Triangle[0], Axis);
	float p1 = VDot(Triangle[1], Axis);
    float p2 = VDot(Triangle[2], Axis);

    OutMin = (p0 < p1 ? (p0 < p2 ? p0 : p2) : (p1 < p2 ? p1 : p2));
    OutMax = (p0 > p1 ? (p0 > p2 ? p0 : p2) : (p1 > p2 ? p1 : p2));

}

bool ModelCheckers::IsModel_Joint_Model(const int& M1, const int& M2, float M1_R)
{
  ///M２のモデルから三角形のリストを作成 ここがどうにもできない
    std::vector<VECTOR> List;
    std::vector<VECTOR> M1List;


    for (int TriangleIndex = 0; TriangleIndex <= List.size(); TriangleIndex+=3)
    {
        VECTOR Triangle[3];
         Triangle[0] = List[TriangleIndex];
         Triangle[1] = List[TriangleIndex+1];
         Triangle[2] = List[TriangleIndex+2];


         if (IsTriangle_Joint_Sphere(Triangle[1], Triangle[0], Triangle[2], MV1GetPosition(M1), M1_R))
         {
             ///もっとも離れた二つを出す
             VECTOR V1 = VSub(Triangle[0], Triangle[1]);
             VECTOR V2 = VSub(Triangle[0], Triangle[2]);
             VECTOR V3 = VSub(Triangle[2], Triangle[1]);

             float Max = VSize(VMax(V1, V2, V3));
             for(int Triangle2Index = 0; Triangle2Index <= M1List.size(); Triangle2Index += 3)
             {
                 ///さっきの反対のモデルでも同じことをする
                 VECTOR Triangle2[3];
                 Triangle2[0] = List[Triangle2Index];
                 Triangle2[1] = List[Triangle2Index + 1];
                 Triangle2[2] = List[Triangle2Index + 2];

                 if (IsTriangle_Joint_Sphere(Triangle2[1], Triangle2[0], Triangle2[2], Triangle[0], Max))
                 {
                     if (IsTriangle_Joint_Triangle(Triangle[1], Triangle[0], Triangle[2], Triangle2[1], Triangle2[0], Triangle2[2]))
                     {
                         return true;
                     }
                 }
             }

         }
    }

   


    return false;
}
