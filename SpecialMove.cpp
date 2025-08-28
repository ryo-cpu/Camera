#include "SpecialMove.h"


SpecialMove::SpecialMove(Camera& Camera, Character& Player, Character& Enemy) : camera(Camera), player(Player), enemy(Enemy)
{
	
}
bool SpecialMove::Update(float DeltaTime)
{
	float ElapsedTime = player.GetLiveTime() -player.GetStartLiveTime();
	if (ElapsedTime <= 0.5)
	{
		///‹N‚±‚è

	}
	else if (ElapsedTime <= 1.0)
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
	else if (ElapsedTime <= 1.5)
	{
		///‹ó’†Zoom
		camera.EndChase();
		camera.StartMove(VScale(VSub(player.GetPos(), camera.GetPos()), 0.01));

		if (VSize(VSub(camera.GetOffset(), SpecaleMoveCameraS)) != 0)
		{
			camera.ResetOffset(SpecaleMoveCameraS, player.GetPos());
		}
	}
	else if (ElapsedTime <= 2.0)
	{
		///ˆÚ“®‚ÆUŒ‚
		camera.ResetOffset(DefaultCamera, player.GetPos());
		player.SetMove(VScale(VSub(enemy.GetPos(),player.GetPos()), 0.1));
		VECTOR AttackPos = VGet(0, 0, 0);
		AttackPos = VTransformSR(AttackPos, MGetRotY(player.GetDir().y));
		player.SetAttackCollison(VAdd(player.GetPos(), AttackPos), 100.f);
		DrawSphere3D(player.GetAttackCollison().GetPos(), player.GetAttackCollison().GetSphereSize(), 16, GetColor(200, 255, 255), GetColor(0, 0, 0), TRUE);
	}
	else
	{
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
