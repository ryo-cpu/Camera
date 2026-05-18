#pragma once
#include "DxLib.h"
class UI
{
private:
	char* Message;
	float MessagePosX;
	float MessagePosY;
	float MessageSize;
	int Img;
	float ImgPosX;
	float ImgPosY;
public :
	UI();
	void DrawImg();
	void DrawMessage();
	void SetMessagePos(float X, float Y);
	void SetImgPos(float X, float Y);
	void SetMessageSize(float size);
	void SetMessage(char* message);
	void SetImg(char* Link);


    
};

