#pragma once
#include<DxLib.h>
#include <chrono>  // chronoを使うため]
#include<cmath>


const VECTOR SpecaleMoveCamerafast = VGet(10, 0, 200);
const VECTOR SpecaleMoveCameraS = VGet(100, -300, -500);
const VECTOR DefaultCamera = VGet(0, 600, 1300);
const VECTOR StartCamera = VGet(0, 1000, 3000);
const VECTOR LoseCamera = VGet(0, 300, 500);
const VECTOR WinCameraFast = VGet(500, 1000, 1000);
const VECTOR WinCameraSecand = VGet(0, 1000, -1000);
const VECTOR WaitCamera = VGet(0, 200, 1500);
const VECTOR CounterCamera = VGet(100, -100, 200);




class Camera
{
    VECTOR Pos;
    VECTOR Offset;
    VECTOR Angle;////自分の向き
    VECTOR Dir;
    VECTOR TargetAngle;////相手からの自分の向き
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
    void StartChase(VECTOR TPos);
    void EndChase();
    void Chase(VECTOR TPos);
    void Look(VECTOR TPos);
    void StartMove(VECTOR dir);
    void ChangeMove(VECTOR dir);
    void Apply();
    void EndMove();
    VECTOR GetDir();
    VECTOR GetPos();
    void SetPos(VECTOR pos);
    VECTOR GetOffset();
    void Move();
    /// <summary>
    ///  ターゲット軸回転
    /// </summary>
    void RotationAxis(VECTOR TPos, MATRIX TurnPower);
    /// <summary>
    /// 自分軸回転
    /// </summary>
    void Rotation(MATRIX TurnPower);
    void SetOffset(VECTOR offset);

    /// <summary>
    /// オフセットの変更
    /// </summary>
    /// <param name="CPos"></param>
    /// <param name="TPos"></param>
    void ResetOffset(VECTOR offset, VECTOR TPos);
    void Action(VECTOR offset, VECTOR TPos, float VRotate, float HRotate, float TRotate);

    void StartZoom(float ZoomDistance);
    bool GetisZoom();
    void EndZoom();
    /// <summary>
    /// ズーム
    /// </summary>
    /// <param name="TPos"></param>
    void Zoom(VECTOR TPos);
    void ZoomOut(float OutSpeed);
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
    void CalculateAngle(VECTOR Target);
    void SetAngle(VECTOR angle);
    void AddAngle(VECTOR addangle);
    void CalculateTargetAngle(VECTOR Target);
    void SetTAngle(VECTOR angle);
    void AddTAngle(VECTOR addangle);
    VECTOR GetTargetAngle();
    VECTOR WorldToCamera(VECTOR Pos);


}


;
