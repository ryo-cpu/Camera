#include "SpecialMove.h"
#include"EffectM.h"

SpecialMove::SpecialMove(Camera& Camera, Character& Player, Character& Enemy) : camera(Camera), player(Player), enemy(Enemy)
{
	
}
bool SpecialMove::Update(float DeltaTime)
{
	///ê√é~Ç≥ÇπÇÈ
	player.SetMove(VGet(0, 0, 0));
	///ê≥ñ Çå¸Ç©ÇπÇÈ
	player.SetDir(VGet(0, 0, 0));
	MV1SetRotationXYZ(player.GetImg(),player.GetDir());
	float ElapsedTime = player.GetLiveTime() -player.GetStartLiveTime();
	VECTOR Front =VScale(VNorm( VSub(player.GetPos(),enemy.GetPos())),player.GetAttackCollison().GetSphereSize());
	VECTOR HitPoint = VAdd(VGet(Front.x,400,Front.z), enemy.GetPos());
	EffectImg* SpE = new EffectImg("data/KickWave.efkefc", 100);

	if (ElapsedTime <= 1.5)
	{
		///ãNÇ±ÇË
		///Ç±ÇÃéûä‘ÇÕëOåÑÇ´
		enemy.Update(DeltaTime);
		camera.ResetOffset(DefaultCamera, player.GetPos());
		camera.EndMove();
		camera.EndZoom();
		NowMode = Jump;

		
	}
	else if (ElapsedTime<=2.0)
	{
		///îÚÇ—è„Ç™ÇË
		player.SetMove(VGet(0, 1000*DeltaTime, 0));
		camera.StartPan();
		camera.EndMove();
		player.SetAttack(1000);
		if (VSize(VSub(camera.GetOffset(), SpecaleMoveCamerafast)) != 0)
		{
			camera.ResetOffset(SpecaleMoveCamerafast, player.GetPos());
		}
		NowMode = ZoomWait;
	}
	else if(NowMode==ZoomWait)
	{
		////çUåÇèâä˙à íuÇ…à⁄ìÆ
		VECTOR InitPos = SPInitPos;
		////ìGÇÃï˚å¸
		VECTOR EnemyDir = VNorm(VSub(enemy.GetPos(), player.GetPos()));
		EnemyDir.y = 0;
		///ìGÇ…å¸Ç©Ç¢çáÇ§ÇÊÇ§Ç»âÒì]óÕÇèoÇ∑
		float Angle = atan2f(EnemyDir.z, EnemyDir.x);
		////çUåÇèâä˙à íuÇâÒì]ÇπÇÍÇÈ
		InitPos = VTransformSR(InitPos, MGetRotY(Angle));
		player.SetPos(VAdd(enemy.GetPos(), InitPos));
		///ÉJÉÅÇÁ
		camera.ResetOffset(VScale(VNorm(VSub(enemy.GetPos(), player.GetPos())), 1000), player.GetPos());
		////ìGÇ∆é©ï™ÇÃäpìxÇãÅÇﬂÇÈ
		float rat = atan2(EnemyDir.z,EnemyDir.x);
		EffectM::Add(*SpE,player.GetPos(), VGet(0, rat, 0));
		NowMode = Zoom;
	}
	
	else if (ElapsedTime <= 3.0)
	{
		
		///ãÛíÜZoom
		camera.EndChase();
		if (VSize(VSub(camera.GetPos(), player.GetPos()))<=100.0f)
		{
			camera.EndMove();
		}
		else
		{
			camera.StartMove(VScale(VSub(player.GetPos(), camera.GetPos()), DeltaTime*2));
		}
		

		NowMode = Attak;
		
	}
	else if (ElapsedTime <= 5.0)
	{
		///ïKéEãZñ≥ìG
		enemy.SetAttackCollison(enemy.GetPos(), 0);
		///à⁄ìÆÇ∆çUåÇ
	    player.SetCollison(player.GetPos(), 0);
		///PlayerÉJÉâenemyÇÃíºê¸èÛÇ…ÉJÉÅÉâ
		VECTOR Offset = VSub(player.GetPos(), enemy.GetPos());

		camera.ResetOffset(VScale(Offset,1.25), player.GetPos());
		player.SetMove(VScale(VNorm(VSub(enemy.GetPos(),player.GetPos())),VSize(SPInitPos)*DeltaTime));
		///çUåÇÇÃîªíËÇçÏê¨
		VECTOR AttackPos = VGet(0, 0, 0);
		AttackPos = VTransformSR(AttackPos, MGetRotY(player.GetDir().y));
		player.SetAttackCollison(VAdd(player.GetPos(), AttackPos), 100.f);
		
		if (player.GetCollison().Collison(player.GetAttackCollison(), enemy.GetCollison()))
		{
			///í‚é~
			player.SetMove(VGet(0,0,0));

		}
		player.SetAttack(10);
	}

	else
	{
		VECTOR PushBack = VSub(enemy.GetPos(), player.GetPos());
		PushBack.y = 0;
		if (VSize(PushBack) == 0)
		{
			PushBack.x + 1;
		}
		player.SetPos(VAdd(enemy.GetPos(), VScale(VNorm(PushBack), -800)));
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
