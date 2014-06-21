#include"DxLib.h"

#define MAXWIDTH 10
#define MAXHEIGHT 7

#define IMGWIDTH 62
#define IMGHEIGHT 62

#define BALL_SPEED 4
#define SIKAKU_SPEED 3
#define SHOT_SPEED 2


enum Direction
{
	RIGHT,
	LEFT,

};

struct Ball
{
	int x;
	int y;
	int handle;
};


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);


	if (DxLib_Init() == -1)
		return-1;
	SetGraphMode(640, 480, 16);
	SetDrawScreen(DX_SCREEN_BACK);
	
	
	Ball ball;
	ball.x=IMGWIDTH * 2;
	ball.y=IMGHEIGHT * 5;
	ball.handle= LoadGraph("img/Ball.png");

	
	int shotX = 0;
	int shotY = 0;
	int handle_shot = LoadGraph("img/Shot.png");

	

	int sikakuX = IMGWIDTH * 1;
	int sikakuY = IMGHEIGHT * 1;
	int handle_sikaku = LoadGraph("img/Sikaku.png");

		/*int newX = ball.x;
		int newY = ball.y;*/
		
		int sikaku_muki=0;

		int shotFlag = 0;

	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();
		
		

		if (CheckHitKey(KEY_INPUT_UP))
			ball.y -= BALL_SPEED;
		else if (CheckHitKey(KEY_INPUT_DOWN))
			ball.y += BALL_SPEED;
		else if (CheckHitKey(KEY_INPUT_RIGHT))
			ball.x += BALL_SPEED;
		else if (CheckHitKey(KEY_INPUT_LEFT))
			ball.x -= BALL_SPEED;

		if (ball.x < 0)
			ball.x = 0;
		if (ball.y < 0)
			ball.y = 0;
		if (ball.x >(MAXWIDTH - 0.5)*IMGWIDTH)
			ball.x = (MAXWIDTH - 0.5)*IMGWIDTH;
		if (ball.y >(MAXHEIGHT*IMGHEIGHT))
			ball.y = (MAXHEIGHT*IMGHEIGHT);
		
		if (CheckHitKey(KEY_INPUT_Z) && shotFlag == 0)
		{
			shotX = ball.x + IMGWIDTH / 2;
			shotY = ball.y + 2;
			shotFlag = 1;

		}
		if (shotFlag)
		{
			shotY -= SHOT_SPEED;
			DrawGraph(shotX, shotY, handle_shot, FALSE);
		}

		

		if (sikaku_muki == RIGHT)
			sikakuX += SIKAKU_SPEED;
		else if (sikaku_muki == LEFT)
			sikakuX -= SIKAKU_SPEED;

		if (sikakuX > (MAXWIDTH - 0.5)*IMGWIDTH)
		{
			sikakuX = (MAXWIDTH - 0.5)*IMGWIDTH;
			sikaku_muki = LEFT;
		}
		else if (0 > sikakuX)
		{
			sikakuX = 0;
			sikaku_muki = RIGHT;
		}

		if (shotFlag == 1 && shotY < -5)
		{
			shotFlag = 0;
		}
		/*if (sikakuX < (MAXWIDTH - 0.5)*IMGWIDTH)
			sikakuX += 2;
		else if (0 < sikakuX)
			sikakuX -= 2;*/

		DrawGraph(sikakuX, sikakuY, handle_sikaku, FALSE);
		DrawGraph(ball.x, ball.y, ball.handle, FALSE);
		ScreenFlip();
		if (ProcessMessage() == -1)
			break;
	}

	DxLib_End();

	return 0;
}