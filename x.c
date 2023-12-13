#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the size of the grid
#define ROWS 5
#define COLS 5

// Define the symbols for the grid
#define DOT '.'
#define HLINE  '-'
#define VLINE '|'
#define BOX 'X'

// Define the players
#define HUMAN 1
#define COMPUTER 2

// Define the colors
#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"

// Declare the global variables
char grid[ROWS][COLS]; // The grid array
int human_score = 0; // The human's score
int computer_score = 0; // The computer's score
int turn = HUMAN; // The current turn

// Declare the functions
void init_grid(); // Initialize the grid
void draw_grid(); // Draw the grid
int is_valid(int r1, int c1, int r2, int c2); // Check if a line is valid
void update_grid(int r1, int c1, int r2, int c2); // Update the grid and the score
int is_over(); // Check if the game is over
void computer_move(); // Make the computer's move

// The main function
int main()
{
    // Initialize the random seed
    srand(time(NULL));

    // Initialize the grid
    init_grid();

    // Print the welcome message
    printf("Welcome to Dots and Boxes!\n");
    printf("You are playing against the computer.\n");
    printf("You can draw a line by entering the coordinates of two adjacent dots.\n");
    printf("For example, to draw a line between a1 and a2, enter: a1 a2\n");
    printf("The game ends when all the lines are drawn.\n");
    printf("The player with the most boxes wins.\n");
    printf("Good luck!\n\n");

    // Draw the grid
    draw_grid();

    // Start the game loop
    while (!is_over())
    {
        // Declare the variables for the input
        char c1, c2;
        int r1, r2, col1, col2;

        // Check whose turn it is
        if (turn == HUMAN)
        {
            // Print the human's turn message
            printf("Your turn. Enter a line: ");

            // Get the input from the user
            scanf(" %c%d %c%d", &c1, &r1, &c2, &r2);

            // Convert the input to array indices
            col1 = c1 - 'a';
            col2 = c2 - 'a';
            r1--;
            r2--;

            // Check if the input is valid
            if (is_valid(r1, col1, r2, col2))
            {
                // Update the grid and the score
                update_grid(r1, col1, r2, col2);

                // Draw the grid
                draw_grid();
            }
            else
            {
                // Print the invalid input message
                printf("Invalid input. Try again.\n");
            }
        }
        else
        {
            // Print the computer's turn message
            printf("Computer's turn.\n");

            // Make the computer's move
            computer_move();

            // Draw the grid
            draw_grid();
        }
    }

    // Print the game over message
    printf("Game over.\n");

    // Print the final score
    printf("Your score: %d\n", human_score);
    printf("Computer's score: %d\n", computer_score);

    // Print the result
    if (human_score > computer_score)
    {
        printf("You win!\n");
    }
    else if (human_score < computer_score)
    {
        printf("You lose.\n");
    }
    else
    {
        printf("It's a tie.\n");
    }

    // Return 0
    return 0;
}

// The function to initialize the grid
void init_grid()
{
    // Loop through the rows
    for (int i = 0; i < ROWS; i++)
    {
        // Loop through the columns
        for (int j = 0; j < COLS; j++)
        {
            // Check if the row and column are even
            if (i % 2 == 0 && j % 2 == 0)
            {
                // Set the grid element to a dot
                grid[i][j] = DOT;
            }
            else
            {
                // Set the grid element to a space
                grid[i][j] = ' ';
            }
        }
    }
}

// The function to draw the grid
void draw_grid()
{
    // Print a newline
    printf("\n");

    // Print the column labels
    printf("  ");
    for (int i = 0; i < COLS; i += 2)
    {
        printf("%c ", 'a' + i);
    }
    printf("\n");

    // Loop through the rows
    for (int i = 0; i < ROWS; i++)
    {
        // Print the row label
        if (i % 2 == 0)
        {
            printf("%d ", i / 2 + 1);
        }
        else
        {
            printf("  ");
        }

        // Loop through the columns
        for (int j = 0; j < COLS; j++)
        {
            // Check if the grid element is a box
            if (grid[i][j] == BOX)
            {
                // Check whose box it is
                if (i % 4 == 1)
                {
                    // Print the box in red
                    printf(RED "%c " RESET, grid[i][j]);
                }
                else
                {
                    // Print the box in blue
                    printf(BLUE "%c " RESET, grid[i][j]);
                }
            }
            else
            {
                // Print the grid element
                printf("%c ", grid[i][j]);
            }
        }

        // Print a newline
        printf("\n");
    }

    // Print a newline
    printf("\n");
}

// The function to check if a line is valid
int is_valid(int r1, int c1, int r2, int c2)
{
    // Check if the coordinates are within the bounds
    if (r1 < 0 || r1 >= ROWS || c1 < 0 || c1 >= COLS || r2 < 0 || r2 >= ROWS || c2 < 0 || c2 >= COLS)
    {
        // Return 0
        return 0;
    }

    // Check if the coordinates are dots
    if (grid[r1][c1] != DOT || grid[r2][c2] != DOT)
    {
        // Return 0
        return 0;
    }

    // Check if the coordinates are adjacent
    if ((r1 == r2 && abs(c1 - c2) == 2) || (c1 == c2 && abs(r1 - r2) == 2))
    {
        // Check if the line is already drawn
        if (grid[(r1 + r2) / 2][(c1 + c2) / 2] == ' ')
        {
            // Return 1
            return 1;
        }
    }

    // Return 0
    return 0;
}

