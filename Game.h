#pragma once

#ifndef GAME_H
#define GAME_H

#include "Entity.h"
#include <SDL.h>
#include <vector>
#include <random>

struct Entity;
class Character;
class Window;
class Game
{
public:
	Game(Window& window);
	~Game();

	void render(const Window& window, Character& player);
	void endGame() { m_gameOver = true; }
	void update(Character& player);
	void collisionManagement(Character& player);
	void playerBounds(Character& player);

	bool isGameOver() const { return m_gameOver; }
	int getRandomNumber(const int val1, const int val2) const;

private:
	void createRenderer(const Window& window);	
	void spawnFood();

	const int FOOD_SPAWN_TIME = 1500;
	int m_nextFoodSpawn = 0;
	std::vector<Entity> m_food;
	bool m_gameOver = false;
	SDL_Renderer* m_renderer = nullptr;
};
#endif // !GAME_H
