
/************** ͷ�ļ� ****************/
#include<windows.h>
#include "Sokoban.h"

// �����ڲ���ʱ���е��߼�����
// ����Ϸֻʹ�õ��˼����������Ҽ����ơ�



//��������
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

// ��Ϸ�ĳ�ʼ����
// ������Ϸ���ڲ����ݽṹ��ϵͳ����
void CreateGame(HWND hwnd, // �����ھ��
	dirction init_dir,int map[][SIZE_Y], GAME_COORD &Person, GAME_COORD *Boxes,int x,int y)
{
	ArrayInit(map);
	InitCoordinate(Person, Boxes);
	SetBoundary(x, y);
}
