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


void ShowTextureName(int Model)
{
   int num= MV1GetTextureNum(Model);
   SetFontSize(12);
   for (int i = 0; i < num; i++)
   {
       DrawFormatString(0, i*10, GetColor(255, 255, 255), "Name                  %s", MV1GetTextureName(Model, i));
   }
}

void ShowFrameName(int Model)
{
    int num = MV1GetFrameNum(Model);
    SetFontSize(12);
    for (int i = 0; i < num; i++)
    {
        DrawFormatString(0, i * 10, GetColor(255, 255, 255), "Name                  %s", MV1GetFrameName(Model, i));
    }
  
}

VECTOR VMax(VECTOR V1, VECTOR V2)
{
    return Vsize(V1) > Vsize(V2) ? V1 : V2;
}

VECTOR VMax(VECTOR V1, VECTOR V2, VECTOR V3)
{
    VECTOR MAX = VMax(V1, V2);
    MAX = VMax(MAX, V3);
    return MAX;
}

VECTOR VMin(VECTOR V1, VECTOR V2)
{
    return VSize(V1) < VSize(V2) ? V1 : V2;;
}

VECTOR VMin(VECTOR V1, VECTOR V2, VECTOR V3)
{
    VECTOR MIN = VMin(V1, V2);
    MIN = VMin(MIN, V3);
    return MIN;
}

VECTOR VProject(VECTOR CheckPoint, VECTOR StartGround, VECTOR EndGround)
{
    VECTOR Ground = VSub(EndGround, StartGround);
    ////CheckPintは引数と別れていると考える　変更しても引数側を改変しない
    CheckPoint = VSub(CheckPoint, StartGround);
    VECTOR  Proj = VScale(Ground, (VDot(CheckPoint, Ground) / VDot(Ground, Ground)));
    return Proj;
}

bool IsParallel(VECTOR A1, VECTOR A2, VECTOR B1, VECTOR B2)
{
    VECTOR Pos_inA = VProject(B1, A1, A2);
    VECTOR ShadowPos = VAdd(A1, Pos_inA);

    float Shadow_B1 = VSize(VSub(B1, ShadowPos));

    Pos_inA = VProject(B2, A1, A2);
    ShadowPos = VAdd(A1, Pos_inA);

    float Shadow_B2 = VSize(VSub(B2, ShadowPos));

    return Shadow_B1 == Shadow_B2;
}

bool IsTriangle_Joint_Sphere(VECTOR T1, VECTOR T2, VECTOR T3, VECTOR SphereP, float R)
{
    ///法線ベクトルを出す
    VECTOR Edge1 = VSub(T2, T1);
    VECTOR Edge2 = VSub(T3, T1);
    VECTOR Normal = VCross(Edge1, Edge2);
    float NormalLen = VSize(Normal);
    // 退化三角形チェック
    if (NormalLen < 1e-8f) {
        return false;
    }

    // 法線を正規化
    Normal = VScale(Normal, 1.0f / NormalLen);

    // 球の中心から三角形平面への距離
    VECTOR T1toSphere = VSub(SphereP, T1);
    float Distance = fabs(VDot(T1toSphere, Normal));

    // 距離がR以上なら衝突していない
    if (Distance > R) {
        return false;
    }
    // 球の中心から平面への最近点を求める
    VECTOR ClosestPointOnPlane = VSub(SphereP, VScale(Normal, VDot(T1toSphere, Normal)));

    // その点が三角形内にあるかチェック（重心座標を使用）
    if (IsPointInTriangle_Robust(ClosestPointOnPlane, T1, T2, T3)) {
        return true;  // 平面内に衝突点がある
    }

    // 三角形の3つの辺との距離をチェック
    float MinDist = R;

    // 辺1 (T1-T2)
    if (IsPointToSegmentDistance(SphereP, T1, T2, R)) {
        return true;
    }

    // 辺2 (T2-T3)
    if (IsPointToSegmentDistance(SphereP, T2, T3, R)) {
        return true;
    }

    // 辺3 (T3-T1)
    if (IsPointToSegmentDistance(SphereP, T3, T1, R)) {
        return true;
    }

    // 3つの頂点との距離をチェック
    if (VSize(VSub(SphereP, T1)) <= R) return true;
    if (VSize(VSub(SphereP, T2)) <= R) return true;
    if (VSize(VSub(SphereP, T3)) <= R) return true;

    return false;
}

