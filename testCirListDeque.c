#include "cirListDeque.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
        
	struct cirListDeque *q;
	q = createCirListDeque();
		printf("deque sentinel initialized.")
	if(isEmptyCirListDeque(q) == 1)
		printf("deque is empty.\n")
	addFrontCirListDeque(q, 1);
	addBackCirListDeque(q, 2);
	addFrontCirListDeque(q, 3);
	addBackCirListDeque(q, 4);
	addFrontCirListDeque(q, 5);
	printCirListDeque(q);
	if(isEmptyCirListDeque(q) == 1)
		printf("deque is empty.\n")
	removeFrontCirListDeque(q);
	printCirListDeque(q);
	removeBackCirListDeque(q);
	printCirListDeque(q);
	addFrontCirListDeque(q, 6);
	printCirListDeque(q);
	addBackCirListDeque(q, 7);
	printCirListDeque(q);
	printf("front is: %f\n", frontCirListDeque(q));
	printf("back is: %f\n", backCirListDeque(q));
	freeCirListDeque(q);

	/* Test your linked list in here! */
	/* Try to write the tests yourself */

	printf("Hello from test code!\n");
	return 0;
}


