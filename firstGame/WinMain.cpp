#include"DxLib.h"

#define IMGWIDTH 62
#define IMGHEIGHT 62

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);


	if (DxLib_Init() == -1)
		return-1;
	SetGraphMode(640, 480, 16);
	SetDrawScreen(DX_SCREEN_BACK);

	int handle_ball = LoadGraph("img/Ball.png");

	int ballX = IMGWIDTH * 1;
	int ballY = IMGHEIGHT * 0;

		int newX = ballX;
		int newY = ballY;

	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();
		
		

		if (CheckHitKey(KEY_INPUT_UP))
			newY -= 4;
		else if (CheckHitKey(KEY_INPUT_DOWN))
			newY += 4;
		else if (CheckHitKey(KEY_INPUT_RIGHT))
			newX += 4;
		else if (CheckHitKey(KEY_INPUT_LEFT))
			newX -= 4;

		
		DrawGraph(newX, newY, handle_ball, FALSE);
		ScreenFlip();
		if (ProcessMessage() == -1)
			break;
	}

	DxLib_End();

	return 0;
}