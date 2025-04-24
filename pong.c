#include <stdio.h>
#include <SDL2/SDL.h>

static int movement_speed = 5;
static const Uint32 white = 0xffffffff;
static const Uint32 black = 0x00000000;
static const int refresh_rate = 60;

// Function that handles moving of players
void move_rect(SDL_Surface* surface, SDL_Rect* rect, int speed)
{
	SDL_Rect* rect2 = rect;
	if (rect2->y + speed <= 0)
	{
		SDL_FillRect(surface, rect, black);
		rect->y = 0;
		SDL_FillRect(surface, rect, white);
	} else if (rect->y + speed >= 280)
	{
		SDL_FillRect(surface, rect, black);
		rect->y = 280;
		SDL_FillRect(surface, rect, white);
	} 
	else 
	{
		SDL_FillRect(surface, rect, black);
		rect->y += speed;
		SDL_FillRect(surface, rect, white);
	}
}

int main()
{
	// Initialize system
	SDL_InitSubSystem(SDL_INIT_VIDEO);

	// Create window and grab surface
	SDL_Window *window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
	640, 480, SDL_WINDOW_SHOWN);
	SDL_Surface *surface = SDL_GetWindowSurface(window);

	SDL_Rect middle = (SDL_Rect) {320, 0, 1, 480};
	SDL_FillRect(surface, &middle, white);

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

		// Handle player inputs
		if(keyboard_state_array[SDL_SCANCODE_S] && !(keyboard_state_array[SDL_SCANCODE_UP] || keyboard_state_array[SDL_SCANCODE_DOWN] || keyboard_state_array[SDL_SCANCODE_W]))
		{
			move_rect(surface, &pl1, +movement_speed);
		}
		if (keyboard_state_array[SDL_SCANCODE_W] && !(keyboard_state_array[SDL_SCANCODE_UP] || keyboard_state_array[SDL_SCANCODE_DOWN] || keyboard_state_array[SDL_SCANCODE_S]))
		{
			move_rect(surface, &pl1, -movement_speed);
		}
		if (keyboard_state_array[SDL_SCANCODE_DOWN] && !(keyboard_state_array[SDL_SCANCODE_UP] || keyboard_state_array[SDL_SCANCODE_S] || keyboard_state_array[SDL_SCANCODE_W]))
		{
			move_rect(surface, &pl2, +movement_speed);
		}
		if (keyboard_state_array[SDL_SCANCODE_UP] && !(keyboard_state_array[SDL_SCANCODE_S] || keyboard_state_array[SDL_SCANCODE_DOWN] || keyboard_state_array[SDL_SCANCODE_W]))
		{
			move_rect(surface, &pl2, -movement_speed);
		}
		if (keyboard_state_array[SDL_SCANCODE_S] && keyboard_state_array[SDL_SCANCODE_UP] && !(keyboard_state_array[SDL_SCANCODE_DOWN] || keyboard_state_array[SDL_SCANCODE_W]))
		{
			move_rect(surface, &pl2, -movement_speed);
			move_rect(surface, &pl1, +movement_speed);
		}
		if (keyboard_state_array[SDL_SCANCODE_S] && keyboard_state_array[SDL_SCANCODE_DOWN] && !(keyboard_state_array[SDL_SCANCODE_UP] || keyboard_state_array[SDL_SCANCODE_W]))
		{
			move_rect(surface, &pl2, +movement_speed);
			move_rect(surface, &pl1, +movement_speed);
		}
		if (keyboard_state_array[SDL_SCANCODE_W] && keyboard_state_array[SDL_SCANCODE_UP] && !(keyboard_state_array[SDL_SCANCODE_DOWN] || keyboard_state_array[SDL_SCANCODE_S]))
		{
			move_rect(surface, &pl2, -movement_speed);
			move_rect(surface, &pl1, -movement_speed);
		}
		if (keyboard_state_array[SDL_SCANCODE_W] && keyboard_state_array[SDL_SCANCODE_DOWN] && !(keyboard_state_array[SDL_SCANCODE_UP] || keyboard_state_array[SDL_SCANCODE_S]))
		{
			move_rect(surface, &pl2, +movement_speed);
			move_rect(surface, &pl1, -movement_speed);
		}
		if (keyboard_state_array[SDL_SCANCODE_W] && keyboard_state_array[SDL_SCANCODE_DOWN] && keyboard_state_array[SDL_SCANCODE_UP] && !(keyboard_state_array[SDL_SCANCODE_S]))
		{
			move_rect(surface, &pl1, -movement_speed);
		}
		if (keyboard_state_array[SDL_SCANCODE_S] && keyboard_state_array[SDL_SCANCODE_DOWN] && keyboard_state_array[SDL_SCANCODE_UP] && !(keyboard_state_array[SDL_SCANCODE_W]))
		{
			move_rect(surface, &pl1, +movement_speed);
		}
		if (keyboard_state_array[SDL_SCANCODE_W] && keyboard_state_array[SDL_SCANCODE_S] && keyboard_state_array[SDL_SCANCODE_UP] && !(keyboard_state_array[SDL_SCANCODE_DOWN]))
		{
			move_rect(surface, &pl2, -movement_speed);
		}
		if (keyboard_state_array[SDL_SCANCODE_W] && keyboard_state_array[SDL_SCANCODE_S] && keyboard_state_array[SDL_SCANCODE_DOWN] && !(keyboard_state_array[SDL_SCANCODE_UP]))
		{
			move_rect(surface, &pl2, +movement_speed);
		}

		// Update window
		SDL_UpdateWindowSurface(window);

		// Set time between frames
		SDL_Delay(refresh_rate/6);
	}
	SDL_Quit();
}
