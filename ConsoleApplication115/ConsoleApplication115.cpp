#include<iostream>
#define print(n) std::cout << n << std::endl;

#include<windows.h>
#include<deque>

#include<vector>
#include "Snake.h"

#include "Defines.h"
#include<list>

#include "SnakeBot.h"
#define field std::vector<std::string>
std::vector<std::pair<int, int>> apples;

Snake player;
SnakeBot bot;

field map;

std::vector<std::string> FieldConfig(const int rows,
	const int cols)
{
	// Resizing with the exact neede positions
	field map(rows);
	map[0] = std::string(rows, '#');
	// ! Not sure if it takes exactly cols size
	for (int i = 1; i < rows; i++)
	{
		map[i] = std::string(rows, ' ');
		map[i][0] = '#';
		map[i][cols - 1] = '#';
	}
	map[map.size() - 1] = std::string(rows, '#');
	// ! Add obstacles and power ups 

	return map;
}
inline void printMap(field map)
{
	print("SCORE: " << player.getScore());

	if (bot.isAlive())
		print("ENEMY SCORE: " << bot.getScore());

	for (const auto& k : map)
	{
		print(k);
	}
}
#include<ctime>
std::vector<std::pair<int, int>> addApples()
{
	srand(time(0));
	std::vector<std::pair<int, int>> item;
	int size = rand() % (map.size() / 4);
	for (int i = 0; i < size; i++)
	{
		int row = rand() % map.size();
		int col = rand() % map[0].size();
		if (map[row][col] == ' ')
		{
			map[row][col] = ITEMS::APPLE;
			item.push_back({ row, col });
		}
	}
	return item;
}

STATUS_CODE updateField(const KEY position, KEY& newPos)
{
	STATUS_CODE code = player.move(position);
	bot.move();

	if (code == SNAKE_DEAD_OUT_OF_RANGE)
		return SNAKE_DEAD_OUT_OF_RANGE;
	else if (code == SNAKE_DEAD_CRASHED)
		return SNAKE_DEAD_CRASHED;

	field updateMap = FieldConfig(map.size(), map[0].size());

	// Apply snake head

	player.update(updateMap);
	bot.update(updateMap);

	for (int i = 0; i < apples.size(); i++)
	{
		updateMap[apples[i].first][apples[i].second] = ITEMS::APPLE;
	}
	newPos = position;
	map = updateMap;

	if (apples.empty())
		apples = addApples();

	return SNAKE_MOVING;
}
const int xSize = 25, ySize = 25;
int main()
{
	system("color 0f");

	map = FieldConfig(xSize, ySize);
	map[1][1] = SNAKE_HEAD;
	map[10][10] = SNAKE_HEAD;

	STATUS_CODE snake = SNAKE_MOVING;
	KEY position = NONE;
	system("pause");
	while (snake != SNAKE_DEAD_OUT_OF_RANGE && snake != SNAKE_DEAD_CRASHED)
	{
		printMap(map);
		if (GetAsyncKeyState(KEY::UP))
		{
			snake = updateField(KEY::UP, position);
		}
		else if (GetAsyncKeyState(KEY::DOWN))
		{
			snake = updateField(KEY::DOWN, position);
		}
		else if (GetAsyncKeyState(KEY::LEFT))
		{
			snake = updateField(KEY::LEFT, position);
		}
		else if (GetAsyncKeyState(KEY::RIGHT))
		{
			snake = updateField(KEY::RIGHT, position);
		}
		else
		{
			snake = updateField(position, position);
		}
		system("cls");
	}
	switch (snake)
	{
	case SNAKE_DEAD_OUT_OF_RANGE:
		print("\t\t\t\t\tOut of range ! \n");
		break;
	case SNAKE_DEAD_CRASHED:
		print("\t\t\t\t\t You've crashed into your tale ! \n");
		break;
	default:
		print("A fatal error occured ! \n");
	}
	system("color 0c");

	print("\t\t\t\t\tThe snake died! \n");
	system("pause > nul");
}