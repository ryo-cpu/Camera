#include "SpecialMove.h"


SpecialMove::SpecialMove(Camera& Camera, Character& Player, Character& Enemy) : camera(Camera), player(Player), enemy(Enemy)
{
	
}
bool SpecialMove::Update(float DeltaTime)
{
	float ElapsedTime = player.GetLiveTime() -player.GetStartLiveTime();
	VECTOR Front =VScale(VNorm( VSub(player.GetPos(),enemy.GetPos())),player.GetAttackCollison().GetSphereSize());
	VECTOR HitPoint = VAdd(VGet(Front.x,400,Front.z), enemy.GetPos());


	if (ElapsedTime <= 1.5)
	{
		///‹N‚±‚è
		camera.ResetOffset(DefaultCamera, player.GetPos());
		camera.EndMove();
	}
	else if (ElapsedTime <= 2.0)
	{
		///”ò‚Ñã‚ª‚è
		player.SetMove(VGet(0, 10, 0));
		camera.StartPan();
		camera.EndMove();

		if (VSize(VSub(camera.GetOffset(), SpecaleMoveCamerafast)) != 0)
		{
			camera.ResetOffset(SpecaleMoveCamerafast, player.GetPos());
		}
	}
	else if (ElapsedTime <= 3.0)
	{
		///‹ó’†Zoom
		camera.EndChase();
		if (VSize(VSub(camera.GetPos(), player.GetPos()))<=100.0f)
		{
			camera.EndMove();
		}
		else
		{
			camera.StartMove(VScale(VSub(player.GetPos(), camera.GetPos()), 0.01));
		}
		

		if (VSize(VSub(camera.GetOffset(), SpecaleMoveCameraS)) != 0)
		{
			camera.ResetOffset(SpecaleMoveCameraS, player.GetPos());
		}
	}
	else if (ElapsedTime <= 4.0)
	{
		///ˆÚ“®‚ÆUŒ‚
	    player.SetCollison(player.GetPos(), 0);
		camera.ResetOffset(DefaultCamera, player.GetPos());
		////“–‚½‚è”»’è‚¬‚è‚¬‚è‚ÅŽ~‚Ü‚é
		player.SetMove(VScale(VSub(HitPoint, player.GetPos()),0.5));
		VECTOR AttackPos = VGet(0, 0, 0);
		AttackPos = VTransformSR(AttackPos, MGetRotY(player.GetDir().y));
		player.SetAttackCollison(VAdd(player.GetPos(), AttackPos), 100.f);
		DrawSphere3D(player.GetAttackCollison().GetPos(), player.GetAttackCollison().GetSphereSize(), 16, GetColor(200, 255, 255), GetColor(0, 0, 0), TRUE);
	}

	else
	{
		player.SetCollison(player.GetPos(), 40);
		camera.ResetOffset(DefaultCamera, player.GetPos());
		enemy.SetisDraw(true);
		return false;
	}
	player.AnimUpdate(DeltaTime);
	player.MoveCollison(player.GetMove());
	player.SetPos(VAdd(player.GetPos(),player.GetMove()));

	player.AddLiveTime(DeltaTime);
	return true;
}
