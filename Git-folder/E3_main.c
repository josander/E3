/*
E2_main.c
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "E2_func.h"
#define PI 3.141592653589


/* Main program */
int main()
{
	/* Declaration of variables */
	int nbr_of_timesteps;
	double timestep;
	int i,j,n,nbr_of_particles;
	double kappa;
	double m;
	double alpha;


	/* Set variables */
	nbr_of_particles = 32; /* The number of particles*/
	alpha = 0.1;
	timestep = 0.1;
	nbr_of_timesteps = 250000; /* nbr_of_timesteps+1 = power of 2, for best speed */
	m = 1.0;
	kappa = 1.0;
    
    	/* Declartion of arrays*/
    	double q[nbr_of_particles],v[nbr_of_particles],a[nbr_of_particles];
    	double Q[nbr_of_particles];
	double P[nbr_of_particles];
	double omega[nbr_of_particles];
	double E[nbr_of_particles];
	double eTot[nbr_of_timesteps+1];
	double energy[nbr_of_particles],pe[nbr_of_particles],ke[nbr_of_particles];

	/*Initialize with zeros */
	for (i = 0; i < nbr_of_particles; i++){
		Q[i] = 0.0;
		P[i] = 0.0;
		q[i] = 0.0;
		v[i] = 0.0;
		a[i] = 0.0;
		energy[i] = 0.0;
		pe[i] = 0.0;
		ke[i] = 0.0;
		E[i] = 0.0;
	}

	/* Initial conditions */
	P[0] = sqrt(2 * nbr_of_particles);
	Q[0] = 0;

	/* Set initial displacements and velocites */
	inverseTransform(nbr_of_particles, Q, q, m);
	inverseTransform(nbr_of_particles, P, v, m);

	/* Calculate initial accelerations based on initial displacements */
	calc_acc(a, q, m, kappa, nbr_of_particles, alpha);

	/* Initial energies */
	calc_pe(q,kappa,nbr_of_particles,pe);
	calc_ke(v,nbr_of_particles,m,ke);
	
	for(i = 0; i < nbr_of_particles; i++){
		energy[i] = pe[i] + ke[i];
	}

	/*Transform the displacements and velocities to normal modes */
	transform(nbr_of_particles, q, Q, m);
	transform(nbr_of_particles, v, P, m);

	/* Calculate the energy of every mode*/
	eTot[0] = 0;
	for (n = 0; n < nbr_of_particles; n++){
		omega[n] = 2 * sqrt(kappa / m) * sin((n + 1) * PI / (nbr_of_particles + 1));
		E[n] = (P[n] * P[n] + omega[n] * omega[n] * Q[n] * Q[n]) / 2;
		eTot[0] += E[n];
        }

    
    	/* Print initial displacement and energy data to output file */
	FILE *d_file;
	d_file = fopen("disp.data","w");

	FILE *modeE_file;
	modeE_file = fopen("modeEnergy.data","w");

	FILE *e_file;
	e_file = fopen("energy.data","w");

	FILE *totME_file;
	totME_file = fopen("totModeEnergy.data","w");
    
	fprintf(d_file, "%.5f", 0.0);
	fprintf(e_file, "%.5f", 0.0);
	fprintf(modeE_file, "%.5f", 0.0);
	fprintf(totME_file, "%.5f \t %e \n", 0.0, eTot[0]);

	for (n = 0; n < nbr_of_particles; n++){
		fprintf(d_file, "\t %e", q[n]);
		fprintf(e_file, "\t %e", energy[n]);
		fprintf(modeE_file, "\t %e", E[n]);
	}

	fprintf(d_file, "\n");
	fprintf(e_file, "\n");
	fprintf(modeE_file, "\n");
	

	/* timesteps according to velocity Verlet algorithm */
	for (i = 1; i < nbr_of_timesteps + 1; i++){
		/* v(t+dt/2) */
		for (j = 0; j < nbr_of_particles; j++){
		    v[j] += timestep * 0.5 * a[j];
		} 

		/* q(t+dt) */
		for (j = 0; j < nbr_of_particles; j++){
		    q[j] += timestep * v[j];
		}

		/* a(t+dt) */
		calc_acc(a, q, m, kappa, nbr_of_particles, alpha);

		/* v(t+dt) */
		for (j = 0; j < nbr_of_particles; j++){
		    v[j] += timestep * 0.5 * a[j];
		} 

		/* Calculate energies */
		calc_pe(q,kappa,nbr_of_particles, pe);
		calc_ke(v,nbr_of_particles,m, ke);
		for(n=0; n<nbr_of_particles; n++){
			energy[n] = pe[n] + ke[n];

		}

		/*Transform the displacements and velocities to normal modes */
		transform(nbr_of_particles, q, Q, m);
		transform(nbr_of_particles, v, P, m);

		eTot[i] = 0;
		for (n = 0; n < nbr_of_particles; n++){
			omega[n] = 2 * sqrt(kappa / m) * sin((n+1) * PI / (2*(nbr_of_particles + 1)));
			E[n] = (P[n] * P[n] + omega[n] * omega[n] * Q[n] * Q[n]) / 2;
			eTot[i] += E[n];
        	}


        	/* Print current displacement and energy data to output file */
		fprintf(d_file, "%.5f", i*timestep);
		fprintf(e_file, "%.5f", i*timestep);
		fprintf(modeE_file, "%.5f", i*timestep);
		fprintf(totME_file, "%.5f \t %e \n", i*timestep, eTot[i]);
	
		for (n = 0; n < nbr_of_particles; n++){
			fprintf(d_file, "\t %e", q[n]);
			fprintf(e_file, "\t %e",energy[n]);
			fprintf(modeE_file, "\t %e",E[n]);
		}

		fprintf(d_file, "\n");
		fprintf(e_file, "\n");
		fprintf(modeE_file, "\n");
	}
    
    	/* Close the displacement and energy output files */
   	fclose(d_file);
    	fclose(e_file);
    	fclose(modeE_file);
    	fclose(totME_file);

	return 0;    
}