bool IsTriangle_Joint_Triangle(VECTOR TA1, VECTOR TA2, VECTOR TA3, VECTOR TB1, VECTOR TB2, VECTOR TB3)
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
    
    const float EPSILON = 1e-6f;  // 浮動小数点誤差の容差

    for(const auto& Axis : Axes)
    {
        if (VSize(Axis) < EPSILON)continue;

		float MinA=0, MinB=0, MaxA=0, MaxB=0;

		TProject(Triangle_A, Axis, MinA, MaxA);
		TProject(Triangle_B, Axis, MinB, MaxB);

        if (MaxA < MinB - EPSILON || MaxB < MinA - EPSILON)
        {
            return false; 
        }
	}

    return true;
}

void TProject(const VECTOR Triangle[3], const VECTOR& Axis, float& OutMin, float &OutMax)
{
	float p0 = VDot(Triangle[0], Axis);
	float p1 = VDot(Triangle[1], Axis);
    float p2 = VDot(Triangle[2], Axis);

    OutMin = (p0 < p1 ? (p0 < p2 ? p0 : p2) : (p1 < p2 ? p1 : p2));
    OutMax = (p0 > p1 ? (p0 > p2 ? p0 : p2) : (p1 > p2 ? p1 : p2));

}

bool IsModel_Joint_Model(const int& M1, const int& M2, float M1_R)
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

bool IsPointInTriangle(VECTOR P, VECTOR T1, VECTOR T2, VECTOR T3)
{
    VECTOR v0 = VSub(T3, T1);
    VECTOR v1 = VSub(T2, T1);
    VECTOR v2 = VSub(P, T1);

    ///ないせきをとる
    float dot00 = VDot(v0, v0);
    float dot01 = VDot(v0, v1);
    float dot02 = VDot(v0, v2);
    float dot11 = VDot(v1, v1);
    float dot12 = VDot(v1, v2);

    float invDenom = 1.0f / (dot00 * dot11 - dot01 * dot01);
    float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    return (u >= 0) && (v >= 0) && (u + v <= 1);
}

bool IsPointToSegmentDistance(VECTOR P, VECTOR A, VECTOR B, float R)
{
    VECTOR AP = VSub(P, A);
    VECTOR AB = VSub(B, A);
    float ABLen = VSize(AB);

    if (ABLen < 1e-8f) {
        return VSize(AP) <= R;
    }

    float t = VDot(AP, AB) / (ABLen * ABLen);
    t = (t < 0.0f) ? 0.0f : (t > 1.0f) ? 1.0f : t;

    VECTOR ClosestPoint = VAdd(A, VScale(AB, t));
    return VSize(VSub(P, ClosestPoint)) <= R;
}

bool IsPointInTriangle_Robust(VECTOR P, VECTOR T1, VECTOR T2, VECTOR T3)
{
    VECTOR Normal = VCross(VSub(T2, T1), VSub(T3, T1));

    VECTOR C1 = VCross(VSub(T2, T1), VSub(P, T1));
    VECTOR C2 = VCross(VSub(T3, T2), VSub(P, T2));
    VECTOR C3 = VCross(VSub(T1, T3), VSub(P, T3));

    float d1 = VDot(Normal, C1);
    float d2 = VDot(Normal, C2);
    float d3 = VDot(Normal, C3);

    const float EPSILON = 1e-6f;
    return (d1 >= -EPSILON && d2 >= -EPSILON && d3 >= -EPSILON) ||
        (d1 <= EPSILON && d2 <= EPSILON && d3 <= EPSILON);
}
void PrintTestResult(const char* testName, bool result, bool expected)
{
    bool passed = (result == expected);
    const char* status = passed ? "✓ PASS" : "✗ FAIL";
    const char* resultStr = result ? "true" : "false";
    const char* expectedStr = expected ? "true" : "false";

    printf("%s: %s (result: %s, expected: %s)\n", status, testName, resultStr, expectedStr);
}

float Vsize(VECTOR a)
{
    return (a.x*a.x)+(a.y*a.y)+(a.z*a.z);
}
