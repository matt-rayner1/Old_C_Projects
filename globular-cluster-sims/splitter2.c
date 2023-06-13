#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* 	This program takes the data from the gravitylab output, and splits it into
	individual snapshots of the form "snap_001.txt" etc.
	NOTE: Please use a file with ONLY x,y,z coords (not the full simulation data)
		i.e. use awk to create a new file with the 2nd, 3rd and 4th columns only.
	1) Asks user for:
		i)	 name of file to split
		ii)	 number of particles in data set
		iii) output interval for data (no. of outputs per time unit)
		iv)	 total simulation time
	2) Calculates:
		i)	 size of each set ("set_size") (no. of elements in each set)
		ii)  number of "snapshots" ("total_snaps")
		iii) number of elements ("data_num")
	3) Allocates memory (dynamically-ish) to "mem_ptr" based on size of input file
	4) Copies data from input file to "mem_ptr" as a stream of elements
	5) (Hopefully) transfers correct elements to an individual "snap" for each time step
	
*/

int main() 
{
//----------------------------------------------------------------------DEFINITIONS
	FILE *input_ptr;
	FILE *output_ptr;
	int i, j;
	int particles, sim_time, out_intr, data_num;
	int set_size;
	int total_snaps, snap_request, snap_start, snap_end;
	char filename[50]; 
//-----------------------------------------------------------------------USER INPUT	
	printf("Enter filename to split up: ");
	gets(filename);
	printf("Enter number of particles: ");
	scanf("%d", &particles);
	printf("Enter output interval (outputs per time unit): ");
	scanf("%d", &out_intr);
	printf("Enter total sim time: ");
	scanf("%d", &sim_time);
	printf("\n");

//----------------------------------CALCULATE SET SIZE, TOTAL SNAPS, TOTAL ELEMENTS
	set_size = particles * 3;
	total_snaps = sim_time * out_intr;
	data_num = set_size * total_snaps;
	
//------------------------------------------------ALLOCATE MEMORY FOR ELEMENT ARRAY
	double *mem_ptr;
	mem_ptr = malloc(data_num * sizeof(double));
	
	if(mem_ptr == NULL) {
		printf("ERROR! memory not allocated correctly.");
		return 1;
	}
	
//------------------------------------------------OPEN INPUT FILE, COPY TO mem_ptr
	input_ptr = fopen(filename, "r"); 
	if( input_ptr != NULL ) {
		for(i = 0; i < data_num; i++)
			fscanf(input_ptr, "%lg", &mem_ptr[i]);
		fclose(input_ptr);
	}
	else {
		printf("Error: Cannot find input file, ending program...\n");
		return 1;
	}

//------------------------------------------------CREATE AND POPULATE "SNAP" FILES
	for(i = 0; i < total_snaps; i++) {
		char out_filename[sizeof "snap_1000.txt"];
		sprintf(out_filename, "snap_%d.txt", i);
		output_ptr = fopen(out_filename, "w");
		
		snap_request = i;
		snap_start = (snap_request * set_size);
		snap_end = snap_start + (set_size - 1);
		
		for(j = snap_start; j <= snap_end; j++) {
			fprintf(output_ptr, "%0.9g ", mem_ptr[j]);
			if(j % 3 == 2)
				fprintf(output_ptr, "\n");
		}
		
		fclose(output_ptr);
	}
	
	free(mem_ptr);
	return 0;

}