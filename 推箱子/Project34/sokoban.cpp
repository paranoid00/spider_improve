#include <Windows.h>
#include "Sokoban.h"

GAME_COORD boundary;

void MoveTo(dirction dir, GAME_COORD &Person, int map[][SIZE_Y], int &flag, PGAME_COORD Boxes)
{


	switch (dir)
	{
	case PERSON_LEFT:
		if ((Person.y - 1) >= 0 && (map[Person.x][Person.y - 1] == ROAD || map[Person.x][Person.y - 1] == FLAG))
		{
			map[Person.x][Person.y] = ROAD;
			if (map[Person.x][Person.y - 1] != FLAG)
			{
				map[Person.x][Person.y - 1] = PERSON;
			}
			Person.y--;
		}
		if ((Person.y - 1) >= 0 && map[Person.x][Person.y - 1] == BOX)
		{
			if ((Person.y - 2) >= 0 && (map[Person.x][Person.y - 2] == ROAD || map[Person.x][Person.y - 2] == FLAG))
			{
				if (map[Person.x][Person.y - 2] == FLAG)
					flag++;
				map[Person.x][Person.y] = ROAD;
				map[Person.x][Person.y - 1] = PERSON;
				map[Person.x][Person.y - 2] = BOX;
				for (int i = 0; i < 4; i++)
				{
					if (Boxes[i].y == Person.y - 1 && Boxes[i].x == Person.x)
					{
						Boxes[i].y = Person.y - 2;
						Boxes[i].x = Person.x;
					}
				}
				Person.y--;
			}
		}

		break;
	case PERSON_RIGHT:
		if ((Person.y + 1) <= SIZE_Y && (map[Person.x][Person.y + 1] == ROAD || map[Person.x][Person.y + 1] == FLAG))
		{
			map[Person.x][Person.y] = ROAD;
			if (map[Person.x][Person.y + 1] != FLAG)
			{
				map[Person.x][Person.y + 1] = PERSON;
			}
			Person.y++;
		}
		if ((Person.y + 1) <= SIZE_Y && map[Person.x][Person.y + 1] == BOX)
		{
			if ((Person.y + 2) <= SIZE_Y && (map[Person.x][Person.y + 2] == ROAD || map[Person.x][Person.y + 2] == FLAG))
			{
				if (map[Person.x][Person.y + 2] == FLAG)
					flag++;
				map[Person.x][Person.y] = ROAD;
				map[Person.x][Person.y + 1] = PERSON;
				map[Person.x][Person.y + 2] = BOX;
				for (int i = 0; i < 4; i++)
				{
					if (Boxes[i].y == Person.y + 1 && Boxes[i].x == Person.x)
					{
						Boxes[i].y = Person.y + 2;
						Boxes[i].x = Person.x;
					}
				}
				Person.y++;

			}

		}

		break;
	case PERSON_DOWN:
	{
		if ((Person.x + 1) < SIZE_X && (map[Person.x + 1][Person.y] == ROAD) || map[Person.x+1][Person.y] == FLAG)
		{
			map[Person.x][Person.y] = ROAD;
			if (map[Person.x+1][Person.y ] != FLAG)
				map[Person.x+1][Person.y ] = PERSON;
			Person.x++;

		}
		if ((Person.x + 2) < SIZE_X && map[Person.x + 1][Person.y] == BOX)
		{
			if (map[Person.x + 2][Person.y] == ROAD || map[Person.x + 2][Person.y] == FLAG)
			{
				if (map[Person.x + 2][Person.y] == FLAG)
					flag++;
				map[Person.x][Person.y] = ROAD;
				map[Person.x + 1][Person.y] = PERSON;
				map[Person.x + 2][Person.y] = BOX;
				for (int i = 0; i < 4; i++)
				{
					if ((Boxes[i].x == Person.x + 1) && Boxes[i].y == Person.y)
					{
						Boxes[i].x = Person.x + 2;
						Boxes[i].y = Person.y;

					}
				}
				Person.x++;
			}
		}
		break;
	}
	case PERSON_UP:
	{
		if ((Person.x - 1) < SIZE_X && (map[Person.x - 1][Person.y] == ROAD) || map[Person.x-1][Person.y] == FLAG)
		{
			map[Person.x][Person.y] = ROAD;
			if (map[Person.x - 1][Person.y] != FLAG)
				map[Person.x - 1][Person.y] = PERSON;
			Person.x--;

		}
		if ((Person.x - 2) < SIZE_X && map[Person.x - 1][Person.y] == BOX)
		{
			if (map[Person.x - 2][Person.y] == ROAD || map[Person.x - 2][Person.y] == FLAG)
			{
				if (map[Person.x - 2][Person.y] == FLAG)
					flag++;
				map[Person.x][Person.y] = ROAD;
				map[Person.x - 1][Person.y] = PERSON;
				map[Person.x - 2][Person.y] = BOX;
				for (int i = 0; i < 4; i++)
				{
					if ((Boxes[i].x == Person.x - 1) && Boxes[i].y == Person.y)
					{
						Boxes[i].x = Person.x - 2;
						Boxes[i].y = Person.y;

					}
				}
				Person.x--;
			}
		}
		break;
	}
	}
	
	
}
	
	
void GetWall(MAP_COORD* Wall)
{
	
	Wall[0].left_top.x = 0;
	Wall[0].left_top.y = 0;
	Wall[0].right_bottom.x = 4; 
	Wall[0].right_bottom.y = 4;

	Wall[1].left_top.x = 4;
	Wall[1].left_top.y = 0;
	Wall[1].right_bottom.x = 5;
	Wall[1].right_bottom.y = 1;

	Wall[2].left_top.x = 5;
	Wall[2].left_top.y = 0;
	Wall[2].right_bottom.x = 10;
	Wall[2].right_bottom.y = 3;

	Wall[3].left_top.x = 0;
	Wall[3].left_top.y = 4;
	Wall[3].right_bottom.x = 2;
	Wall[3].right_bottom.y = 5;

	Wall[4].left_top.x = 8;
	Wall[4].left_top.y = 3;
	Wall[4].right_bottom.x = 10;
	Wall[4].right_bottom.y = 4;

	Wall[5].left_top.x = 0;
	Wall[5].left_top.y = 5;
	Wall[5].right_bottom.x = 5;
	Wall[5].right_bottom.y = 8;

	Wall[6].left_top.x = 5;
	Wall[6].left_top.y = 7;
	Wall[6].right_bottom.x = 6;
	Wall[6].right_bottom.y = 8;

	Wall[7].left_top.x = 6;
	Wall[7].left_top.y = 4;
	Wall[7].right_bottom.x = 10;
	Wall[7].right_bottom.y = 8;
	
}



void InitCoordinate(GAME_COORD &Person, GAME_COORD *Boxes)

{
	
	Person.x = 4;
	Person.y = 5;
	Boxes[0].x = 3;
	Boxes[0].y = 4;
	Boxes[2].x = 4;
	Boxes[2].y = 4;
	Boxes[1].x = 3;
	Boxes[1].y = 6;
	Boxes[3].x = 5;
	Boxes[3].y = 5;

}
// 设置边界坐标
void SetBoundary(int x, int y)
{
	boundary.x = x;
	boundary.y = y;
}

// 获得边界坐标
PGAME_COORD GetBoundary()
{
	return &boundary;
}