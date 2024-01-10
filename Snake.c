#include <stdio.h>
#include <conio.h> // For _kbhit() and _getch() on Windows
#include <stdlib.h>
#include <windows.h>

// Constants
#define BOARD_SIZE 20
#define SNAKE_MAX_LENGTH (BOARD_SIZE * BOARD_SIZE)

// Directions
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

int gameover = 0;

// Function to draw the game board
void drawBoard(void) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (j == 0 || j == BOARD_SIZE - 1) {
                printf("|");
            } else if (i == 0 || i == BOARD_SIZE - 1) {
                printf("-");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

// Initialize the snake struct
typedef struct {
    int x[SNAKE_MAX_LENGTH];
    int y[SNAKE_MAX_LENGTH];
    int l;
} Snake;

int main(void) {

    // Initialize the snake
    Snake s;
    s.x[0] = BOARD_SIZE / 2;
    s.y[0] = BOARD_SIZE / 2;
    s.l = 1; 

    // Initialize the fruit position
    int fruitX = 5;
    int fruitY = 5;

    // Hide the cursor and clear the screen
    printf("\e[?25l");
    system("cls"); // Clear the screen

    // Initialize the initial direction
    int direction = DOWN;

    // Draw a board
    drawBoard();

    // Plot the fruit
    printf("\e[%d;%dHF", fruitY, fruitX); // Plot the 'X' of a snake


    
    while (!gameover) {
        // Check if a key is pressed
        if (_kbhit()) {
            switch (_getch()) {
                case 'w':
                    direction = UP;
                    break;
                case 's':
                    direction = DOWN;
                    break;
                case 'a':
                    direction = LEFT;
                    break;
                case 'd':
                    direction = RIGHT;
                    break;
                case 'x':
                    gameover = 1;
                    break;
            }
        }

        // Move the snake
        for (int i = s.l; i > 0; i--) {
            s.x[i] = s.x[i - 1];
            s.y[i] = s.y[i - 1];
        }

        switch (direction) {
            case UP:
                s.y[0]--;
                break;
            case DOWN:
                s.y[0]++;
                break;
            case LEFT:
                s.x[0]--;
                break;
            case RIGHT:
                s.x[0]++;
                break;
        }

        // Plot the snake with 'X' chars
        for (int i = 0; i <= s.l; i++) {
            printf("\e[%d;%dHX", s.y[i], s.x[i]); 
        }

        // Grow (if eats fruit)
        if (s.y[0] == fruitY && s.x[0] == fruitX ){
            s.l++ ;
            fruitY = rand() % (BOARD_SIZE - 2) + 2;
            fruitX = rand() % (BOARD_SIZE - 2) + 2;
            // Plot the fruit
            printf("\e[%d;%dHF", fruitY, fruitX); 
        }
        // Check for hitting the wall
        if(s.y[0] == 0 || s.y[0] == BOARD_SIZE || s.x[0] == 1 || s.x[0] == BOARD_SIZE)  {
            gameover = 1;
            printf("\e[%d;%dHGame Over! You hit a wall!\n",BOARD_SIZE + 1, 0);
        }
        // Check for collision with its body 
        for (int i = 1; i < s.l; i++) {
            if (s.x[i] == s.x[0] && s.y[i] == s.y[0]) {
                gameover = 1;
                printf("\e[%d;%dHGame Over! You collided with yourself!\n",BOARD_SIZE + 1, 0);
            }
        }

        // Clear the trace 
        printf("\e[%d;%dH ", s.y[s.l], s.x[s.l]);  

        //Speed of snake's movement
        Sleep(100);
    }


    // Move the cursor to row 21
    printf("\e[%d;1H", BOARD_SIZE + 2 );

    return 0;
}
