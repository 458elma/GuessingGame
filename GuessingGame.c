#include <stdio.h>
#define SIZE_FIVE 5
#define SIZE_SEVEN 7
#define SIZE_TEN 10
/*

    Guessing Game

*/

static const int GUESSES = 5; // number of guesses

// function prototype for function to choose difficulty of single 1 game
void choose_single();
// function prototype for function to choose difficulty of multiple 1s game
void choose_multiple();
// function prototype for function to load game board for single 1 game
void load_single(int size, int selection);
// function prototype for the function that contains the game logic for single 1s
void play_single(int row_count, int col_count, int gameBoard[row_count][col_count]);
// function prototype for the function to load game board for multiple 1s game
void load_multiple(int gridSize);
// function prototype for the function that contains game logic for multiple 1s
void play_multiple(int row_total, int col_total, int gameGrid[row_total][col_total]);

int main(void) {
    int mode_chosen = 0; // variable to hold game mode chosen
    puts("Welcome to the Guessing Game!");
    fputs("Please select a game mode(type 1 for single 1, type 2 for multiple 1s): ", stdout);
    scanf("%d", &mode_chosen);
    printf("\n");

    // switch statement to load difficulty selection section based on player choice
    switch (mode_chosen) {
    case 1:
        choose_single();
        break;
    case 2:
        choose_multiple();
        break;
    default:
        puts("Game mode unavailable, please restart the game.");
    }
    return 0;
}

/*

    Function to choose difficulty of single 1 game

*/
void choose_single() {
    int difficulty_single = 0; // variable to hold difficulty level
    int board_selection = 0; // variable to hold board selection
    puts("You have chosen single 1 mode.");
    fputs("Please select a difficulty (type 1 for easy, type 2 for medium, type 3 for hard): ", stdout);
    scanf("%d", &difficulty_single);
    fputs("Please choose a number(1, 2, or 3): ", stdout);
    scanf("%d", &board_selection);
    printf("\n");

    // switch statement to load game depending on player's choice
    switch (difficulty_single) {
    case 1:
        load_single(SIZE_FIVE, board_selection);
        break;
    case 2:
        load_single(SIZE_SEVEN, board_selection);
        break;
    case 3:
        load_single(SIZE_TEN, board_selection);
        break;
    default:
        puts("Difficulty mode unavailable, please restart the game.");
    }
}

/*

    Function to choose difficulty of multiple 1s game

*/
void choose_multiple() {
    int difficulty_multiple = 0; // variable to hold difficulty level
    puts("You have chosen multiple 1s mode.");
    fputs("Please select a difficulty (type 1 for easy, type 2 for medium, type 3 for hard): ", stdout);
    scanf("%d", &difficulty_multiple);
    printf("\n");

    // switch statement to load game depending on player's choice
    switch (difficulty_multiple) {
    case 1:
        load_multiple(SIZE_FIVE);
        break;
    case 2:
        load_multiple(SIZE_SEVEN);
        break;
    case 3:
        load_multiple(SIZE_TEN);
        break;
    default:
        puts("Difficulty mode unavailable, please restart the game.");
    }
}

