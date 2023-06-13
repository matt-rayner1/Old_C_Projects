#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*  This program simulates how wealth is distrubuted across a set of trader, throughout "generations".
    This is an example of the "pareto distribution" or "Matthew principle". 

    The rules are simple:
        1) Each trader starts with the same amount of "bananas"
        2) For each "generation", a coin is flipped between pairs of traders. 
             If it is heads, the 1st trader gets a banana from the 2nd trader.
             If it is tails, the 1st trader loses a bana to the 2nd trader.
        3) If a trader reaches 0 bananas, they can no longer play the game and are out.

    Please see INITIALISE area to change parameters for the simulation. 
    The program will output a data file ("trader_data.txt") with the banana values for each trader.
    For simplicity and ease of manipulation, the data is 'raw'.
    I.e. it does not contain anything but the traders' data separated by a space, or a newline if the generation has finished.

    (KNOWN ISSUE: wealth is not conserved 100% throughout the simulation for some unknown reason, but is close to the proper starting amount.)
*/

double coinflip();

int main()
{
//----------------------------------------------------------INITIALISE
    const int num_traders = 100;            //Total number of traders
    const int time_tot = 1000;              //Will give time_tot + 1 printouts
    const int initial_wealth = 10;          //Starting bananas/wealth given to each trader

    int traders[num_traders];
    int wealth_check = 0;
    int i, j, k, t;
    int breakcheck;
    int i_init, j_init;
    int flagA, flagB;
    FILE *trader_data;

    trader_data = fopen("trader_data.txt", "w");
    srand(time(NULL));

    for(i = 0; i < num_traders; i++)
        traders[i] = initial_wealth;

//-------------------------------------------------------INITIAL PRINTOUT
    for(i = 0; i < num_traders; i++)
        fprintf(trader_data, "%d ", traders[i]);
    fprintf(trader_data, "\n");

//--------------------------------------------------MAIN SIMULATION LOOP
    for(t = 0; t < time_tot; t++) {
        printf("Time step :%d\n", t);
        k = 0;
        while(k < num_traders) {
            flagA = 0;
            flagB = 0;
            breakcheck = 0;
            while(flagA == 0 && flagB == 0) {
                if(coinflip() > 0.5) {                          //(HEADS)
                    for(i = k; i < num_traders; i++) {          //(1ST TRADER)
                        if(i == num_traders - 1 && traders[i] == 0) {
                            j_init = i + 1;
                            breakcheck = 1;
                            break;
                        }
                        else if(traders[i] != 0 && flagA == 0) {
                            traders[i] += 1;
                            flagA = 1;
                            j_init = i + 1;
                            break;
                        }      
                    }
                    if(breakcheck == 1) {
                        k = num_traders + 1;
                        break;
                    }
                    for(j = j_init; j < num_traders; j++) {     //(2ND TRADER)
                        if(j == num_traders - 1 && traders[j] == 0) {
                            traders[j_init - 1] -= 1;
                            breakcheck = 1;
                            break;
                        }
                        else if(traders[j] != 0 && flagB == 0) {
                            traders[j] -= 1;
                            flagB = 1;
                            k = j + 1;
                            break;
                        }
                    }
                }
                else {                                          //(TAILS)
                    for(i = k; i < num_traders; i++) {          //(1ST TRADER)
                        if(i == num_traders - 1 && traders[i] == 0) {
                            j_init = i + 1;
                            k = i + 1;
                            breakcheck = 1;
                            break;
                        }   
                        else if(traders[i] == 0) {
                            k += 1;
                        }
                        else if(traders[i] != 0 && flagA == 0) {
                            traders[i] -= 1;
                            flagA = 1;
                            j_init = i + 1;
                            break;
                        }     
                    }
                    if(breakcheck == 1) {
                        break;
                    }
                    for(j = j_init; j < num_traders; j++) {     //(2ND TRADER)
                        if(j == num_traders - 1 && traders[j] == 0) {
                            traders[j_init - 1] += 1;
                            k = j + 1;
                            breakcheck = 1;
                            break;
                        }
                        else if(traders[j] != 0 && flagB == 0) {
                            traders[j] += 1;
                            flagB = 1;
                            k = j + 1;
                            break;
                        }
                    }
                }
                if(breakcheck == 1) {
                    break;
                }
            }
        }

        //print trader data into trader_data.txt
        for(j = 0; j < num_traders; j++)
                fprintf(trader_data, "%02d ", traders[j]);
        fprintf(trader_data, "\n");

    }

//---------------------------------------------------DISPLAY END RESULTS
    for(i = 0; i < num_traders; i++)
        printf("\nTrader: %02d, \tWealth: %d", i, traders[i]);
    for(i = 0; i < num_traders; i++)
        wealth_check += traders[i];
    printf("\nTOTAL WEALTH: %d", wealth_check);


//------------------------------------------------CLOSE PROGRAM PROPERLY
    fclose(trader_data);
    return 0;
}

double coinflip() {
	return (double)rand()/(double)RAND_MAX;
}
