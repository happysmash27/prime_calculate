#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <math.h>

int is_prime_u(unsigned int num){
     unsigned int max_num = sqrt(num);
     for (unsigned int i = 2; i<=max_num; i++){
	  if (num%i == 0){
	       return 0;
	  }
     }
     return 1;
}

int is_prime_ul(unsigned long num){
     unsigned long max_num = sqrt(num);
     for (unsigned long i = 2; i<=max_num; i++){
	  if (num%i == 0){
	       return 0;
	  }
     }
     return 1;
}

int is_prime_ull(unsigned long long num){
     unsigned long long max_num = sqrt(num);
     for (unsigned long long i = 2; i<=max_num; i++){
	  if (num%i == 0){
	       return 0;
	  }
     }
     return 1;
}

int main(int argc, char** argv){
     //Check if we have one argument
     if (argc!=2){
	  fprintf(stderr, "Usage: `prime_calculate <max_num>`, with <max_num> being a positive integer smaller than %llu to calculate primes to\n", ULLONG_MAX);
	  return 1;
     }

     //Convert input to number
     errno = 0;
     unsigned long long max_num = strtoull(argv[1], NULL, 10);
     if (errno!=0){
	  perror("Invalid argument");
     }

     //Todo: Use a switch or something?
     //Tests if we can use a function on smaller, more optimised numbers
     if (max_num<=ULONG_MAX){

	  //Unsigned int
	  if (max_num<=UINT_MAX){
	       unsigned int max_num_sm = max_num;
	       for (unsigned int i=1; i<=max_num_sm; i+=2){
		    if(is_prime_u(i)){
			 fprintf(stdout, "%u\n", i);
		    }
	       }
	       return 0;
	  }

	  //Unsigned long int
	  unsigned long max_num_sm = max_num;
	  for (unsigned long i=1; i<= max_num_sm; i+=2){
	       if(is_prime_ul(i)){
		    fprintf(stdout, "%lu\n", i);
	       }
	  }
	  return 0;
     } else {
	  //Unsigned long long int
	  for (unsigned long long i=1; i<= max_num; i+=2){
	       if(is_prime_ull(i)){
		    fprintf(stdout, "%llu\n", i);
	       }
	  }
	  return 0;
     }
}
	       
