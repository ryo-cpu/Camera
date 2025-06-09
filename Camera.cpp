#include<vector>
#include "DxLib.h"
#include"Camera.h"

Camera::Camera()
{
    SetCameraNearFar(100.0f, 1500.0f);
    Pos = VGet(0, 0, 0);
    Offset = VGet(0, 0, 0);
    Dir = VGet(0, 0, 0);
    isMove = false;
    isPan = false;
    isZoom = false;
    isChase = false;
    zoomDistance = 1.0f;
}

Camera::Camera(float Near, float Far)
{
    SetCameraNearFar(Near, Far);
    Pos = VGet(0, 0, 0);
    Offset = VGet(0, 0, 0);
    Dir = VGet(0, 0, 0);

    isMove = false;
    isPan = false;
    isZoom = false;
    isChase = false;
    zoomDistance = 0.0f;


}

Camera::Camera(float Near, float Far, VECTOR CPos)
{
    SetCameraNearFar(Near, Far);
    Pos = CPos; 
    Offset = VGet(0, 0, 0);
    Dir = VGet(0, 0, 0);

    isMove = false;
    isPan = false;
    isZoom = false;
    isChase = false;

    zoomDistance = 0.0f;

}

Camera::Camera(float Near, float Far, VECTOR CPos, VECTOR TPos)
{
    SetCameraNearFar(Near, Far);
    SetCameraPositionAndTarget_UpVecY(CPos,TPos);
    Offset = VSub(CPos, TPos);
    Dir = VGet(0, 0, 0);

    Pos = CPos;

    isMove = false;
    isPan = false;
    isZoom = false;
    isChase = false;
  
    zoomDistance = 0.0f;

}

Camera::Camera(float Near, float Far, VECTOR CPos, float VRotate, float HRotate, float TRotate)
{
    SetCameraNearFar(Near, Far);
    SetCameraPositionAndAngle(CPos, VRotate, HRotate, TRotate);
    Pos = CPos;
    Offset = VGet(0, 0, 0);
    Dir = VGet(0, 0, 0);
    isMove = false;
    isPan = false;
    isZoom = false;
    isChase = false;
    Angle = VGet(VRotate, HRotate, TRotate);


    zoomDistance = 0.0f;

}

Camera::Camera(VECTOR CPos)
{
    SetCameraNearFar(100.0f, 1500.0f);
    SetCameraPositionAndTarget_UpVecY(CPos,VGet(0,0,0));
    Dir = VGet(0, 0, 0);
    Pos = CPos;
    Offset = VGet(0, 0, 0);

    isMove = false;
    isPan = false;
    isZoom = false;
    isChase = false;
    zoomDistance = 0.0f;



}

Camera::Camera(VECTOR CPos, VECTOR TPos)
{
    SetCameraNearFar(100.0f, 1500.0f);

    SetCameraPositionAndTarget_UpVecY(CPos, TPos);
    Offset = VSub(TPos, CPos);
    Dir = VGet(0, 0, 0);
    Pos = CPos;
    isMove = false;
    isPan = false;
    isZoom = false;
    isChase = false;
   
    zoomDistance = 0.0f;



}

void Camera::StartChase()
{
    isChase = true;
    ///その他のPos干渉するフラグ止め
    isPan = false;
    isMove = false;
}

void Camera::EndChase()
{
    isChase = false;
}

void Camera::Chase(VECTOR TPos)
{
    SetCameraPositionAndTarget_UpVecY(VAdd(TPos,Offset), TPos);
    
    Pos = VAdd(TPos, Offset);
    GetAngle(TPos);
}

void Camera::Look(VECTOR TPos)
{
    SetCameraPositionAndTarget_UpVecY(VAdd(TPos, Offset), TPos);
    GetAngle(TPos);
}

void Camera::StartMove(VECTOR dir)
{
    isPan = false;
    isChase = false;
    isMove = true;
    Dir = dir;

}

