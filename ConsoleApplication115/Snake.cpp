#include "Snake.h"
#include<utility>

#include "Defines.h"

Snake::Snake() // : body{ {1,1 } }
{
	body.push_back({ 1,1 });
}

void Snake::getApples(const int x, const int y)
{
	std::vector<std::pair<int, int>>::iterator it = apples.begin();
	for (; it != apples.end();)
	{
		if (x == it->first && y == it->second)
		{
			body.push_back({ body[0].first, body[0].second });
			it = apples.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Snake::update(field& updateMap)
{
	updateMap[this->body[0].first][this->body[0].second] = SNAKE_HEAD;

	for (int i = 1; i < this->body.size(); i++)
	{
		updateMap[this->body[i].first][this->body[i].second] = SNAKE_TAIL;
	}
}

int Snake::getScore() const
{
	return body.size() - 1;
}

STATUS_CODE Snake::move(const KEY position)
{
	int x = body[0].first, y = body[0].second;

	switch (position)
	{
	case KEY::UP:
		x = body[0].first - 1;
		break;
	case KEY::DOWN:
		x = body[0].first + 1;
		break;
	case KEY::LEFT:
		y = body[0].second - 1;
		break;
	case KEY::RIGHT:
		y = body[0].second + 1;
		break;
	}

	if (x == map.size() - 1 || y == map[0].size() - 1 ||
		x == 0 || y == 0)
		return SNAKE_DEAD_OUT_OF_RANGE;
	else if (map[x][y] == 'x')
		return SNAKE_DEAD_CRASHED;

	getApples(x, y);

	// INVAKID OPTIMIZATION, mine was O(N)
	body.pop_back();
	body.push_front({ x, y });

}