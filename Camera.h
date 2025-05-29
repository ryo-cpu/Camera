#pragma once
#include<DxLib.h>


class Camera
{
    VECTOR Pos;
    VECTOR Offset;
    VECTOR Angle;
    VECTOR Dir;
    bool isMove, isPan, isChase,isZoom;
    float zoomDistance;///���̋������߂���

public:
    /// <summary>
    /// �����Ȃ����̃C���X�g���N�^
    /// </summary>
    Camera();
    /// <summary>
    /// �J�����̈ʒu�̂�
    /// </summary>
    /// <param name="CPos"></param>
    Camera(float Near, float Far);
    Camera(float Near, float Far, VECTOR CPos);
    Camera(float Near, float Far, VECTOR CPos, VECTOR TPos);
    Camera(float Near, float Far, VECTOR CPos, float VRotate, float HRotate, float TRotate);
    Camera(VECTOR CPos);
    /// <summary>
    /// �J�����̈ʒu�@�^�[�Q�b�g�̈ʒu
    /// </summary>
    /// <param name="CPos"></param>
    /// <param name="TPos"></param>
    Camera(VECTOR CPos, VECTOR TPos);
    /// <summary>
    /// �Ǐ]
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
    ///  �^�[�Q�b�g����]
    /// </summary>
    void RotaionAxis(VECTOR TPos, MATRIX TurnPower);
    /// <summary>
    /// ��������]
    /// </summary>
    void Rotaion(MATRIX TurnPower);

    /// <summary>
    /// �I�t�Z�b�g�̕ύX
    /// </summary>
    /// <param name="CPos"></param>
    /// <param name="TPos"></param>
    void ResetOffset(VECTOR offset, VECTOR TPos);
    void Action(VECTOR offset, VECTOR TPos, float VRotate, float HRotate, float TRotate);

    void StartZoom(float ZoomDistance);
    void EndZoom();
    /// <summary>
    /// �Y�[��
    /// </summary>
    /// <param name="TPos"></param>
    void Zoom(VECTOR TPos);
    /// <summary>
    /// ��U��̂ݒǏ]
    /// </summary>
    /// <param name="TPos"></param>
    void Pan(VECTOR TPos);
    void StartPan();
    void EndPan();
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="TPos"></param>
    void Update(VECTOR TPos);
    /// <summary>
    /// �f�X�g���C�A
    /// </summary>
    VECTOR RotFreeAxis(VECTOR & V1, const  VECTOR & Axis, const MATRIX & Power);
    void GetAngle(VECTOR Target);

}


;
