#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/*  Program for splitting and formatting each step of banana_traders.c output
	Generates individual "snap" files for use in gnuplot to make a .gif
		1) Asks user for:
			i)		name of file to split
			ii)		number of traders in data set
			iii) 	total simulation time
		2)	Calculates total elements in the data set
		3) 	Allocates memory, and copies data from the input to "mem_ptr" as a stream
			of elements
		4) 	Transfers correct elements of "mem_ptr" to an individual "snap_.txt" file
			for each time step. 
			(the output contains 3 columns for use in gnuplot: column 1: x, column 2: y
									   column 3: point size)
*/

int main() 
{
//----------------------------------------------------------------------DEFINITIONS
	FILE *input_ptr;
	FILE *output_ptr;
	char filename[50]; 
	int i, j;
	int num_traders, time_tot, tot_elements;
	int snap_request, snap_start, snap_end;

//-----------------------------------------------------------------------USER INPUT	
	printf("Enter filename to split up: ");
	gets(filename);
	printf("Enter number of traders in the data set: ");
	scanf("%d", &num_traders);
	printf("Enter total sim time steps: ");
	scanf("%d", &time_tot);
	printf("\n");

//---------------------------------------------------------------CALC TOTAL ELEMENTS
tot_elements = time_tot * num_traders;
	
//------------------------------------------------ALLOCATE MEMORY FOR ELEMENT ARRAY
	int *mem_ptr;
	mem_ptr = malloc(tot_elements * sizeof(int));
	
	if(mem_ptr == NULL) {
		printf("ERROR! memory not allocated correctly.");
		return 1;
	}
	
//------------------------------------------------OPEN INPUT FILE, COPY TO mem_ptr
	input_ptr = fopen(filename, "r"); 
	if( input_ptr != NULL ) {
		for(i = 0; i < tot_elements; i++)
			fscanf(input_ptr, "%d", &mem_ptr[i]);
		fclose(input_ptr);
	}
	else {
		printf("Error: Cannot find input file, ending program...\n");
		return 1;
	}

//------------------------------------------------CREATE AND POPULATE "SNAP" FILES
	for(i = 0; i < time_tot; i++) {
		char out_filename[sizeof "snap_1000.txt"];
		sprintf(out_filename, "snap_%d.txt", i);
		output_ptr = fopen(out_filename, "w");
		
		snap_request = i;
		snap_start = (snap_request * num_traders);
		snap_end = snap_start + (num_traders - 1);
		
		for(j = snap_start; j <= snap_end; j++) {
			fprintf(output_ptr, "%d ", j - snap_start + 1);
			fprintf(output_ptr, "%d ", mem_ptr[j]);
			fprintf(output_ptr, "%d\n", mem_ptr[j]);
		}
		
		fclose(output_ptr);
	}
	
	free(mem_ptr);
	return 0;

}
