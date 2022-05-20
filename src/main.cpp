#include <iostream>
#include "network/Neuron.h"
#include "network/Connection.h"
#include "network/Gene.h"
#include "SDL.h"

using std::cout;

// int main()
// {
// 	Neuron n;
// 	Neuron n2;
// 	Connection n3;
// 	std::cout << "Hello World" << n.innovationNumber << n2.innovationNumber << n3.innovationNumber << std::endl;
// }

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Failed to initialize the SDL2 library\n";
		return -1;
	}

	SDL_Window *window = SDL_CreateWindow("SDL2 Window",
																				SDL_WINDOWPOS_CENTERED,
																				SDL_WINDOWPOS_CENTERED,
																				680, 480,
																				0);

	std::cout << " test " << std::endl;

	if (!window)
	{
		std::cout << "Failed to create window\n";
		return -1;
	}

	SDL_Surface *window_surface = SDL_GetWindowSurface(window);

	if (!window_surface)
	{
		std::cout << "Failed to get the surface from the window\n";
		return -1;
	}

	SDL_UpdateWindowSurface(window);

	bool quit = false;
	SDL_Event e;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
	}
}