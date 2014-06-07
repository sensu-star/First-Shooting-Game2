#include"DxLib.h"

#define MAXWIDTH 10
#define MAXHEIGHT 7

#define IMGWIDTH 62
#define IMGHEIGHT 62

//文字に数字を割り当てる、連続して定数を作りたいときに使うことが多い
enum mapState	
{
	FIELD,	//#define FIELD 0
	WALL,	//#define WALL 1
	KEY,	//#define KEY 2
	GOAL,	//#define GOAL 3　と同値

};

int CheckMapHit(int mapData[MAXHEIGHT][MAXWIDTH],int x,int y,mapState map)
{
	if ((0 <= newX&&newX < MAXWIDTH*IMGWIDTH) && (0 <= newY&&newY < MAXHEIGHT*IMGHEIGHT))
	{
		int i = newY / IMGHEIGHT;
		int j = newX / IMGWIDTH;
		int i2;
		int j2;
		if (newY%IMGHEIGHT == 0)
			i2 = i;
		else
			i2 = i + 1;
		if (newX%IMGWIDTH == 0)
			j2 = j;
		else
			j2 = j + 1;

		if (mapData[])

}

// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);


	if (DxLib_Init() == -1)
		return-1;
	SetGraphMode(640, 480, 16);
	SetDrawScreen(DX_SCREEN_BACK);

	//数字によって表示する画像を変える
	int mapData[MAXHEIGHT][MAXWIDTH] =
	{
		1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 1, 2, 0, 0, 1, 3, 1,
		1, 1, 0, 1, 1, 1, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 1, 1, 1, 1, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};
	int handle_field = LoadGraph("img/field.png");
	int handle_wall = LoadGraph("img/wall.png");
	int handle_man = LoadGraph("img/man.png");
	int handle_key = LoadGraph("img/key.png");
	int handle_goal = LoadGraph("img/goal.png");

	int manX = IMGWIDTH * 1;
	int manY = IMGHEIGHT * 0;
	int isGoal = 0;
	int keyFlag = 1;


	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		/*SetBackgroundColor(0,255,0);*/
		ClearDrawScreen();
		/*DrawCircle(300, 230, 200, 0x008080);
		DrawBox(300, 300, 100, 80,80,0x006400);*/

		int newX = manX;
		int newY = manY;

		if (CheckHitKey(KEY_INPUT_UP))
			newY-=2;
		else if (CheckHitKey(KEY_INPUT_DOWN))
			newY+=2;
		else if (CheckHitKey(KEY_INPUT_RIGHT))
			newX+=2;
		else if (CheckHitKey(KEY_INPUT_LEFT))
			newX-=2;

		if ((0 <= newX&&newX < MAXWIDTH*IMGWIDTH) && (0 <= newY&&newY < MAXHEIGHT*IMGHEIGHT))
		{
			int i = newY / IMGHEIGHT;
			int j = newX / IMGWIDTH;
			int i2;
			int j2;
			if (newY%IMGHEIGHT == 0)
				i2 = i;
			else
				i2 = i + 1;
			if (newX%IMGWIDTH == 0)
				j2 = j;
			else
				j2 = j + 1;
			
			if (mapData[i][j] != WALL && mapData[i][j2] != WALL && mapData[i2][j] != WALL && mapData[i2][j2] != WALL)
			{
				manX = newX;
				manY = newY;
			}
			
			if (mapData[i][j] == KEY || mapData[i][j2] == KEY || mapData[i2][j] == KEY || mapData[i2][j2] == KEY)
			{
				keyFlag = 0;
			}
			
			if (mapData[i][j] == GOAL || mapData[i][j2] == GOAL || mapData[i2][j] == GOAL || mapData[i2][j2] == GOAL)
			{
				if (keyFlag == 0)
				{
					isGoal = 1;
				}
			}
			
		}
		
		for (int i = 0; i < MAXHEIGHT; i++)
		{
			for (int j = 0; j < MAXWIDTH; j++)
			{
				switch(mapData[i][j])
				{
					case FIELD:
						DrawGraph(IMGWIDTH*j, IMGHEIGHT*i, handle_field,FALSE );
						
							break;
					case WALL:
						DrawGraph(IMGWIDTH*j, IMGHEIGHT*i, handle_wall ,FALSE);
							
							break;
					case GOAL:
						DrawGraph(IMGWIDTH*j, IMGHEIGHT*i, handle_goal, FALSE);

							break;
					case KEY:
							if (keyFlag)
							{
								DrawGraph(IMGWIDTH*j, IMGHEIGHT*i, handle_key, FALSE);
							}
							else
							{
								DrawGraph(IMGWIDTH*j, IMGHEIGHT*i, handle_field, FALSE);
							}
				
						break;
						



				}
				
				

			}
		}
		DrawGraph(manX, manY, handle_man, FALSE);
		/*DrawGraph(IMGWIDTH * 4, IMGHEIGHT * 1, handle_key, FALSE);*/
		if (isGoal)
		{
			ClearDrawScreen();
			DrawString(640 / 2, 480 / 2, "GOAL!!", GetColor(255, 0, 0));
		}
		/*if (manX == 0)
			manX = 1;
		else if (manY == 0)
			manY = 1;
		else if (manX == 310)
			manX = 309;
		else if (manY == 217)
			manY = 216;*/


		ScreenFlip();
		if (ProcessMessage() == -1)
			break;
	}
	DxLib_End();
	return 0;
}