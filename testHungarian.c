/*
    testHungarian.c - File to test Hungarian Algorithm

    -------------------------------------------------------------
    UNSW COMP2521 17s2 Assignment 2 - Yaggle
    (http://www.cse.unsw.edu.au/~cs2521/17s2/ass/ass02/Ass2.html)
    ass2grp (Yaggle) members:
    - Rahil Agrawal (z5165505) rahil.agrawal@student.unsw.edu.au
    - Dennis Gann (z5164328) d.gann@unsw.edu.au
    - Kongwei Ying (z5014882) k.ying@student.unsw.edu.au
    -------------------------------------------------------------

 */

#include "headers.h"
#include "hungarian.h"

int main() {

	// an example cost matrix

	double r[10][10] = {{1.00,  0.80,  0.80,  0.80,  0.80,  0.80,  0.80,  0.80,  0.80,  0.80},
						{1.40,  1.20,  1.00,  0.80,  0.60,  0.40,  0.20,  0.00,  0.20,  0.40},
						{0.80,  0.60,  0.60,  0.60,  0.60,  0.60,  0.60,  0.60,  0.80,  1.00},
						{2.30,  1.80,  1.50,  1.20,  1.10,  1.00,  1.30,  1.60,  1.90,  2.20},
						{0.60,  0.40,  0.20,  0.00,  0.20,  0.40,  0.60,  0.80,  1.00,  1.20},
						{1.80,  1.60,  1.40,  1.20,  1.00,  0.80,  0.60,  0.40,  0.20,  0.00},
						{1.60,  1.40,  1.20,  1.00,  0.80,  0.60,  0.40,  0.20,  0.20,  0.20},
						{0.70,  0.40,  0.30,  0.20,  0.50,  0.80,  1.10,  1.40,  1.70,  2.00},
						{1.70,  1.40,  1.10,  0.80,  0.50,  0.20,  0.30,  0.40,  0.70,  1.00},
						{0.60,  0.40,  0.40,  0.40,  0.40,  0.40,  0.60,  0.80,  1.00,  1.20}};

	double **m = (double **)calloc(10, sizeof(double *));

	for (int i = 0; i < 10; i++){
		m[i] = (double *)calloc(10, sizeof(double));

		for (int j = 0; j < 10; j++) m[i][j] =  r[i][j];

	}

	//initialise hungarian
	hProblem p = newHungarian(m, 10);

	printf("Cost Matrix:\n");
	//print cost matrix
	printHungarianCostMatrix(p);

	//solve
	printf("Cost: %lf\n", solveHungarian(p));

	//print assignment
	printf("Assignemnt:\n");
	printHungarianAssignment(p);

	disposeHungarian(p);

	return 0;
}
