
/************** 头文件 ****************/
#include<windows.h>
#include "Sokoban.h"

// 当用于操作时进行的逻辑处理。
// 本游戏只使用到了键盘上下左右键控制。



//函数定义
//GAME_COORD GetPerson() {return Person; };
//GAME_COORD* GetBoxes() {return Boxes; };
//int GetFlag() {return flag; };

   void OnKeyDown(DWORD vk, GAME_COORD &Person, int map[][SIZE_Y], int &flag, PGAME_COORD Boxes)
{
	switch (vk) // virtual key value
	{
	case VK_LEFT:
		MoveTo(PERSON_LEFT, Person,map,flag,Boxes);
		break;
	case VK_RIGHT:
		MoveTo(PERSON_RIGHT,Person,map,flag,Boxes);
		break;
	case VK_UP:
		MoveTo(PERSON_UP, Person, map, flag,Boxes);
		break;
	case VK_DOWN:
		MoveTo(PERSON_DOWN, Person, map, flag,Boxes);
		break;
	}
	
}

// 游戏的初始化，
// 创建游戏的内部数据结构和系统对象。
void CreateGame(HWND hwnd, // 主窗口句柄
	dirction init_dir,int map[][SIZE_Y], GAME_COORD &Person, GAME_COORD *Boxes,int x,int y)
{
	ArrayInit(map);
	InitCoordinate(Person, Boxes);
	SetBoundary(x, y);
}
