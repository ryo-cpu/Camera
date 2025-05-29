#pragma once
#include<DxLib.h>


class Camera
{
    VECTOR Pos;
    VECTOR Offset;
    VECTOR Angle;
    VECTOR Dir;
    bool isMove, isPan, isChase,isZoom;
    float zoomDistance;///その距離分近ずく

public:
    /// <summary>
    /// 何もない時のインストラクタ
    /// </summary>
    Camera();
    /// <summary>
    /// カメラの位置のみ
    /// </summary>
    /// <param name="CPos"></param>
    Camera(float Near, float Far);
    Camera(float Near, float Far, VECTOR CPos);
    Camera(float Near, float Far, VECTOR CPos, VECTOR TPos);
    Camera(float Near, float Far, VECTOR CPos, float VRotate, float HRotate, float TRotate);
    Camera(VECTOR CPos);
    /// <summary>
    /// カメラの位置　ターゲットの位置
    /// </summary>
    /// <param name="CPos"></param>
    /// <param name="TPos"></param>
    Camera(VECTOR CPos, VECTOR TPos);
    /// <summary>
    /// 追従
    /// </summary>
    void StartChase();
    void EndChase();
    void Chase(VECTOR TPos);
    void StartMove(VECTOR dir);
    void ChangeMove(VECTOR dir);
    void EndMove();
    VECTOR GetDir();
    void Move();
    /// <summary>
    ///  ターゲット軸回転
    /// </summary>
    void RotaionAxis(VECTOR TPos, MATRIX TurnPower);
    /// <summary>
    /// 自分軸回転
    /// </summary>
    void Rotaion(MATRIX TurnPower);

    /// <summary>
    /// オフセットの変更
    /// </summary>
    /// <param name="CPos"></param>
    /// <param name="TPos"></param>
    void ResetOffset(VECTOR offset, VECTOR TPos);
    void Action(VECTOR offset, VECTOR TPos, float VRotate, float HRotate, float TRotate);

    void StartZoom(float ZoomDistance);
    void EndZoom();
    /// <summary>
    /// ズーム
    /// </summary>
    /// <param name="TPos"></param>
    void Zoom(VECTOR TPos);
    /// <summary>
    /// 首振りのみ追従
    /// </summary>
    /// <param name="TPos"></param>
    void Pan(VECTOR TPos);
    void StartPan();
    void EndPan();
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="TPos"></param>
    void Update(VECTOR TPos);
    /// <summary>
    /// デストロイア
    /// </summary>
    VECTOR RotFreeAxis(VECTOR & V1, const  VECTOR & Axis, const MATRIX & Power);
    void GetAngle(VECTOR Target);

}


;