/*

    Function that sets up game board for single one game and loads game

*/
void load_single(int size, int selection) {
    int prize_row = 0; // variable to hold row number to guess
    int prize_col = 0; // variable to hold column number to guess
    int r_prize_five = 0; // variable to hold row number to guess based on size 5 and selection
    int c_prize_five = 0; // variable to hold col number to guess based on size 5 and selection
    int r_prize_seven = 0; // variable to hold row number to guess based on size 7 and selection
    int c_prize_seven = 0; // variable to hold col number to guess based on size 7 and selection
    int r_prize_ten = 0; // variable to hold row number to guess based on size 10 and selection
    int c_prize_ten = 0; // variable to hold col number to guess based on size 10 and selection

    // set up the game grid with the given size with all 0s
    int game_grid[size][size];
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            game_grid[r][c] = 0;
        }
    }

    // switch statement to choose row and column number to load
    // based on selection
    switch (selection) {
    case 1:
        r_prize_five = 1;
        c_prize_five = 1;
        r_prize_seven = 5;
        c_prize_seven = 4;
        r_prize_ten = 7;
        c_prize_ten = 0;
        break;
    case 2:
        r_prize_five = 4;
        c_prize_five = 4;
        r_prize_seven = 3;
        c_prize_seven = 6;
        r_prize_ten = 4;
        c_prize_ten = 1;
        break;
    case 3:
        r_prize_five = 0;
        c_prize_five = 3;
        r_prize_seven = 1;
        c_prize_seven = 5;
        r_prize_ten = 2;
        c_prize_ten = 8;
        break;
    default:
        // do nothing
        r_prize_five = 0;
        c_prize_five = 0;
        r_prize_seven = 0;
        c_prize_seven = 0;
        r_prize_ten = 0;
        c_prize_ten = 0;
    }

    // switch statement to load winning guess depending on which
    // board is selected by user
    switch (size) {
    case SIZE_FIVE:
        prize_row = r_prize_five;
        prize_col = c_prize_five;
        break;
    case SIZE_SEVEN:
        prize_row = r_prize_seven;
        prize_col = c_prize_seven;
        break;
    case SIZE_TEN:
        prize_row = r_prize_ten;
        prize_col = c_prize_ten;
        break;
    default:
        prize_row = 0;
        prize_col = 0;
    }

    game_grid[prize_row][prize_col] = 1; // mark the winning coordinate

    play_single(size, size, game_grid); // call the function to start the game
}

/*

    Function that contains game logic for finding a single 1 in a grid of 0s

*/
void play_single(int row_count, int col_count, int gameBoard[row_count][col_count]) {
    int guessRow = -1; // variable to store the row position guess
    int guessCol = -1; // variable to store the column position guess
    int guesses  = GUESSES; // variable to store amount of guesses left
    _Bool foundOne = 0; // variable to set to true if 1 is found
    int isGuessed[row_count][col_count]; // grid to use to check if coordinate is guessed

    // nested for loop to set all coordinates in guesses grid to 0 to represent not guessed yet
    for (int rowGuessed = 0; rowGuessed < row_count; rowGuessed++) {
        for (int colGuessed = 0; colGuessed < col_count; colGuessed++) {
            isGuessed[rowGuessed][colGuessed] = 0;
        }
    }

    // Initial text to inform player about the game
    printf("There is a hidden %dx%d board. Can you guess where the 1 is?\n", row_count, col_count);
    puts("Instructions: \nThe board coordinates are in 0 index format so the top left corner of the board is (0,0).");
    puts("Input the row and column you wish to guess in the format: \nrowNumber colNumber\n");

    // do-while loop to loop through player guesses
    do {
        printf("You have %d guesses left.\n", guesses);
        fputs("Guess where the 1 is: ", stdout);
        scanf("%d%d", &guessRow, &guessCol);
        // if-else block to check if coordinates guessed are valid
        if (guessRow >= 0 && guessRow < row_count && guessCol >= 0 && guessCol < col_count) {
            // if-else block to check if valid guess is a new guess
            if (isGuessed[guessRow][guessCol] == 0) {
                isGuessed[guessRow][guessCol] = 1; // mark this coordinate as guessed
                printf("The number in position [%d][%d] is %d\n\n", guessRow, guessCol, gameBoard[guessRow][guessCol]);
                // if statement to check if coordinate is where the 1 is
                if (gameBoard[guessRow][guessCol] == 1) {
                    puts("You win! You found the one!"); // winning message
                    foundOne = 1; // used to stop the loop because game is won and over
                }
                guesses--; // every valid guess takes 1 away from guesses left
            } else {
                // saves a guess for the user because it was already guessed
                printf("You already guessed position [%d][%d].\n\n", guessRow, guessCol);
            }
        } else {
            // tell the user that guess was invalid
            // guess will not be counted
            puts("Please enter a valid row and column position.");
            printf("\n");
        }
    } while(guesses > 0 && !foundOne);

    // display losing message if 1 not found
    if (!foundOne) {
        puts("You lose. You did not find the one.");
    }
}

