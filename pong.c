#include <stdio.h>
#include <SDL2/SDL.h>

static int player_speed;
static const Uint32 white = 0xffffffff;
static const Uint32 black = 0x00000000;
static const int refresh_rate = 60;
int ballX = 5;
int ballY = 4;
int max_speed = 15;
int player1Score = 0;
int player2Score = 0;
double maxOffset = .75;
int playerHeight = 120;
int playerWidth = 30;
int windowWidth;
int windowHeight;
int ballRadius = 10;
int borderWidth = 20;
int middleLineWidth = 3;
int ai = 1; // 0 for off, any other number for on

struct circle
{
	int x;
	int y;
	int r;
};

int predict_ball(struct circle* ball, SDL_Rect* ai)
{
	int yBall = ballY;
	while (ball->x + ball->r + ballX < ai->x)
	{
		if (ball->y + ball->r + yBall >= windowHeight - borderWidth || ball->y - ball->r+ yBall <= borderWidth)
		{
			yBall *= -1;
		}
		ball->x += ballX;
		ball->y += yBall;
	}
	return ball->y;
}

void draw_map(SDL_Surface* surface)
{
	// Create top and bottom borders
	SDL_Rect topBorder = (SDL_Rect) {0, 0, windowWidth, borderWidth};
	SDL_Rect bottomBorder = (SDL_Rect) {0, windowHeight-borderWidth, windowWidth, borderWidth};
	SDL_FillRect(surface, &topBorder, white);
	SDL_FillRect(surface, &bottomBorder, white);

	// Create dotted white line down the middle
	for (int i = borderWidth; i <= windowHeight; i += 2*borderWidth)
	{
		SDL_Rect middleBox = (SDL_Rect) {windowWidth/2 - borderWidth/2, i, borderWidth, borderWidth};
		SDL_FillRect(surface, &middleBox, white);
	}
}

// Function that draws circles
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

// Function that handles moving of the ball
void move_ball(SDL_Surface* surface, struct circle* ball, SDL_Rect* pl1, SDL_Rect* pl2)
{
	// If ball collidies with player 2, calculate offset and alter x, y, speeds occrdingly while also flipping x direction
	if ((pl2->y <= ball->y) && (ball->y <= pl2->y+playerHeight) && (ball->x + ballX >= pl2->x))
	{
		float offset = (float)(ball->y - (pl2->y + playerHeight/2)) / playerHeight;
		if (offset < -1) offset = -1;
		if (offset > 1) offset = 1;
		offset *= maxOffset;
		ballY = max_speed * offset;
		if (offset < 0) offset = -offset;
		ballX = -max_speed * (1 - offset);
	}

	// If ball collidies with player 1, calculate offset and alter x, y, speeds occrdingly while also flipping x direction
	if ((pl1->y <= ball->y) && (ball->y <= pl1->y+playerHeight) && (ball->x + ballX <= pl1->x + playerWidth))
	{
		float offset = (float)(ball->y - (pl1->y + playerHeight/2)) / playerHeight;
		if (offset < -1) offset = -1;
		if (offset > 1) offset = 1;
		offset *= maxOffset;
		ballY = max_speed * offset * maxOffset;
		if (offset < 0) offset = -offset;
		ballX = max_speed * (1 - offset);
	}

	// If ball collidies with either upper or lower edge of the window border, start moving in the other y direction
	if (ball->y + ball->r + ballY >= windowHeight - borderWidth || ball->y - ball->r+ ballY <= borderWidth)
	{
		ballY *= -1;
	}

	// If the ball is beyond player 2, give player 1 a point and reset ball position
	if (ball->x - ball->r + ballX > pl2->x)
	{
		player1Score++;
		printf("\n\nPLAYER 1 SCORES!\n");
		printf("\nTOTAL SCORE\n----------------\nPLAYER 1: %d\nPLAYER 2: %d \n", player1Score, player2Score);
		draw_circle(surface, ball, black);
		ball->x = windowWidth/2;
		ball->y = windowHeight/2;
		draw_circle(surface, ball, white);
		ballX *= -1;
	} else if (ball->x + ball->r + ballX < pl1->x + playerWidth) // If the ball is beyond player 1, give player 2 a point and reset ball position
	{
		player2Score++;
		printf("\n\nPLAYER 2 SCORES!\n");
		printf("\nTOTAL SCORE\n----------------\nPLAYER 1: %d\nPLAYER 2: %d \n", player1Score, player2Score);
		draw_circle(surface, ball, black);
		ball->x = windowWidth/2;
		ball->y = windowHeight/2;
		draw_circle(surface, ball, white);
		ballX *= -1;
	} else // Else, let the ball continue on it's path
	{
		draw_circle(surface, ball, black);
		ball->x += ballX;
		ball->y += ballY;
		draw_circle(surface, ball, white);
		SDL_FillRect(surface, pl1, white);
		SDL_FillRect(surface, pl2, white);
	}
}

