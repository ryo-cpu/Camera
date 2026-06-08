#include "UIArrow.h"

void UIArrow::Make(VECTOR Target, VECTOR Root)
{
    VECTOR TargetScreenPos = ConvWorldPosToScreenPos(Target);
    VECTOR RooScreentPos = ConvWorldPosToScreenPos(Root);

    VECTOR  Dir = VSub(TargetScreenPos, RooScreentPos);
    Dir = VNorm(Dir);
    ///０，０に上向きの矢印を作成
    VECTOR Top = VGet(0, 30, 0);
    VECTOR Root1 = VTransformSR(Top, MGetRotZ(DX_PI_F / 2));
    VECTOR Root2 = VTransformSR(Top, MGetRotZ(DX_PI_F / -2));
    VECTOR Move = VScale(Dir, 300.0f);
    MGetTranslate(Move);
    VDot(VGet(0, 10, 0), Dir)/(VSize(VGet(0,10,0))*VSize(Dir));

    Top =   VAdd(Top, Move);
    Root1 = VAdd(Root1, Move);
    Root2 = VAdd(Move, Root2);

   

}

void UIArrow::Draw()
{
	DrawTriangle(TopX, TopY, Root1X, Root1Y, Root2X, Root2Y, GetColor(200,21,13), TRUE);
}
