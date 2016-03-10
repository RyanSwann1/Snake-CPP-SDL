#include "Character.h"
#include <iostream>


Character::Character()
{
	m_movementSpeed = 25;
	m_snake.push_back(Entity(START_X_POS, START_Y_POS));
	m_dir = MoveDirection::NO_DIRECTION;

}


void Character::moveManagement()
{

	Uint32 currentTime = SDL_GetTicks();
	if (SDL_TICKS_PASSED(currentTime, m_moveTime))
	{
		//Get position of snake before movement
		for (int i = 0; i < m_snake.size(); i++)
		{
			int currentXPos = m_snake[i].m_pos.x;
			int currentYPos = m_snake[i].m_pos.y;

			m_snakeOldPos.push_back(Entity(currentXPos, currentYPos));
		}

		movementDirection();
		//move();
		move(); //Check to see whether player has moved in on themselves
		//Keep tail showing even when player is still
		if (m_dir != MoveDirection::NO_DIRECTION)
		{
			tailManagement();
		}

		//Clear all old positions

		m_snakeOldPos.clear();
		m_moveTime += m_nextMove;
	}
}


void Character::movementDirection()
{
	const Uint8 *keyState = SDL_GetKeyboardState(NULL);

	//Get movement Direction
	if (m_dir != MoveDirection::LEFT)
	{
		//Move Right
		if (keyState[SDL_SCANCODE_D]) {
			//m_snake.front().m_pos.x += m_movementSpeed;
			m_dir = MoveDirection::RIGHT;
			return;
		}
	}

	if (m_dir != MoveDirection::RIGHT)
	{
		//Move Left
		if (keyState[SDL_SCANCODE_A]) {
			//m_snake.front().m_pos.x -= m_movementSpeed;
			m_dir = MoveDirection::LEFT;
			return;
		}
	}

	if (m_dir != MoveDirection::UP)
	{
		//Move Down
		if (keyState[SDL_SCANCODE_S]) {
			//m_snake.front().m_pos.y += m_movementSpeed;
			m_dir = MoveDirection::DOWN;
			return;
		}
	}

	if (m_dir != MoveDirection::DOWN)
	{
		//Move Up
		if (keyState[SDL_SCANCODE_W]) {
			//m_snake.front().m_pos.y -= m_movementSpeed;
			m_dir = MoveDirection::UP;
			return;
		}
	}
}

void Character::move()
{
	//Test to see whether requested movement will move snake into itself
	if (m_dir == MoveDirection::RIGHT)
	{
		m_snake.front().m_pos.x += m_movementSpeed;
		for (auto i : m_snakeOldPos)
		{
			if (m_snake.front().m_pos.x == i.m_pos.x && m_snake.front().m_pos.y == i.m_pos.y) {
				reset();
			}
		}
		//m_snake.front().m_pos.x -= m_movementSpeed;
	}
	if (m_dir == MoveDirection::LEFT)
	{
		m_snake.front().m_pos.x -= m_movementSpeed;
		for (auto i : m_snakeOldPos)
		{
			if (m_snake.front().m_pos.x == i.m_pos.x && m_snake.front().m_pos.y == i.m_pos.y) {
				reset();
			}
		}
	}

	if (m_dir == MoveDirection::DOWN)
	{
		m_snake.front().m_pos.y += m_movementSpeed;
		for (auto i : m_snakeOldPos)
		{
			if (m_snake.front().m_pos.x == i.m_pos.x && m_snake.front().m_pos.y == i.m_pos.y) {
				reset();
			}
		}
	}

	if (m_dir == MoveDirection::UP)
	{
		m_snake.front().m_pos.y -= m_movementSpeed;
		for (auto i : m_snakeOldPos)
		{
			if (m_snake.front().m_pos.x == i.m_pos.x && m_snake.front().m_pos.y == i.m_pos.y) {
				reset();
			}
		}
	}

	if (m_dir == MoveDirection::NO_DIRECTION)
	{
		return;
	}
}


void Character::tailManagement()
{	
	//Move the tail
	for (int i = 1; i < m_snake.size(); i++)
	{
		m_snake[i].m_pos = m_snakeOldPos[i - 1].m_pos;
	}
}

bool Character::collision(const Entity & player, const Entity & entity)
{
	//Calculate player colliisons
	int playerLeft = player.m_pos.x;
	int playerRight = player.m_pos.x + player.m_pos.w;
	int playerTop = player.m_pos.y;
	int playerBot = player.m_pos.y + player.m_pos.h;

	//Calculate entity collisions
	int entityLeft = entity.m_pos.x;
	int entityRight = entity.m_pos.x + entity.m_pos.w;
	int entityTop = entity.m_pos.y;
	int entityBot = entity.m_pos.y + entity.m_pos.h;

	//Find collisions
	if (playerLeft >= entityRight) {
		return false;
	}
	if (playerRight <= entityLeft) {
		return false;
	}
	if (playerBot <= entityTop) {
		return false;
	}
	if (playerTop >= entityBot) {
		return false;
	}

	//No Collision
	return true;
}



void Character::eat()
{
	m_snake.push_back(Entity()); //Add extra body part to snake 
}


void Character::reset()
{
	m_snake.clear();
	m_snake.push_back(Entity(START_X_POS, START_Y_POS));
	m_dir = MoveDirection::NO_DIRECTION;
}