// Function that handles moving of players
void move_rect(SDL_Surface* surface, SDL_Rect* rect, int speed)
{
	SDL_Rect* rect2 = rect;
	if (rect2->y + speed <= borderWidth)
	{
		SDL_FillRect(surface, rect, black);
		rect->y = borderWidth;
		SDL_FillRect(surface, rect, white);
	} else if (rect->y + speed >= windowHeight - playerHeight - borderWidth)
	{
		SDL_FillRect(surface, rect, black);
		rect->y = windowHeight - playerHeight - borderWidth;
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

	// Create window, grab surface, and initialize window dimensions dependendant variables
	SDL_Window *window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
	640, 480, SDL_WINDOW_SHOWN);
	SDL_Surface *surface = SDL_GetWindowSurface(window);
	windowHeight = surface->h;
	windowWidth = surface->w;
	player_speed = windowWidth / 128;
	SDL_SetWindowResizable(window, SDL_TRUE);

	// Initialize ball
	struct circle circle;
	circle.x = windowWidth/2;
	circle.y = windowHeight/2;
	circle.r = ballRadius;
	draw_circle(surface, &circle, white);

	// Decorate window
	draw_map(surface);

	// Create player 1's rectange;
	SDL_Rect pl1 = (SDL_Rect) {playerWidth, playerWidth + borderWidth, playerWidth, playerHeight};
	SDL_FillRect(surface, &pl1, white);

	// Create player 2's rectange;
	SDL_Rect pl2 = (SDL_Rect) {windowWidth - 2 * playerWidth, windowHeight - playerHeight - playerWidth - borderWidth, playerWidth, playerHeight};
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

		// If user closes application, send final message to terminal and stop game loop
		if(event.type == SDL_QUIT)
		{
			printf("\nFINAL SCORE\n----------------\nPLAYER 1: %d\nPLAYER 2: %d \n", player1Score, player2Score);
			running = 0;
		}

		// If user resizes window, re-initialize window dimensions dependant variables and game
		if (event.type == SDL_WINDOWEVENT){
			if (event.window.event == SDL_WINDOWEVENT_RESIZED){
				surface = SDL_GetWindowSurface(window);
				windowHeight = surface->h;
				windowWidth = surface->w;
				player_speed = windowWidth / 128;
				pl2.x = windowWidth - 2 * playerWidth;
				move_rect(surface, &pl1, 1);
				move_rect(surface, &pl2, 1);
				draw_map(surface);
				SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
			}
		}

		// Handle player/computer inputs
		// PLAYER 1
		if (keyboard_state_array[SDL_SCANCODE_W]) {
			move_rect(surface, &pl1, -player_speed);
		}
		if (keyboard_state_array[SDL_SCANCODE_S]) {
			move_rect(surface, &pl1, player_speed);
		}

		// PLAYER 2
		if (!ai)
		{
			if (keyboard_state_array[SDL_SCANCODE_UP]) {
				move_rect(surface, &pl2, -player_speed);
			}
			if (keyboard_state_array[SDL_SCANCODE_DOWN]) {
				move_rect(surface, &pl2, player_speed);
			}
		} else {
			if (ballX < 0){
				if (circle.y < pl2.y)
				{
					move_rect(surface, &pl2, -player_speed);
				}
				if (circle.y > pl2.y + playerHeight)
				{
					move_rect(surface, &pl2, player_speed);
				}
			} else {
				struct circle mockCircle = circle;
				int targetY = predict_ball(&mockCircle, &pl2);
				if (pl1.y + playerHeight / 2 > targetY && pl2.y + circle.r > targetY)
				{
					for (int i = 0; i < player_speed; i++)
					{
						if (pl2.y > targetY)
						{
							move_rect(surface, &pl2, -1);
						}
					}
				} else if (pl1.y + playerHeight / 2 < targetY && pl2.y + playerHeight - circle.r > targetY)
				{
					for (int i = 0; i < player_speed; i++)
					{
						if (pl2.y + playerHeight > targetY)
						{
							move_rect(surface, &pl2, -1);
						}
					}
				} else if (pl1.y + playerHeight / 2 > targetY && pl2.y + circle.r < targetY)
				{
					for (int i = 0; i < player_speed; i++)
					{
						if (targetY && pl2.y < targetY)
						{
							move_rect(surface, &pl2, 1);
						}
					}
				} else if (pl1.y + playerHeight / 2 < targetY && pl2.y + playerHeight - circle.r < targetY)
				{
					for (int i = 0; i < player_speed; i++)
					{
						if (pl2.y + playerHeight < targetY)
						{
							move_rect(surface, &pl2, 1);
						}
					}
				}
			}
		}

		// Update ball position
		move_ball(surface, &circle, &pl1, &pl2);

		// Update window
		draw_map(surface);
		SDL_UpdateWindowSurface(window);

		// Set time between frames
		SDL_Delay(1000/refresh_rate);
	}
	SDL_Quit();
}