#include "SnakeBot.h"
#include<cstdlib>

SnakeBot::SnakeBot() : Snake(), target(INT_MAX), min(INT_MIN, -1)
{
	body = { { 10,10 } };
}

bool SnakeBot::isAlive()
{
	return body.size() != 0;
}

STATUS_CODE SnakeBot::move()
{
	int x = body[0].first, y = body[0].second;
	int difference = INT_MAX;
	if (min.first == INT_MIN || (x == min.first && y == min.second))
	{
		for (int i = 0; i < apples.size(); i++)
		{
			size_t formula = abs(body[0].first - apples[i].first) +
				abs(body[0].second - apples[i].second);
			if (difference > formula)
			{
				difference = formula;
				min = { apples[i].first, apples[i].second };
			}
		}
	}

	if (min.first != INT_MIN && map[min.first][min.second] != APPLE)
		min.first = INT_MIN;

	if (min.first != INT_MIN)
	{
		short int n = rand() % 2;

		if (n == 0)
		{
			if (body[0].first < min.first)
			{
				x++;
			}
			else if (body[0].first > min.first)
			{
				x--;
			}
		}
		else if (n == 1)
		{
			if (body[0].second < min.second)
			{
				y += 1;
			}
			else if (body[0].second > min.second)
			{
				y -= 1;
			}
		}

		//if there are apples on this position
		Snake::getApples(x, y);

		// INVAKID OPTIMIZATION, mine was O(N)
		body.pop_back();
		body.push_front({ x, y });
	}
	return SNAKE_MOVING;

}