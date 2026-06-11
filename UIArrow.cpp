#include "UIArrow.h"
#include<math.h>
/// <summary>
/// /矢印の根本から表示の中心までの距離
/// </summary>
const float RootDistance = 200.0f;
const float ArrowSize = 100.0f;  
void UIArrow::Make(VECTOR Target, VECTOR Root)
{
   

	///カメラの位置と注視点を取得
    VECTOR CamPos = GetCameraPosition();
	CamPos.y = 0.0f;
    VECTOR CamTarget = GetCameraTarget();
	CamTarget.y = 0.0f;
	///カメラの正面ベクトルを求める
    VECTOR Forward = VNorm(VSub(CamTarget, CamPos));
    VECTOR Right = VNorm(VGet( Forward.z, 0.0f,-Forward.x));
	///ターゲットとカメラの方向を求める
    VECTOR Dir = VNorm(VSub(Target, CamPos));
	Dir.y = 0.0f;   
    VECTOR ToTarget = VSub(Target, CamPos);

    float x = VDot(ToTarget, Right);
    float y = VDot(ToTarget, Forward);

    Dir = VNorm(Dir);

    float angle = atan2f(x, y);

    ///０，０に上向きの矢印を作成
    VECTOR Top = VGet(0, -ArrowSize, 0);
    VECTOR Root1 = VTransformSR(Top, MGetRotZ(DX_PI_F / 2));
	Root1 = VScale(Root1, 1/4.f);
    VECTOR Root2 = VTransformSR(Top, MGetRotZ(DX_PI_F / -2));
    Root2 = VScale(Root2, 1/4.f);
    VECTOR Move=VGet(0,0,0);
    VECTOR Center = VGet(960, 540, 0);

    Move.x = Center.x + sin(angle) * RootDistance;
    Move.y = Center.y - cos(angle) * RootDistance;

	
    //移動行列の追加
    MATRIX Moveing= MGetTranslate(Move);
	
    

    MATRIX Rot = MGetRotZ(angle);

	MATRIX All = MMult(Moveing,Rot);


	Top = VTransformSR(Top, All);
    Root1 = VTransformSR(Root1, All);
    Root2 = VTransformSR(Root2, All);

    Center =ConvWorldPosToScreenPos(Root);
    Center.x = Center.x + sin(angle) * RootDistance;
    Center.y = Center.y - cos(angle) * RootDistance;
	TopX   = Top.x+Center.x;
	TopY   = Top.y+Center.y;
	Root1X = Root1.x+Center.x;
	Root1Y = Root1.y+Center.y;
	Root2X = Root2.x+Center.x;
	Root2Y = Root2.y+Center .y;
}

void UIArrow::Draw()
{
	DrawTriangle(TopX, TopY, Root1X, Root1Y, Root2X, Root2Y, GetColor(200,21,13), TRUE);
}
