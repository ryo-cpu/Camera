#include "SpecialMove.h"

SpecialMove::SpecialMove(Camera& Camera, Character& Player, Character& Enemy) : camera(Camera), player(Player), enemy(Enemy)
{
	EnemyPos = enemy.GetPos();
	///•KE‹Z”­“®‚É•ÏX‚³‚ê‚é@ƒfƒtƒHƒ‹ƒg‚Ítrue
	WasHit = true;
}
SpecialMove::~SpecialMove()
{
	
}
bool SpecialMove::GetWasHit()
{
	return WasHit;
}
void SpecialMove::Hit()
{
	WasHit = true;
}
bool SpecialMove::Update(float DeltaTime)
{
	///Ã~‚³‚¹‚é
	player.SetMove(VGet(0, 0, 0));
	///³–Ê‚ğŒü‚©‚¹‚é
	VECTOR Front = VNorm(VSub(player.GetPos(),enemy.GetPos()));
	float Angle = atan2f(Front.x, Front.z);
	player.SetDir(VGet(0, Angle, 0));
	MV1SetRotationXYZ(player.GetImg(),player.GetDir());
	float ElapsedTime = player.GetLiveTime() -player.GetStartLiveTime();

	//VECTOR HitPoint = VAdd(VGet(Front.x,400,Front.z), enemy.GetPos());
	EffectImg* SpE = new EffectImg("data/KickWave.efkefc", 100);

	if (ElapsedTime <= 1.5)
	{
		///‹N‚±‚è
		///‚±‚ÌŠÔ‚Í‘OŒ„‚«
		enemy.AnimUpdate(DeltaTime);
		enemy.Update(DeltaTime);
		camera.ResetOffset(DefaultCamera, player.GetPos());
		camera.EndMove();
		camera.EndZoom();
		NowMode = Jump;
		Afterimages.clear();
		float Rot = 0.02f;
		VECTOR F = VScale(VGet(0, 0, 1), VSize(VGet(DefaultCamera.x, 0, DefaultCamera.z)));
		camera.AddTAngle(VGet(0, Rot, 0));
		VECTOR RotP = camera.GetTargetAngle();
		MATRIX RotX = MGetRotX(RotP.x);
		MATRIX RotY = MGetRotY(RotP.y);///Z‚Í‰ñ“]‚µ‚È‚¢
		MATRIX RotAll = MMult(RotX, RotY);
		
		camera.ResetOffset(VTransformSR(F, RotAll), player.GetPos());
		camera.Look(player.GetPos());
		
	}
	else if (ElapsedTime<=2.0)
	{
		player.SetDir(VGet(0, Angle, 0));
		///”ò‚Ñã‚ª‚è
		player.SetMove(VGet(0, 1000*DeltaTime, 0));
		camera.StartPan();
		camera.EndMove();
		player.SetAttack(1000);
		StartJoypadVibration(DX_INPUT_PAD1, 500, 100, 1);

		if (VSize(VSub(camera.GetOffset(), SpecaleMoveCamerafast)) != 0)
		{
			camera.ResetOffset(SpecaleMoveCamerafast, player.GetPos());
		}
		NowMode = ZoomWait;
	}
	else if(NowMode==ZoomWait)
	{
		////UŒ‚‰ŠúˆÊ’u‚ÉˆÚ“®
		VECTOR InitPos = SPInitPos;
		const char* HipName = "mixamorig:Hips";
		VECTOR test = MV1GetPosition(enemy.GetImg());
		int HipIndex = MV1SearchFrame(enemy.GetImg(), HipName);
		if (HipIndex >= 0)
		{
			EnemyPos = MV1GetFramePosition(enemy.GetImg(), HipIndex);
		}
		////“G‚Ì•ûŒü
		VECTOR EnemyDir = VNorm(VSub(EnemyPos, player.GetPos()));
		EnemyDir.y = 0;
		///“G‚ÉŒü‚©‚¢‡‚¤‚æ‚¤‚È‰ñ“]—Í‚ğo‚·
		float Angle = atan2f(EnemyDir.z, EnemyDir.x);
		////UŒ‚‰ŠúˆÊ’u‚ğ‰ñ“]‚¹‚ê‚é
		InitPos =VTransformSR(InitPos, MGetRotY(Angle));
		player.SetPos(VAdd(EnemyPos, InitPos));
		///ƒJƒ‚ç
		camera.ResetOffset(VScale(VNorm(VSub(EnemyPos, player.GetPos())), 1000), player.GetPos());
		////“G‚Æ©•ª‚ÌŠp“x‚ğ‹‚ß‚é
		float rat = atan2(EnemyDir.z,EnemyDir.x);
		EffectM::Add(*SpE,player.GetPos(), VGet(0, rat, 0),VGet(0,0,0),SpEffctID);
		NowMode = Zoom;
		///•KE‹Z‚ğ‚Å“–‚Ä‚È‚¢‚æ‚¤‚É
		WasHit = false;
		player.SetAttack(200);
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
			camera.StartMove(VScale(VSub(player.GetPos(), camera.GetPos()), DeltaTime*2));
		}
		

		NowMode = Attak;
		
	}
	else if (ElapsedTime <= 5.0)
	{

		///•KE‹Z–³“G
		enemy.SetAttackCollision(EnemyPos, 0);
		///ˆÚ“®‚ÆUŒ‚
	    player.SetCollision(player.GetPos(), 0);
		///PlayerƒJƒ‰enemy‚Ì’¼üó‚ÉƒJƒƒ‰
		VECTOR Offset = VSub(player.GetPos(), EnemyPos);
		if (ElapsedTime >= 3.5)
		{
			////Offset‚ğ‰ñ“]‚³‚¹‚½‚à‚Ì
			MATRIX RotY = MGetRotY(DX_PI_F / 2);
			Offset = VAdd(Offset,VTransformSR(Offset, RotY));
		}
		
		if(fabs(fmod(ElapsedTime, 0.05f)) < 0.01f&& !player.GetCollision().Collision(player.GetAttackCollision(), enemy.GetCollision()))
		{ 
			////V‚µ‚¢c‘œ‚ğì‚é
			        AfterImage NewAfterImage;
					NewAfterImage.handle = MV1DuplicateModel(player.GetImg());
					NewAfterImage.pos = MV1GetPosition(player.GetImg());
					NewAfterImage.rot = MV1GetRotationXYZ(player.GetImg());
					NewAfterImage.alpha = 100;
					NewAfterImage.valid = MV1GetSemiTransState(NewAfterImage.handle);
			

				
					int frameNum = MV1GetFrameNum(player.GetImg());
					for (int i = 0; i < frameNum; i++)
					{
						MATRIX m = MV1GetFrameLocalMatrix(player.GetImg(), i);
						MV1SetFrameUserLocalMatrix(NewAfterImage.handle, i, m);
					}
					Afterimages.push_back(NewAfterImage);
		
				
				

			
		}
		
		for (int i = 0; i < Afterimages.size(); i++)
		{
			
			MV1SetPosition(Afterimages[i].handle,Afterimages[i].pos);
			MV1SetRotationXYZ(Afterimages[i].handle,Afterimages[i].rot);
			MV1SetOpacityRate(Afterimages[i].handle,Afterimages[i].alpha / 255.0f);
			MV1DrawModel(Afterimages[i].handle);

		}
		camera.ResetOffset(VScale(Offset,2),player.GetPos());
		player.SetMove(VScale(VNorm(VSub(EnemyPos,player.GetPos())),VSize(SPInitPos)*DeltaTime));
		///UŒ‚‚Ì”»’è‚ğì¬
		VECTOR AttackPos = VGet(0, 0, 0);
		AttackPos =VTransformSR(AttackPos, MGetRotY(player.GetDir().y));
		player.SetAttackCollision(VAdd(player.GetPos(), AttackPos), 200.f);
		Sphere_Collision Next_E;
		Next_E.SetPos(VAdd(EnemyPos, enemy.GetMove()));
		Next_E.SetSphereSize(enemy.GetCollision().GetSphereSize());
	/*	Capsule JagHit(player.GetAttackCollision().GetPos(), player.GetAttackCollision().GetPos(), player.GetAttackCollision().GetSphereSize());
		for (int i = 0; i < player.GetCapsuleCollision().size(); i++)
		{
			
			if (JagHit.Survey(player.GetCapsuleCollision()[i], JagHit))
			{

				
				
			}
		}*/
		if (WasHit)
		{
			

			StartJoypadVibration(DX_INPUT_PAD1, 100, 300, 0);
			StartJoypadVibration(DX_INPUT_PAD1, 1000, 50, 1);
			///’â~
			player.SetMove(VGet(0, 0, 0));
		}
		
		
	}
	else if (ElapsedTime <= 6.0)
	{
		////////
		Effect* SpEffect = nullptr;
		SpEffect = EffectM::Search(SpEffctID);
		if (SpEffect != nullptr)
		{
			SpEffect->Stop();
			SpEffect = nullptr;
		}
		enemy.Update(DeltaTime);
		player.SetPos(VAdd(player.GetPos(), VGet(0, (5.5f-ElapsedTime)*1000*DeltaTime, 0)));
		player.SetAttackCollision(player.GetPos(), 0.0f);
		camera.ResetOffset(DefaultCamera, player.GetPos());
		camera.CalculateAngle(player.GetPos());
		camera.CalculateTargetAngle(player.GetPos());
		enemy.SetisDraw(true);

	}

	else
	{
		player.SetDir(VGet(0, Angle, 0));
		player.SetAttack(20);
		WasHit = true;
		VECTOR PushBack = VSub(EnemyPos, player.GetPos());
		PushBack.y = 0;
		if (VSize(PushBack) == 0)
		{
	    ///0‚Ì‚¨d•Ô‚µ‚ğ”ğ‚¯‚é‚½‚ß

		PushBack.x =+ 1;
		}
		/*player.SetPos(VAdd(EnemyPos, VScale(VNorm(PushBack), -800)));*/
		player.SetCollision(player.GetPos(), 40);
		/////////////////////////////////////////////////

		camera.ResetOffset(VTransformSR(DefaultCamera,MGetRotY(player.GetDir().y)),  player.GetPos());
		camera.CalculateAngle(player.GetPos());
		camera.CalculateTargetAngle(player.GetPos());
		enemy.SetisDraw(true);
		return false;
	}
	player.AnimUpdate(DeltaTime);
	player.MoveCollision(player.GetMove());
	player.SetPos(VAdd(player.GetPos(),player.GetMove()));

	player.AddLiveTime(DeltaTime);
	return true;
}