/*

    Function that sets up game board for multiple 1s game and loads game

*/
void load_multiple(int gridSize) {
    // set up the game grid with the given size with all 0s
    int game_grid[gridSize][gridSize];
    for (int r = 0; r < gridSize; r++) {
        for (int c = 0; c < gridSize; c++) {
            game_grid[r][c] = 0;
        }
    }

    // switch statement to load 1s depending on which
    // board is selected by user
    switch (gridSize) {
    case SIZE_FIVE:
        game_grid[0][2] = 1;
        game_grid[0][4] = 1;
        game_grid[1][3] = 1;
        game_grid[2][0] = 1;
        game_grid[4][4] = 1;
        break;
    case SIZE_SEVEN:
        game_grid[1][2] = 1;
        game_grid[2][5] = 1;
        game_grid[4][0] = 1;
        game_grid[4][5] = 1;
        game_grid[6][2] = 1;
        break;
    case SIZE_TEN:
        game_grid[1][6] = 1;
        game_grid[3][3] = 1;
        game_grid[4][2] = 1;
        game_grid[6][9] = 1;
        game_grid[8][5] = 1;
        break;
    default:
        game_grid[0][0] = 1;
    }

    play_multiple(gridSize, gridSize, game_grid); // call the function to start the game
}

/*

    Function that contains the game logic for finding multiple 1s in a grid of 0s

*/
void play_multiple(int row_total, int col_total, int gameGrid[row_total][col_total]) {
    int row_guess = -1; // variable to hold guessed row
    int col_guess = -1; // variable to hold guessed column
    int guess_count = GUESSES; // variable to keep track of guesses left
    int score = 0; // variable to keep track of score

    // 2-d array to keep track of which coordinates have been guessed
    int guessedGrid[row_total][col_total];
    for (int rRow = 0; rRow < row_total; rRow++) {
        for (int cCol = 0; cCol < col_total; cCol++) {
            guessedGrid[rRow][cCol] = 0;
        }
    }

    // Initial text to inform player about the game
    printf("There is a hidden %dx%d board. Can you guess where all the 1s are?\n", row_total, col_total);
    puts("Instructions: \nThe board coordinates are in 0 index format so the top left corner of the board is (0,0).");
    puts("Input the row and column you wish to guess in the format: \nrowNumber colNumber\n");

    // do-while loop to loop through player guesses
    do {
        printf("You have %d guesses left.\n", guess_count);
        fputs("Guess where a 1 is: ", stdout);
        scanf("%d%d", &row_guess, &col_guess);
        // if-else block to check if coordinates guessed are valid
        if (row_guess >= 0 && row_guess < row_total && col_guess >= 0 && col_guess < col_total) {
            // if-else block to check if valid guess is a new guess
            if (guessedGrid[row_guess][col_guess] == 0) {
                guessedGrid[row_guess][col_guess] = 1; // mark this coordinate as guessed
                printf("The number in position [%d][%d] is %d\n\n", row_guess, col_guess, gameGrid[row_guess][col_guess]);
                // if statement to check if coordinate is where a 1 is
                if (gameGrid[row_guess][col_guess] == 1) {
                    puts("You found a one!\n"); // message to tell player they found a 1
                    score++; // increase score by 1
                }
                guess_count--; // every valid guess takes 1 away from guesses left
            } else {
                // saves a guess for the user because it was already guessed
                printf("You already guessed position [%d][%d].\n\n", row_guess, col_guess);
            }
        } else {
            // tell the user that guess was invalid
            // guess will not be counted
            puts("Please enter a valid row and column position.");
            printf("\n");
        }
    } while(guess_count > 0);

    // tells user how many 1s player found when game is over
    if (score < GUESSES) {
        printf("You found %d/%d 1s. Play again to try to find them all.", score, GUESSES);
    } else {
        printf("You found all %d 1s!", GUESSES);
    }
}
