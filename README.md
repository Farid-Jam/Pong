# 🕹️ Pong Game
A 1972 Pong clone featuring two modes: one-on-one with a simple strategic AI and simple two-player local gameplay. 

![screenshot](images/screenshot.png)

## Features
- Classic two-player Pong gameplay
- Smooth paddle and ball movement using SDL2
- Simple, retro-style graphics
- Collision checking
- Resizable window
- Score tracking / scoreboard within terminal 

## Prerequisites 
Make sure you have the following installed on your system:
- [SDL2](https://www.libsdl.org/)
- A C compiler (e.g., `gcc`, `clang`)
- `make` build tool

## How to Run
Open a terminal and follow these steps:
1. **Clone the repository**

   Navigate to your desired directory and run: 
   ```bash
   git clone <repository-url>
   cd <repository-folder>
   ```
   
2. **Compile the C file**

   Use the included `Makefile` to build the project: 
   ```bash
   make
   ```

3. **Run the game**

   After building, run the executable:
   ```bash
   ./pong
   ```

## Controls 
| Player | Move Up | Move Down |
|--------|---------|-----------|
| P1     | `W`     | `S`       |
| P2     | `↑`     | `↓`       |

## Planned Features
- In-game score
- Pause button
