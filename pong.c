#include <stdio.h>
#include <SDL2/SDL.h>

static int movement_speed = 5;
static const Uint32 white = 0xffffffff;
static const Uint32 black = 0x00000000;
static const int refresh_rate = 60;
int ballX = 5;
int ballY = 4;

struct circle
{
	int x;
	int y;
	int r;
};

void draw_circle(SDL_Surface* surface, struct circle* circle, Uint32 color)
{
	int radiusSquared = circle->r * circle->r;
	for (int x = circle->x - circle->r; x <= circle->x + circle->r; x++){
		for (int y = circle->y - circle->r; y <= circle->y + circle->r; y++){
			if ((circle->x - x) * (circle->x - x) + (circle->y - y) * (circle->y - y) <= radiusSquared)
			{
				SDL_Rect pixel = (SDL_Rect) {x, y, 1, 1};
				SDL_FillRect(surface, &pixel, color);
			}
		}
	}
}

void move_ball(SDL_Surface* surface, struct circle* ball, SDL_Rect* pl1, SDL_Rect* pl2)
{
	if ((pl2->y <= ball->y) && (ball->y <= pl2->y+200) && (ball->x + ballX >= pl2->x))
	{
		ballX *= -1;
	}
	else if ((pl1->y <= ball->y) && (ball->y <= pl1->y+200) && (ball->x + ballX <= pl1->x + 40))
	{
		ballX *= -1;
	}
	if (ball->y + ballY >= 480)
	{
		ballY *= -1;
	}
	else if (ball->y + ballY <= 0)
	{
		ballY *= -1;
	}
	draw_circle(surface, ball, black);
	ball->x += ballX;
	ball->y += ballY;
	draw_circle(surface, ball, white);
	SDL_FillRect(surface, pl1, white);
	SDL_FillRect(surface, pl2, white);
}

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

	// Initialize ball
	struct circle circle;
	circle.x = 320;
	circle.y = 240;
	circle.r = 10;
	draw_circle(surface, &circle, white);

	int move_ball_x = 5;
	int move_ball_y = 5;

	// Decorate window
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

		// Update ball position
		move_ball(surface, &circle, &pl1, &pl2);

		// Update window
		SDL_FillRect(surface, &middle, white);
		SDL_UpdateWindowSurface(window);

		// Set time between frames
		SDL_Delay(1000/refresh_rate);
	}
	SDL_Quit();
}