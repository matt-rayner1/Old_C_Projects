#include <stdio.h>
#include <string.h>

/*  YAMMOUTH SCORE TRACKER by matt rayner

    -----------------------------------------------------------------------------------------------------------------------

    1) Asks for number of players
    2) Asks for player names
    3) Asks for scores after each round
        i) Checks for multiple of 25, 10 wins in a row, and if score is over 100
    
    Refer to rules on the github page if you dont understand the game!

    ---------------------------------------------------------------------------------------------------------------------------
*/

void clrscr();

int main()
{
//----------------------------------------------------------------------------DEFINITIONS
	int N, i, j, redo = 0, outs = 0;
	FILE *game_data;
	game_data = fopen("game_data.txt", "w");
	
//-----------------------------------------------------------------INTRO AND PLAYER COUNT
	printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
	printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
	printf("Welcome to Yammouth Score Tracker by Matt Rayner\n");
	printf("Please enter the number of players: ");
	scanf("%d", &N);
	
//------------------------------------------------------------------------SCORE POPULATOR
	int round_score[N];
	int totals[N];
	char names[N][25];
	int streak[N];
	
//----------------------------------------------------------------------------NAME CHECK
	for(i = 0; i < N; i++) {
		printf("Enter name for Player %d: \t", i+1);
		scanf("%s", &names[i]);
		getchar();
	}
	
	printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
	printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
	printf("\n\n");
	
//-----------------------------------------------Initialise totals, Print player no.s to file
	for(i = 0; i < N; i++) {
		totals[i] = 0;
		streak[i] = 0;
		fprintf(game_data, "%s\t", names[i]);
	}
	fprintf(game_data, "\n");
	
	for(i = 0;; i++) {
//--------------------------------------------------------------Round input + add to totals
		printf("------------------------------------------------------------ROUND %d\n", i+1);
		for(j = 0; j < N; j++) {
			if(totals[j] > 100)
				continue;
			printf("%s: enter your score for round %d.\n", names[j], i+1);
			scanf("%d", &round_score[j]);
			totals[j] += round_score[j];
			if(round_score[j] == 0)
				streak[j]++;
		}	
		printf("--------------------------------------------------------------------\n");
		
//-----------------------------------------------------------------emergency exit/redo move
		printf("Redo round? (1 = yes, 0 = no): \t");
		scanf("%d", &redo);
		if(redo == 1) {
			for(j = 0; j < N; j++) {
				if(totals[j] > 100)
					round_score[j] = 0;
				totals[j] -= round_score[j];
				if(round_score[j] == 0)
					streak[j]--;
			}
			i--;
			continue;
		}
		
		clrscr();
		
		printf("--------------------------------------------------------------EVENTS\n");
//----------------------------------------------------------------------------x25 check
		for(j = 0; j < N; j++) {
			if( (totals[j] % 25 == 0) && (totals[j] != 0) ) {
				printf("%s has a multiple of 25!\n", names[j]);
				totals[j] -= 25;
			}
		}
		
//------------------------------------------------------------------------10 in a row check
		for(j = 0; j < N; j++) {
			if(streak[j] >= 10) {
				printf("%s has won 10 times in a row!\n", names[j]);
				streak[j] = 0;
				if(totals[j] != 0)
					totals[j] = 0;
				else if(totals[j] == 0)
					totals[j] = -100;
			}
		}
		
//------------------------------------------------------------------------gonzed check
		for(j = 0; j < N; j++) {
			if(totals[j] > 100) {
				printf("%s is GONZED!\n", names[j]);
				outs++;
			}
		}
		
//------------------------------------------------------------------------total print (screen + file)
		printf("-----------------------------------------------------ROUND %d TOTALS\n", i+1);
		printf("TOTALS:\n");
		for(j = 0; j < N; j++) {
			if(totals[j] > 100) {
				printf("%s: GONZED\t", names[j], j+1);
				fprintf(game_data, "GON\t");
				continue;
			}
			printf("%s: %d\t", names[j], totals[j]);
			fprintf(game_data, "%d\t", totals[j]);
		}
		printf("\n");
		fprintf(game_data, "\n");

		//Game end
		for(j = 0; j < N; j++) {		
			if(outs == N-1) {
				printf("Game over, winner is %s. GG and goodbye\n", names[j]);
				return 0;
			}
			else
				outs = 0;
		}
		
		printf("##################################################################\n\n\n");
	}
	
	return 0;
}

//Clear screen - may not work with some compilers/OSs
void clrscr()
{
    system("@cls||clear");
}
