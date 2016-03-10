#pragma once

#ifndef CHARACTER_h
#define CHARACTER_H



#include "MoveDirection.h"
#include "Entity.h"

#include <vector>

struct Entity;
class Character
{
public:
	Character();

	void moveManagement();

	void eat();



	bool collision(const Entity& player, const Entity& entity);

	//Get
	std::vector<Entity> getSnake() const { return m_snake; }
	SDL_Rect getSnakeHead() { return m_snake.front().m_pos; }

	//Set
	void setXPosition(const int xPos) { m_snake.front().m_pos.x = xPos; }
	void setYPosition(const int yPos) { m_snake.front().m_pos.y = yPos; }

	static constexpr int START_Y_POS = 275;
	static constexpr int START_X_POS = 275;

private:
	void movementDirection();
	void move();
	void reset();
	void tailManagement();

	std::vector<Entity> m_snake;
	std::vector<Entity> m_snakeOldPos;

	unsigned int m_movementSpeed = 0;
	int m_velY = 0;
	int m_velX = 0;
	unsigned int m_nextMove = 90;
	unsigned int m_moveTime = 90;
	MoveDirection m_dir;

};
#endif // !CHARACTER_h