void Camera::ChangeMove(VECTOR dir)
{
    Dir = dir;
}

void Camera::EndMove()
{
    isMove = false;
}

VECTOR Camera::GetDir()
{
    return Dir;
}

VECTOR Camera::GetPos()
{
    return Pos;
}

VECTOR Camera::GetOffset()
{
    return Offset;
}

void Camera::Move()
{
   
    Pos = VAdd(Pos, Dir);
    SetCameraPositionAndAngle(Pos, Angle.x, Angle.y, Angle.z);

}

void Camera::RotaionAxis(VECTOR TPos, MATRIX TurnPower)
{
    RotFreeAxis(Pos, TPos, TurnPower);
}



void Camera::Rotaion(MATRIX TurnPower)
{
    Pos = VTransform(Pos, TurnPower);

}

void Camera::SetOffset(VECTOR offset)
{
    Offset = offset;
}

void Camera::ResetOffset(VECTOR offset, VECTOR TPos)
{
    Offset = offset;
    Pos = VAdd(TPos, Offset);
    SetCameraPositionAndTarget_UpVecY(VAdd(TPos, Offset), TPos);
    GetAngle(TPos);

}

void Camera::Action(VECTOR offset, VECTOR TPos, float VRotate, float HRotate, float TRotate)
{
    Offset = offset;
    Pos = VAdd(TPos, Offset);
    Angle = VGet(VRotate, HRotate, TRotate);

    SetCameraPositionAndAngle(Pos, VRotate, HRotate, TRotate);
  
}

 void Camera::StartZoom(float ZoomDistance)
{
    
         isZoom = true;
         zoomDistance = ZoomDistance;
         
     
}

 void Camera::EndZoom()
 {
     isZoom = false;
     zoomDistance = 0;

 }



void Camera::Zoom(VECTOR TPos)
{
    VECTOR forward;

    float pitch = Angle.x; // X軸（上下）の回転
    float yaw = Angle.y; // Y軸（左右）の回転

    forward.x = sinf(yaw) * cosf(pitch);
    forward.y = -sinf(pitch);
    forward.z = cosf(yaw) * cosf(pitch);

  
    
    forward = VNorm(forward);

    forward = VScale(forward,zoomDistance);
    ///その値を足す
 
    
    SetCameraPositionAndAngle(VAdd(Pos,forward), Angle.x, Angle.y, Angle.z);
    

   
}

void Camera::Pan(VECTOR TPos)
{
   
    GetAngle(TPos);
    SetCameraPositionAndTarget_UpVecY(Pos, TPos);
   

}

void Camera::StartPan()
{
    isPan = true;
    isChase = false;
  
}

void Camera::EndPan()
{
    isPan = false;
    isChase = true;
}


void Camera::Update(VECTOR TPos)
{
    if (isChase)
    {
        Chase(TPos);
    }
    if (isMove)
    {
        Move();
    }
  
    if (isPan)
    {
        Pan(TPos);
    }
    if (isZoom)
    {
        Zoom(TPos);
    }
   
}

VECTOR Camera::RotFreeAxis(VECTOR& V1, const VECTOR& Axis, const MATRIX& Power)
{
    V1 = VSub(V1, Axis);
    V1 = VTransform(V1, Power);
    V1 = VAdd(V1, Axis);
    return V1;
}

void Camera::GetAngle(VECTOR Target)
{
    // 方向ベクトル
    VECTOR dir;
    dir.x = Target.x - Pos.x;
    dir.y = Target.y - Pos.y;
    dir.z = Target.z - Pos.z;

    // カメラの角度を算出（ラジアン）
    float yaw = atan2f(dir.x, dir.z); // Y軸回転（左右）
    float pitch = -atan2f(dir.y, sqrtf(dir.x * dir.x + dir.z * dir.z)); // X軸回転（上下）
    float roll = 0.0f; // Z軸回転は通常0（使っていなければ）

    Angle.x = pitch;
    Angle.y = yaw;
    Angle.z = roll;
    

}



