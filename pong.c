#include <stdio.h>
#include <SDL2/SDL.h>

int main()
{
	SDL_InitSubSystem(SDL_INIT_VIDEO);
	SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,640, 480, 0);
	SDL_Delay(5000);
	SDL_Quit();
}
