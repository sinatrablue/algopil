#include<iostream>
#include<data_struct.h>

using namespace std;

int main {
	// Define a table with 5 node pointers in it
	node A[5];
	node *S;
	node *N;
	node *E;
	node *T;
	node *F;
	A[0] = S;
	A[1] = N;
	A[2] = E;
	A[3] = T;
	A[4] = F;

	GenForet();
	
	return EXIT_SUCCESS;
}
