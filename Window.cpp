#include "Window.h"
#include <cassert>


Window::Window()
{
	createWindow();
	createSurfaceWindow();
}


Window::~Window()
{
}

void Window::createWindow()
{
	m_window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	assert(m_window != nullptr);
}

void Window::createSurfaceWindow()
{
	m_windowSurface = SDL_GetWindowSurface(m_window);
	assert(m_windowSurface != nullptr);
}



