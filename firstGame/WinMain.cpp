#include"DxLib.h"

#define MAXWIDTH 10
#define MAXHEIGHT 7

#define IMGWIDTH 62
#define IMGHEIGHT 62

#define BALL_SPEED 5
#define SIKAKU_SPEED 4
#define SHOT_SPEED 9


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

struct Sikaku
{
	int x;
	int y;
	int handle;
	int muki;
};

struct Shot
{
	int x;
	int y;
	int handle;
	int flag;
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

	Shot shot;
	shot.x = 0;
	shot.y = 0;
	shot.handle = LoadGraph("img/Shot.png");
	shot.flag = 0;
	
	Sikaku sikaku;
	sikaku.x = IMGWIDTH * 1;
	sikaku.y = IMGHEIGHT * 1;
	sikaku.handle = LoadGraph("img/Sikaku.png");
	sikaku.muki = 0;

	

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
		
		if (CheckHitKey(KEY_INPUT_Z) && shot.flag == 0)
		{
			shot.x = ball.x + IMGWIDTH / 2;
			shot.y = ball.y + 2;
			shot.flag = 1;

		}


		if (shot.flag)
		{
			shot.y -= SHOT_SPEED;
			DrawGraph(shot.x, shot.y, shot.handle, FALSE);
		}

		

		if (sikaku.muki == RIGHT)
			sikaku.x += SIKAKU_SPEED;
		else if (sikaku.muki == LEFT)
			sikaku.x -= SIKAKU_SPEED;


		if (sikaku.x > (MAXWIDTH - 0.5)*IMGWIDTH)
		{
			sikaku.x = (MAXWIDTH - 0.5)*IMGWIDTH;
			sikaku.muki = LEFT;
		}
		else if (0 > sikaku.x)
		{
			sikaku.x = 0;
			sikaku.muki = RIGHT;
		}

		if (shot.flag == 1 && shot.y < -5)
		{
			shot.flag = 0;
		}
		

		DrawGraph(sikaku.x, sikaku.y, sikaku.handle, FALSE);
		DrawGraph(ball.x, ball.y, ball.handle, FALSE);
		ScreenFlip();
		if (ProcessMessage() == -1)
			break;
	}

	DxLib_End();

	return 0;
}