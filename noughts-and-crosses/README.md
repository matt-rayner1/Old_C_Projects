# noughts-and-crosses
A simple noughts and crosses program for 1 or 2 players, written in "only" 209 lines in C

The program uses a 3x3 character array for the board, and allows you to choose to play vs another human or the computer.
The computer makes random moves using <time.h> random number functions.

Program was made in VScode and compiled on windows with MinGW

------------------------------------------------------------------

# Concepts Explored:
Using <stdlib.h>'s system() function to clear terminal screen.

Using <time.h>'s rand() function (and also srand() for the seed), to generate random moves for the computer player.

Asking for user inputs, checking if they are valid, and performing different loops based on the user's choices.

Manipulating a 3x3 character array to display and change the board.

Using logic to check if the game has been won by either player (or computer).

Assigning int to char variables and vice versa
