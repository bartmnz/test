#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <limits.h>
#include <math.h>

struct sigaction psa;

struct prime{
	unsigned int next;
	int increment;
};

void next_prime(struct prime* number){
	if ( ! number ){
		fprintf(stderr, "ERROR: invalid input\n");
		exit(0);
	}
	// should always be incrementing by 2 up or down
	if (!(number->increment == 2) && !(number->increment == -2)){
		fprintf(stderr, "ERROR: invalid increment\n");
		exit(0);
	}
	//TODO check to ensure increasing numbers
	if (number->next < 2){
		number->next = 2;
		return;
	}else if ( number->next == 2){
		number->next = 3;
		return;
	}
	unsigned int temp = number->next+=number->increment;

	unsigned int check;

	for(;temp < UINT_MAX && temp >= 2; temp+=number->increment){
		// increment temp up or down depending on the setting in struct
		check = (unsigned int)sqrt((double)temp); // can start checking at square root
		if (! check & 1){
			//printf("%d\n", check);
			check +=1; // make sure check is odd
		}
		for(; check > 0; check--){ // even numbers are not prime
			if( check == 1){ // temp is prime
				number->next = temp;
				return;
			}
			int prime = temp % check;
			printf("temp is %d, check is %d, prime is %d\n", temp, check, prime);
			if ( ! prime ){ //temp is divisible by check -- not prime
				break;
			}

			sleep(1);
		}
	}
	fprintf(stderr, "ERROR: next number is out of bounds \n");
	exit(0);

}


void handler(int signum, siginfo_t *siginfo, void* context){
	siginfo +=1;
	printf("context is: %p\n", context);
	printf("signal is %d\n", signum);
	switch (signum){
		case SIGHUP:
			printf("HERE");
			fflush(stdout);
			break;
		case SIGUSR1:
			printf("nope");
			fflush(stdout);
			break;
		case SIGUSR2:
			printf("not gonna do it");
			fflush(stdout);
			break;
	}
}



int main(int argc, char* argv[]){
	int opt;
	while ((opt = getopt(argc, argv, "s:e:r:")) != -1){
		switch (opt){
		case 's':
			printf("S option used %d\n", atoi(optarg));
			break;
		case 'e':
			printf("E option used %d\n", atoi(optarg));
			break;
		case 'r':
			printf("R option used %d\n", atoi(optarg));
			break;
		default:
			printf("bad usage/n");
			exit(0);
		}
	}
	struct prime myNum;
	memset(&myNum, '\0', sizeof(myNum));
	myNum.next = 1;
	myNum.increment = 2;





	memset (&psa, '\0', sizeof(psa));

	psa.sa_sigaction = &handler;

	psa.sa_flags = SA_SIGINFO;
	//sigaction(SIGHUP, &psa, NULL);

	if(sigaction(SIGHUP, &psa, NULL) < 0){
		printf("ERROR: 1\n");
	}
	else if( sigaction(SIGUSR1, &psa, NULL) < 0 ){
		printf("shouldn't be here\n");
	}
	else if(sigaction(SIGUSR2, &psa, NULL) < 0 ){
		printf("bad places\n");
	}

	while(1){
		//printf("doing stuff here\n" );
		next_prime(&myNum);
		printf("next prime is %d\n", myNum.next);
		sleep(1);
	}

}
