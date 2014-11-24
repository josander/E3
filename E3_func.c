/*
E3_func.c
*/

#include <stdio.h>
#include <math.h>
#define PI 3.141592653589

// Function that evaluates the integral of x(x+1) with the Monte Carlo method. This method uses a variable with a uniform distribution between 0 and 1.
void integral_uniform(){
	
	// Declaration and initiation of variables
	int i, j;
	double sum, sum2;
	int N = 1;
	double mean, mean2;
	double standard_Deviation;

	// Print the expected value of the integral
	printf("UNIFORM: Expected value: %.8F \n", (double) 1/6);

	// For N = 10, 100, 1000, 10000
	for(i = 0; i < 4; i++){

		N = N*10;
		double x[N];
		sum = 0;
		sum2 = 0;
		standard_Deviation = 0;
		
		// Calculate the integral
		for(j = 0; j < N; j++){

			x[j] = (double) j/N;
			sum += x[j]*(1-x[j]);
			sum2 += x[j]*(1-x[j]) * x[j]*(1-x[j]);

		}

	// Get the mean
	mean = sum/N;
	mean2 = sum2/N;
	standard_Deviation = (mean2 - mean*mean)/sqrt(N);	

	// Print the result in the terminal
	printf("For N = %i \t Integral = %.8F ± %.8F \n", N, mean, standard_Deviation);

	}

}

// Function that evaluates the integral of x(x+1) with the Monte Carlo method. This function uses importance sampling where the variable has a sine-distribution between 0 and 1.
void integral_sine(){
	
	// Declaration and initiation of variables
	int i, j;
	double sum, sum2;
	int N = 1;
	double mean, mean2;
	double standard_Deviation;
	double x[4][10000];

	// Open a file to print the variable x in
	FILE *x_file;
	x_file = fopen("distribution.data","w");

	// Print the expected value of the integral
	printf("SINE: Expected value: %.8F \n", (double) 1/6);

	// For N = 10, 100, 1000, 10000
	for(i = 0; i < 4; i++){

		N = N*10;
		sum = 0;
		sum2 = 0;
		standard_Deviation = 0;
		
		// Calculate the integral
		for(j = 0; j < N; j++){

			x[i][j] = (double) sin(PI*j/N);
			sum += x[i][j]*(1-x[i][j]);
			sum2 += x[i][j]*(1-x[i][j]) * x[i][j]*(1-x[i][j]);

		}

		// Get the mean
		mean = sum/N;
		mean2 = sum2/N;
		standard_Deviation = (mean2 - mean*mean)/sqrt(N);	

		// Print the result in the terminal
		printf("For N = %i \t Integral = %.8F ± %.8F \n", N, mean, standard_Deviation);

	}

	// Print x to distribution.data
	for(j = 0; j < N; j++){
		fprintf(x_file,"%F \t %F \t %F \t %F \n", x[0][j], x[1][j], x[2][j], x[3][j]);
	}

	// Close the data-file
	fclose(x_file); 

}

// Function that evaluates the integral of x(x+1) with the Monte Carlo method. This function uses importance sampling where the variable has a sine-distribution between 0 and 1.
void integral_metropolis(){
	
	// Declaration and initiation of variables
	int i, j;
	double sum, sum2;
	int N = 1;
	double mean, mean2;
	double standard_Deviation;
	double x[4][10000];

	// Open a file to print the variable x in
	FILE *x_file;
	x_file = fopen("distribution.data","w");

	// Print the expected value of the integral
	printf("SINE: Expected value: %.8F \n", (double) 1/6);

	// For N = 10, 100, 1000, 10000
	for(i = 0; i < 4; i++){

		N = N*10;
		sum = 0;
		sum2 = 0;
		standard_Deviation = 0;
		
		// Calculate the integral
		for(j = 0; j < N; j++){

			x[i][j] = (double) sin(PI*j/N);
			sum += x[i][j]*(1-x[i][j]);
			sum2 += x[i][j]*(1-x[i][j]) * x[i][j]*(1-x[i][j]);

		}

		// Get the mean
		mean = sum/N;
		mean2 = sum2/N;
		standard_Deviation = (mean2 - mean*mean)/sqrt(N);	

		// Print the result in the terminal
		printf("For N = %i \t Integral = %.8F ± %.8F \n", N, mean, standard_Deviation);

	}

	// Print x to distribution.data
	for(j = 0; j < N; j++){
		fprintf(x_file,"%F \t %F \t %F \t %F \n", x[0][j], x[1][j], x[2][j], x[3][j]);
	}

	// Close the data-file
	fclose(x_file); 

}

void error(){
	FILE *fr;

	fr = fopen("MC.txt","r");
	
	while(fgets(line, 80, fr) != NULL){
		sscanf (line, "%ld", &elapsed_seconds);
	}

	fclose(fr);
}
