/*
    pagerank.c - Calculate pageranks and write to pagerankList.txt

    -------------------------------------------------------------
    UNSW COMP2521 17s2 Assignment 2 - Yaggle
    (http://www.cse.unsw.edu.au/~cs2521/17s2/ass/ass02/Ass2.html)
    ass2grp (Yaggle) members:
    - Rahil Agrawal (z5165505) rahil.agrawal@student.unsw.edu.au
    - Dennis Gann (z5164328) d.gann@unsw.edu.au
    - Kongwei Ying (z5014882) k.ying@student.unsw.edu.au
    -------------------------------------------------------------

*/

#include "pagerank.h"

int main(int argc, char *argv[]) {
	Queue collectionUrls1 = getCollectionUrls();
	Graph urlGraph = createUrlGraph(collectionUrls1);
	if (argc != 4)
		pageRankWeights(0.85, 0.00001, 1000, urlGraph);
	else {
		char *buf;
		pageRankWeights(strtod(argv[1], &buf), strtod(argv[2], &buf), atoi(argv[3]), urlGraph);
	}
	disposeQueue(collectionUrls1);
	disposeGraph(urlGraph);
	return EXIT_SUCCESS;
}

// Base function to calculate pageranks using formula provided in
// http://www.cse.unsw.edu.au/~cs2521/17s2/ass/ass02/Ass2.html and
// http://www.cse.unsw.edu.au/~cs2521/17s2/ass/ass02/page1725348.pdf
void pageRankWeights(double damp, double diffPR, int maxIterations, Graph g) {
	// N = number of Urls in Graph
	int N = nVertices(g);
	// Initialise pageranks of all pages to 1/N
	for (int i = 0; i < N; i++) setPagerankBefore(g, i, (1.0 / (double)N));
	// Initialise counters and variables for looping
	int iteration = 0;
	double diff = diffPR;
	double newDiff = 0.0;
	// Perform algorithm until difference in pageranks is less tahn diffPR
	// or iterations exceed maximum iterations provided
	while (iteration < maxIterations && diff >= diffPR){
		newDiff = 0.0;
		// Find pagerank using given formula
		for (int i = 0; i < N; i++){
			double value = (double)(1.0 - damp) / (double)N + damp *pageRankIncoming(g, i);
			setPagerankAfter(g, i, value);
		}
		// Calculate difference in pageranks
		for (int i = 0; i < N; i++){
			newDiff += fabs(getPagerankAfter(g, i) - getPagerankBefore(g, i));
		}
		// Increment iteration
		iteration += 1;
		// Update difference
		diff = newDiff;
		// Update pageranks
		for (int i = 0; i < N; i++) setPagerankBefore(g, i, getPagerankAfter(g, i));
	}
	// Write pageranks to a pagerankList.txt
	showPageRanks(g);
}

// Function to calculate the product of PageRank, In-weight and Out-weight
double pageRankIncoming(Graph g, int i) {
	// declare variables used to calculate the product of In-Weight
	// Outweight and Pagerank of all nodes that have an outgoing link to
	// the current page and sum these products
	double product = 1.0;
	double sum = 0.0;
	for (int j = 0; j < nVertices(g); j++){
		if (isEdge(g, j, i)){
			// Calculate the sum of the products as defined above
			product = getPagerankBefore(g, j) * Win(g, j, i) * Wout(g, j, i);
			sum += product;
		}

	}
	return sum;
}

// Function to calculate the In-Weight
double Win(Graph g, int j, int i) {
	// Declaring variables to calculate InWeight
	int inLinksI = numInlinks(g, i);
	int inLinksSum = 0;
	for (int k = 0; k < nVertices(g); k++){
		if (isEdge(g, j, k)){
			// Calculate the sum of incoming links to pages that have an
			// outoging link to the current page
			inLinksSum += numInlinks(g, k);
		}
	}
	// Divide the number of Incoming links of the current page by the
	// sum calculated above and that is InWeight of the current page
	return (double)inLinksI / (double)inLinksSum;
}

// Function to calculate the Out-Weight
double Wout(Graph g, int j, int i) {
	// Declaring variables to calculate OutWeight
	double outLinksI = (numOutlinks(g, i) ? numOutlinks(g, i) : 0.5);
	double outLinksSum = 0;
	for (int k = 0; k < nVertices(g); k++){
		if (isEdge(g, j, k)){
			// Calculate the sum of outgoing links to pages that have an
			// outoging link to the current page
			outLinksSum += (numOutlinks(g, k) ? numOutlinks(g, k) : 0.5);
		}
	}
	// Divide the number of Outoging links of the current page by the
	// sum calculated above and that is OutWeight of the current page
	return (double)outLinksI / (double)outLinksSum;
}
