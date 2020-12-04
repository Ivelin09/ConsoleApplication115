#ifndef SNAKE_BOT_H
#define SNAKE_BOT_H

#include "Snake.h"

extern std::vector<std::string> map;
extern std::vector<std::pair<int, int>> apples;

extern const int xSize, ySize;

class SnakeBot : public Snake
{
private:
	long long int target;
	std::pair<int, int> min;
	// asd
	std::vector<std::pair<int, int>> paths;
public:
	STATUS_CODE move();
	bool isAlive();

	SnakeBot();
};

#endif
