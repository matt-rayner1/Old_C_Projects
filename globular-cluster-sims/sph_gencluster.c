#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <string.h>

/* 	This is the single cluster generation program for my N-body report.
	1) Asks user for:
		i) 		name of output file
		ii) 	number of particles to generate, 
		iii) 	value of "a" for the plummer density
	2) Calculates mass of each particle, and after opening a file, puts no. of particles
		then mass at the start of the file.
	3) Generates the position of a particle in spherical coords.
	4) Accepts or rejects this point using the plummer density.
	5) If point is accepted, it's velocity is calculated using v_calc().
	6) Position and velocity are converted to cartesian, and put into file.

	The author understands that "LOOP: do..." is bad practice, 
		but the program works anyway...
*/

//------------------------------------------------------------------------PROTOTYPES
double v_calc(double r);  //Calculates magnitude of velocity for point with length r
double rand_gen();		  //Generates random number between 0 and 1


int main()
{
//------------------------------------------------------------------------DEFINITIONS	
	int particles;
	double mass;
	double a;
	double x,y,z;
	double vx,vy,vz;
	double r,theta,phi;
	double v_mag, v_theta, v_phi;
	double plum;
	int i = 0;
	char file_name[50];
	FILE *sphere_cluster;
//---------------------------------------------------------------------------RNG SEED
	srand(time(NULL));
//--------------------------------------------------------USER INPUT/MASS CALCULATION
	printf("Please enter output filename (include .txt, less than 50 chars)\n");
	gets(file_name);	
	printf("No. of Particles?: ");
    scanf("%d", &particles);
	printf("\nValue of a?: ");
	scanf("%lf", &a);

	
	sphere_cluster = fopen(file_name, "w");		//Opens file, checks if successful etc.
	if(sphere_cluster == NULL) {
		printf("Error creating output file, closing program\n");
		return 1;
	}

    mass = 1/((double) particles); 					//Mass of each particle calculated
	
	fprintf(sphere_cluster, "%d\n", particles);		//Particles put in file
    fprintf(sphere_cluster, "0\n");
//---------------------------------------------------------------POSITION CALCULATION	
	LOOP:do{
		r = pow(rand_gen(), 1.0/3.0);

		plum = (3.0/(4.0*M_PI*pow(a,3.0)))* pow( 1 + ((r*r)/(a*a)) , -5.0/2.0);
		
		if( plum < pow(rand_gen(), 1.0/3.0) )	//restarts loop if plum < random no between 0 and 1
			goto LOOP;						//i.e.  f(x) < Ag(x) ---> MONTE CARLO rejection
		else {
			v_mag = v_calc(r);				//else computes points and velocities,
											//and prints into file
			phi = 2 * M_PI * rand_gen();
			theta = acos( (2 * rand_gen()) - 1 );
			v_phi = 2 * M_PI * rand_gen();
			v_theta = acos( (2 * rand_gen()) - 1 );
			
			x = r * sin(theta) * cos(phi);
			y = r * sin(theta) * sin(phi);
			z = r * cos(theta);
			vx = v_mag * sin(v_theta) * cos(v_phi);
			vy = v_mag * sin(v_theta) * sin(v_phi);
			vz = v_mag * cos(v_theta);
			
			fprintf(sphere_cluster, "%0.9g %0.9g %0.9g %0.9g %0.9g %0.9g %0.9g\n", mass, x, y, z, vx, vy, vz);
			printf("Point %d accepted\n", i);
			i++;
		}
	} while (i < particles);
//--------------------------------------------------------------SUCCESSFUL PROGRAM END
	printf("\aGeneration \a complete, \aexiting program.");
	return 0;
}


//------------------------------------------------------------------------RNG Function
// generates random point between 0 and 1, returns as a double
double rand_gen() {
	return (double)rand()/(double)RAND_MAX;
}

//----------------------------------------------------------------------v_mag Function
//Uses a second Monte Carlo rejection technique to generate a velocity for each point
double v_calc(double r) {
	LOOP: do {
		double c, d;
		
		c = rand_gen();
		d = 0.1 * rand_gen();
		
		if( (c*c)*pow( (1 + (c*c)), 7.0/2.0) < d) //Restarts loop if conditions for c are not met
			goto LOOP;
		else
			return (c * sqrt(2) * pow((1+ (r*r)), -1.0/4.0));
	} while ( 1==1 );
}