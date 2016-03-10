#pragma once
#ifndef  WINDOW_H
#define WINDOW_H

#include <SDL.h>
class Window
{
public:
	Window();
	~Window();

	SDL_Window* getWindow() const { return m_window; }


	static constexpr int SCREEN_WIDTH = 600;
	static constexpr int SCREEN_HEIGHT = 600;
	static constexpr int SCREEN_FPS = 60;
	static constexpr int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
private:
	SDL_Window* m_window = nullptr;
	SDL_Surface* m_windowSurface = nullptr;

	void createWindow();
	void createSurfaceWindow();
};
#endif // ! WINDOW_H

