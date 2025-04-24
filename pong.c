#include <stdio.h>
#include <SDL2/SDL.h>

int main()
{
	// Initialize system
	SDL_InitSubSystem(SDL_INIT_VIDEO);

	// Create window and grab surface
	SDL_Window *window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
	640, 480, SDL_WINDOW_SHOWN);
	SDL_Surface *surface = SDL_GetWindowSurface(window);

	// Create player 1's rectange;
	SDL_Rect pl1 = (SDL_Rect) {40, 40, 40, 200};
	Uint32 color = 0xffffffff;
	Uint32 black = 0x00000000;
	SDL_FillRect(surface, &pl1, color);

	// Create player 2's rectange;
	SDL_Rect pl2 = (SDL_Rect) {560, 240, 40, 200};
	SDL_FillRect(surface, &pl2, color);

	// Update the window
	SDL_UpdateWindowSurface(window);
	SDL_Delay(5000);
	
	// Begin event loop
	int running = 1;
	SDL_Event event;
	while(running){
		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT)
		{
			running = 0;
		}
		if(event.key.keysym.sym == SDLK_s)
		{
			SDL_FillRect(surface, &pl1, 0x00000000);
			pl1.y += 10;
			SDL_FillRect(surface, &pl1, color);
		}
		if (event.key.keysym.sym == SDLK_w)
		{
			SDL_FillRect(surface, &pl1, 0x00000000);
			pl1.y -= 10;
			SDL_FillRect(surface, &pl1, color);
		}
		if (event.key.keysym.sym == SDLK_DOWN)
		{
			SDL_FillRect(surface, &pl2, black);
			pl2.y += 10;
			SDL_FillRect(surface, &pl2, color);
		}
		if (event.key.keysym.sym == SDLK_UP)
		{
			SDL_FillRect(surface, &pl2, black);
			pl2.y -= 10;
			SDL_FillRect(surface, &pl2, color);
		}
		SDL_UpdateWindowSurface(window);
		SDL_Delay(10);
	}
	SDL_Quit();
}
