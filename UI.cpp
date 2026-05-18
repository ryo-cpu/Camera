#include "UI.h"

UI::UI()
{
	MessagePosX = 0.0f;
	MessagePosX = 0.0f;
	ImgPosX = 0.0f;
	ImgPosY = 0.0f;
}

void UI::DrawImg()
{
	DrawGraph(ImgPosX, ImgPosY, Img, false);
}

void UI::DrawMessage()
{
	SetFontSize(MessageSize);
	DrawString(MessagePosX, MessagePosY, Message, GetColor(244, 229, 17));
}

void UI::SetMessagePos(float X, float Y)
{
	MessagePosX = X;
	MessagePosY = Y;
}

void UI::SetImgPos(float X, float Y)
{
	ImgPosX = X;
	ImgPosY = Y;
}

void UI::SetMessageSize(float size)
{
	MessageSize = size;
}

void UI::SetMessage(char* message)
{
	Message = message;
}

void UI::SetImg(char* Link)
{
	Img = LoadGraph(Link);
}
