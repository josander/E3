/*
 E3.c
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "E3_func.h"
#define PI 3.141592653589

/* Main program */
int main()
{
	// Seed for generating random numbers
	srand(time(NULL));


	// Task 1: calculate the integral for different N
	integral_uniform();

	// Task 2: calculate the integral for different N using importance sampling
	integral_sine();

	// Task 3: calculate the integral for different N using the Metropolis algorithm
	//integral_metropolis();

	// Task 4: Evaluate the statistical inefficiency
	//error();

	printf("Done! \n");
}

