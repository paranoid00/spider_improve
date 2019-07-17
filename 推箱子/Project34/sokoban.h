#include<windows.h>
#include"Array.h"

// 人的方向
typedef enum _dirction
{
	PERSON_UP,
	PERSON_DOWN,
	PERSON_LEFT,
	PERSON_RIGHT,
}dirction;



// 游戏坐标
typedef struct _GAME_COORD
{
	short x;
	short y;
}GAME_COORD, *PGAME_COORD;



//矩形坐标结构体
typedef struct _MAP_COORD {
	GAME_COORD left_top;
	GAME_COORD right_bottom;
}MAP_COORD,*PMAP_COORD;



//初始化坐标
void InitCoordinate(GAME_COORD &Person, GAME_COORD *Boxes);
void GetWall(MAP_COORD*);



/// game_opration.c 中的接口函数

//GAME_COORD GetPerson();
//GAME_COORD* GetBoxes();
//int GetFlag();

void CreateGame(HWND hwnd, // 主窗口句柄
	dirction init_dir,int map[][SIZE_Y], GAME_COORD &Person, GAME_COORD *Boxes,int ,int);

void MoveTo(dirction dir,GAME_COORD &Person, int map[][SIZE_Y], int &flag, PGAME_COORD Boxes);

void OnKeyDown(DWORD vk, GAME_COORD &Person, int map[][SIZE_Y], int &flag, PGAME_COORD Boxes);

void SetBoundary(int x, int y);
PGAME_COORD  GetBoundary();