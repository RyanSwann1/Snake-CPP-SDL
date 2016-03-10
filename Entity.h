#pragma once
#ifndef ENTITY_H
#define ENTITY_H


#include <SDL.h>
struct Entity
{
	Entity()
	{
		m_pos.w = sizeWidth;
		m_pos.h = sizeHeight;
	}

	Entity(const int startXPos, const int startYPos)
	{
		m_pos.x = startXPos;
		m_pos.y = startYPos;
		m_pos.h = sizeHeight;
		m_pos.w = sizeWidth;
	}

	SDL_Rect m_pos;
	int sizeWidth = 22;
	int sizeHeight = 22;
};
#endif // !ENTITY_H