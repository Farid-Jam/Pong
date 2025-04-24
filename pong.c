#include <stdio.h>
#include <SDL2/SDL.h>

static int movementSpeed = 10;
static const Uint32 white = 0xffffffff;
static const Uint32 black = 0x00000000;

// Function that handles moving of players
void move_rect(SDL_Surface* surface, SDL_Rect* rect, int speed){
	SDL_FillRect(surface, rect, black);
	rect->y += speed;
	SDL_FillRect(surface, rect, white);
}

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
	SDL_FillRect(surface, &pl1, white);

	// Create player 2's rectange;
	SDL_Rect pl2 = (SDL_Rect) {560, 240, 40, 200};
	SDL_FillRect(surface, &pl2, white);

	// Update the window
	SDL_UpdateWindowSurface(window);
	SDL_Delay(5000);
	
	// Begin event loop
	int running = 1;
	SDL_Event event;
	while(running){
		const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);
		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT)
		{
			running = 0;
		}
		if(event.type == SDL_KEYDOWN)
		{
			if(event.key.keysym.sym == SDLK_s)
			{
				move_rect(surface, &pl1, +movementSpeed);
			}
			if (event.key.keysym.sym == SDLK_w)
			{
				move_rect(surface, &pl1, -movementSpeed);
			}
			if (event.key.keysym.sym == SDLK_DOWN)
			{
				move_rect(surface, &pl2, +movementSpeed);
			}
			if (event.key.keysym.sym == SDLK_UP)
			{
				move_rect(surface, &pl2, -movementSpeed);
			}
		}
		SDL_UpdateWindowSurface(window);
		SDL_Delay(10);
	}
	SDL_Quit();
}
