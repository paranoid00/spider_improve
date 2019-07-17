#include "Array.h"

void ArrayInit(int map[][SIZE_Y])
{
	memset(map, 0, sizeof(map));
	for (int j = 4, i = 1; i < 5; i++)
	{
		map[i][j] = ROAD;
	}
	for (int i = 4, j = 2; j < 6; j++)
	{
		map[i][j] = ROAD;
	}
	for (int i = 3, j = 5; i < 7; i++)
	{
		map[i][j] = ROAD;
	}
	for (int i = 3, j = 4; j < 8; j++)
	{
		map[i][j] = ROAD;
	}
	map[1][4] = map[3][7] = map[4][2] = map[6][5] = FLAG;
	map[4][5] = PERSON;
	map[3][4] = map[4][4] = map[3][6] = map[5][5] = BOX;
}