// The function to update the grid and the score
void update_grid(int r1, int c1, int r2, int c2)
{
    // Declare the variables for the line and the box symbols
    char line, box;

    // Check whose turn it is
    if (turn == HUMAN)
    {
        // Set the line symbol to yellow
        line = YELLOW HLINE RESET;

        // Set the box symbol to red
        box = BOX;
    }
    else
    {
        // Set the line symbol to green
        line = GREEN VLINE RESET;

        // Set the box symbol to blue
        box = BOX;
    }

    // Draw the line on the grid
    grid[(r1 + r2) / 2][(c1 + c2) / 2] = line;

    // Declare a variable to store the number of boxes formed
    int boxes = 0;

    // Check if the line is horizontal
    if (r1 == r2)
    {
        // Check if the line is not on the top edge
        if (r1 > 0) 
        { // Check if the upper box is formed 
            if (grid[r1 - 1][c1] != ' ' && grid[r1 - 1][c2] != ' ' && grid[r1 - 2][c1] != ' ') 
                { // Draw the box on the grid 
                    grid[r1 - 1][c1] = box;
                        // Increment the number of boxes
                    boxes++;
                }
                 if (r1 < ROWS - 1) 
                 { // Check if the lower box is formed 
                    if (grid[r1 + 1][c1] != ' ' && grid[r1 + 1][c2] != ' ' && grid[r1 + 2][c1] != ' ') 
                    { // Draw the box on the grid 
                    grid[r1 + 1][c1] = box;
                        // Increment the number of boxes
                    boxes++;
                    }
                } 
        }
                 else { // Check if the line is not on the left edge 
                 if (c1 > 0) { // Check if the left box is formed 
                    if (grid[r1][c1 - 1] != ' ' && grid[r2][c1 - 1] != ' ' && grid[r1][c1 - 2] != ' ')
                     { // Draw the box on the grid 
                     grid[r1][c1 - 1] = box;
                                 // Increment the number of boxes
            boxes++;
        }
    }

    // Check if the line is not on the right edge
    if (c1 < COLS - 1)
    {
        // Check if the right box is formed
        if (grid[r1][c1 + 1] != ' ' && grid[r2][c1 + 1] != ' ' && grid[r1][c1 + 2] != ' ')
        {
            // Draw the box on the grid
            grid[r1][c1 + 1] = box;

            // Increment the number of boxes
            boxes++;
        }
    }
}

            // Check if any boxes are formed
            if (boxes > 0)
            {
                // Update the score
                if (turn == HUMAN)
                {
                    human_score += boxes;
                }
                else
                {
                    computer_score += boxes;
                }
            }
            else
            {
                // Change the turn
                if (turn == HUMAN)
                {
                    turn = COMPUTER;
                }
                else
                {
                    turn = HUMAN;
                }
            }
            }

 int is_over() 
 { // Loop through the rows 
    for (int i = 0; i < ROWS; i++) 
    { // Loop through the columns 
        for (int j = 0; j < COLS; j++) 
            { // Check if the grid element is a space 
            if (grid[i][j] == ' ') { // Return 0 
            return 0; } 
            } 
            return 1;

}}
void computer_move() { // Declare the variables for the coordinates 
    int r1, c1, r2, c2;
    // Declare a flag to indicate if a move is found
int found = 0;

// Loop through the rows
for (int i = 0; i < ROWS; i++)
{
    // Loop through the columns
    for (int j = 0; j < COLS; j++)
    {
        // Check if the grid element is a dot
        if (grid[i][j] == DOT)
        {
            // Check the four possible lines around the dot
            for (int k = 0; k < 4; k++)
            {
                // Set the coordinates according to the direction
                switch (k)
                {
                case 0: // Up
                    r1 = i - 2;
                    c1 = j;
                    r2 = i;
                    c2 = j;
                    break;
                case 1: // Right
                    r1 = i;
                    c1 = j;
                    r2 = i;
                    c2 = j + 2;
                    break;
                case 2: // Down
                    r1 = i;
                    c1 = j;
                    r2 = i + 2;
                    c2 = j;
                    break;
                case 3: // Left
                    r1 = i;
                    c1 = j - 2;
                    r2 = i;
                    c2 = j;
                    break;
                }

                // Check if the line is valid
                if (is_valid(r1, c1, r2, c2))
                {
                    // Check if the line forms a box
                    if (grid[(r1 + r2) / 2][(c1 + c2) / 2] == ' ')
                    {
                        // Set the flag to 1
                        found = 1;

                        // Break the inner loop
                        break;
                    }
                }
            }

            // Check if a move is found
            if (found)
            {
                // Break the outer loop
                break;
            }
        }
    }

    // Check if a move is found
    if (found)
    {
        // Break the loop
        break;
    }
}

// Check if a move is not found
if (!found)
{
    // Loop until a valid move is found
    do
    {
        // Generate random coordinates
        r1 = rand() % ROWS;
        c1 = rand() % COLS;
        r2 = rand() % ROWS;
        c2 = rand() % COLS;
    } while (!is_valid(r1, c1, r2, c2));
}

// Update the grid and the score
update_grid(r1, c1, r2, c2);
}