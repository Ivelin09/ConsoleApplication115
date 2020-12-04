#ifndef SNAKE_H
#define SNAKE_H

#include<deque>
#include<vector>

#include<string>

#include "Defines.h"

extern std::vector<std::string> map;
extern std::vector<std::pair<int, int>> apples;

#define field std::vector<std::string>

struct Snake
{
	std::deque<std::pair<int, int>> body;

	Snake();

	int getScore() const;
	virtual STATUS_CODE move(const KEY position);

	void update(field& updateMap);
protected:
	void getApples(const int x, const int y);
};

#endif