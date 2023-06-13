#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* A simple noughts and crosses game for 1 or 2 players.
	1) Asks user how many players are playing
	2) Requests input from players until win condition is met.
	3) When win condition is met, player is notified of victory and program ends
	3)b) If game is a draw, players are notified of draw instead.
*/

//------------------------------------------------------------------------PROTOTYPES

void boardprint(char board[3][3]); 		//Draws board to terminal
void clrscr();					//Clears terminal screen
void mover(char board[3][3], int player);	//Asks each player's move
int wincheck(char board[3][3], int player);	//Game win check (1: won, 0: still going)
int rand_gen_0to3();				//RNG for computer opponent

int main()
{
//------------------------------------------------------------------------DEFINITIONS
    int player_count;
    int player = 0;
    char board[3][3];
    int i, j;

    srand(time(NULL)); 				//RNG seed

    for(i = 0; i < 3; i++) {			//Initialise board (white space)
        for(j = 0; j < 3; j++)
            board[i][j] = ' ';
    }

//------------------------------------------------------------------------GAME MODE INPUT
    printf("Welcome to a simple noughts and crosses game. 1 or 2 players? ");
    scanf("%d", &player_count);

    if((player_count != 1) && (player_count != 2)) {
        printf("\nSorry, only 1 or 2 players allowed. Please try again. Exiting program.");
        return 1;
    }

    if(player_count == 1) {			//1 PLAYER
        clrscr();
        boardprint(board);
        for(i = 0; i < 9; i++) {
            if(i%2 == 0)
                player = 1;
            else
                player = 3; 			//(3 is computer opponent)
            mover(board, player);
            clrscr();
            boardprint(board);
            if(wincheck(board, player) == 1) {
                if(player == 1){
                    printf("\nPlayer %d wins!", player);
                    break;
                }
                else {
                    printf("\nComputer wins!");
                    break;
                }
            }
            if(i == 8 && wincheck(board, player) == 0) {
                printf("\nMatch draw!");
                break;
            }
        }           
    }
    else {					//2 PLAYER
        clrscr();
        boardprint(board);
        for(i = 0; i < 9; i++) {
            if(i%2 == 0)
                player = 1;
            else
                player = 2;
            mover(board, player);
            clrscr();
            boardprint(board);
            if(wincheck(board, player) == 1) {
                printf("\nPlayer %d wins!", player);
                break;
            }
            if(i == 8 && wincheck(board, player) == 0) {
                printf("\nMatch draw!");
                break;
            }
        }
    }

    return 0;
}

//----------------------------------------------------------------board print fn
void boardprint(char board[3][3]) {
    printf("[Player 1 (X)\t\t Player 2 (O)]\n");
    printf("\n\t  |  1  |  2  |  3  |\n");
    for(int i = 0; i < 3; i++)
    {
        printf("\t__|_____|_____|_____|\n");
        printf("\t  |     |     |     |\n");
        printf("\t%c ", i + 97);
        for(int j = 0; j < 3; j++) 
            printf("|  %c  ", board[j][i]);
        printf("|\n");
    }
    printf("\t__|_____|_____|_____|");
}

void clrscr() {
    system("@cls||clear");
}

//-------------------------------------------------------------------mover function
void mover(char board[3][3], int player) {
    int x, y;
    char y_char;

    while(1 == 1) {
        if(player == 1 || player == 2) {
            printf("\n\nPlayer %d, please enter your move (e.g. '2 c'): ", player);
            scanf("%d %c", &x, &y_char);

            //convert input to integer grid values (left column at x = 0 etc)
            x--;
            y = y_char - 97;

            //validity check, board input
            if( x < 0 || x > 2 || y < 0 || y > 2)
                printf("\nYou have entered an invalid move. Please try again.");
            else if(board[x][y] != ' ')
                printf("\nMove already made. Please try again");
            else {
                if(player == 1)
                    board[x][y] = 'X';
                else
                    board[x][y] = 'O';
                break;
            }
        }

        //computer turn generator
        if(player == 3) {
            x = rand_gen_0to3();
            y = rand_gen_0to3();
        
            if(board[x][y] != ' ')
                printf("Computer made a move that was already made. Trying again");
            else {
                board[x][y] = 'O';
                break;
            }
        }
    }
}

//-----------------------------------------------------------------win check fn
int wincheck(char board[3][3], int player) {
    char X_or_O;
    //int tally = 0;
    int i, j;

    //function checks for 'X' or 'O'
    if(player == 1)
        X_or_O = 'X';
    else if(player == 2 || player == 3)
        X_or_O = 'O';
    else {
        printf("Incorrect player input into function wincheck(), exiting program");
        exit;
    }

    //row win check v2
    for(i = 0; i < 3; i++) {
        if(board[i][0] == X_or_O && board[i][0] == board[i][1] && board[i][0] == board[i][2])
            return 1;
    }

    //column win check v2
    for(i = 0; i < 3; i++) {
        if(board[0][i] == X_or_O && board[0][i] == board[1][i] && board[0][i] == board[2][i])
            return 1;
    }

    //diag win check1 v2
    if(board[0][0] == X_or_O && board[0][0] == board[1][1] && board[0][0] == board[2][2])
        return 1;

    //diag win check2 v2
    if(board[0][2] == X_or_O && board[0][2] == board[1][1] && board[0][2] == board [2][0])
        return 1;
    else
        return 0;
}

int rand_gen_0to3() {
    double gen_rand;
    int round_down;

    gen_rand = 3 * (double)rand()/(double)RAND_MAX;
    round_down = (int) gen_rand;
	return round_down;
}
