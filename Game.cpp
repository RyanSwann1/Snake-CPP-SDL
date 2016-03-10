#include "Game.h"
#include "Window.h"
#include "Character.h"

#include <cassert>

Game::Game(Window& window)
{
	createRenderer(window);
	m_nextFoodSpawn = 2000;
}


Game::~Game()
{
	
}

void Game::render(const Window& window, Character& player)
{
	SDL_RenderClear(m_renderer);

	//Render player
	SDL_SetRenderDrawColor(m_renderer, 0, 255, 255, 255);
	for (auto &i : player.getSnake()) 
	{
		
		SDL_RenderFillRect(m_renderer, &i.m_pos);
	}

	//Render players head
	SDL_SetRenderDrawColor(m_renderer, 175, 175, 175, 175);
	SDL_RenderFillRect(m_renderer, &player.getSnakeHead());

	//Render Food
	SDL_SetRenderDrawColor(m_renderer, 255, 0, 255, 255);
	for (auto &i : m_food)
	{
		SDL_RenderFillRect(m_renderer, &i.m_pos);
	}

	//Render background
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

	//Apply
	SDL_RenderPresent(m_renderer);
}

void Game::update(Character& player)
{
	spawnFood();
	player.moveManagement();

	playerBounds(player);
	collisionManagement(player);
}

void Game::collisionManagement(Character & player)
{
	//Player to Food Collision
	for (int snakeObject = 0; snakeObject < player.getSnake().size(); snakeObject++)
	{
		for (int foodObject = 0; foodObject < m_food.size(); foodObject++)
		{
			//If collision detected
			if (player.collision(player.getSnake()[snakeObject], m_food[foodObject]))
			{
				m_food.erase(m_food.begin() + foodObject); //Remove food piece from game
				player.eat();
			}
		}
	}
}

void Game::playerBounds(Character & player)
{
	static const int maxPos = 575;
	static const int minPos = 0;
	if (player.getSnake().front().m_pos.x < minPos) {
		player.setXPosition(maxPos);
	}
	if (player.getSnake().front().m_pos.x > maxPos) {
		player.setXPosition(minPos);
	}
	if (player.getSnake().front().m_pos.y < minPos) {
		player.setYPosition(maxPos);
	}
	if (player.getSnake().front().m_pos.y > maxPos) {
		player.setYPosition(minPos);
	}
}

void Game::createRenderer(const Window& window)
{
	m_renderer = SDL_CreateRenderer(window.getWindow(), -1, SDL_RENDERER_ACCELERATED);
	assert(m_renderer != nullptr);
}


int Game::getRandomNumber(const int val1, const int val2) const
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(val1, val2);

	return dis(gen);
}


void Game::spawnFood()
{
	static constexpr int minPos = 20;
	static constexpr int maxPos = 570;

	int spawnFood = 0;
	int randPos = 0;
	int spawnXPos = 0;
	int spawnYPos = 0;
	bool validSpawn = false;

	/*
	Javawag: so takes a random point, divides by 25... but coz its an int it rounds down
Javawag: so imagine its 30.... 30 / 25 = 1 (it drops the .whatever)
Javawag: and then 1 x 25 = 25 :D
Javawag: doesnt work with floats though, obv :D

	
	
	*/

    //https://pastee.org/uazs2

	Uint32 currentTime = SDL_GetTicks();
	if (SDL_TICKS_PASSED(currentTime, m_nextFoodSpawn))
	{
		while (!validSpawn)
		{
			//Get 'X' position
			spawnXPos = getRandomNumber(minPos, maxPos) / 25 * 25;
			//while (spawnXPos % 25 != 0) {
			//	spawnXPos = getRandomNumber(minPos, maxPos);
			//}

			//Get 'Y' Position
			spawnYPos = getRandomNumber(minPos, maxPos) / 25 * 25;
			//while (spawnYPos % 25 != 0) {
			//	spawnYPos = getRandomNumber(minPos, maxPos);
			//}
			//Check to see if food is on requested position
			for (auto &i : m_food)
			{
				if (spawnXPos == i.m_pos.x && spawnYPos == i.m_pos.y) {
					validSpawn = false;
					break;
				}
			}
			//If there is no food on requested position
			validSpawn = true;
		}
		m_food.push_back(Entity(spawnXPos, spawnYPos));
		m_nextFoodSpawn += FOOD_SPAWN_TIME;

	}

}
