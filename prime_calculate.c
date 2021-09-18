#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#include <sys/resource.h>

#define BIT_SET(data, address) data[(address)/8]&(1<<((address)%8))
#define BIT_CLEARED(data, address) (data[(address)/8]&(1<<((address)%8)))==0
#define SET_BIT(data, address) data[(address)/8]|=(1<<((address)%8))
#define CLEAR_BIT(data, address) data[(address)/8]^=(1<<((address)%8))

int use_malloc(size_t size){
     struct rlimit rlim;
     if(getrlimit(RLIMIT_STACK, &rlim)){
	  perror("Unable to get stack size");
	  //Do not use malloc, as we can not ensure the stack is safe
	  return 1;
     }
     //Just use 3/4 our max stack size for now.
     //We could probably make it more efficient in the future
     if (size>(rlim.rlim_cur*(3/4))){
	  return 1;
     } else {
	  return 0;
     }
}

void init_mem_uint8(size_t size, uint8_t* memory){
     for (size_t i=0; i<size; i++){
	  memory[i] = 0;
     }
}

int is_prime_u(unsigned int num){
     unsigned int max_num = sqrt(num);
     for (unsigned int i = 2; i<=max_num; i++){
	  if (num%i == 0){
	       return 0;
	  }
     }
     return 1;
}

void check_primes_u(unsigned int max){
     fputc('2', stdout);
     fputc('\n', stdout);
     for (unsigned int i=3; i<=max; i+=2){
	  if(is_prime_u(i)){
	       fprintf(stdout, "%u\n", i);
	  }
     }
}

void sieve_u(unsigned int max){
     fputc('2', stdout);
     fputc('\n', stdout);
     unsigned int half_max = max/2;
     //Allocate memory
     size_t needed_nums = half_max-1+(max%2);
     size_t needed_mem_size = (needed_nums/8)+((needed_nums%8)>0);
     int should_use_malloc = use_malloc(needed_mem_size);
     uint8_t* sieve;
     if (should_use_malloc){
	  sieve = malloc(needed_mem_size);
     } else {
	  uint8_t sieve_arr[needed_mem_size];
	  sieve = sieve_arr;
     }
     //Fill sieve
     init_mem_uint8(needed_mem_size, sieve);
     for (unsigned int divnum=3; divnum<=half_max; divnum+=2){
	  unsigned int max_fill_number = max-(max%divnum);
	  for (unsigned int j=(divnum*2); j<=max_fill_number; j+=divnum){
	       if (j%2){
		    SET_BIT(sieve, (j/2)-1);
	       }
	  }
     }
     //Print primes
     for (unsigned int i=0; i<needed_nums; i++){
	  if (BIT_CLEARED(sieve, i)){
	       fprintf(stdout, "%u\n", (i*2)+3);
	  }
     }

     //Free resources
     if (should_use_malloc){
	  free(sieve);
     }
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

void check_primes_ul(unsigned long max){
     fputc('2', stdout);
     fputc('\n', stdout);
     for (unsigned long i=3; i<=max; i+=2){
	  if(is_prime_ul(i)){
	       fprintf(stdout, "%lu\n", i);
	  }
     }
}

void sieve_ul(unsigned long max){
     fputc('2', stdout);
     fputc('\n', stdout);
     unsigned long half_max = max/2;
     //Allocate memory
     size_t needed_nums = half_max-1+(max%2);
     size_t needed_mem_size = (needed_nums/8)+((needed_nums%8)>0);
     uint8_t* sieve = malloc(needed_mem_size);
     //Fill sieve
     init_mem_uint8(needed_mem_size, sieve);
     for (unsigned long divnum=3; divnum<=half_max; divnum+=2){
	  unsigned long max_fill_number = max-(max%divnum);
	  for (unsigned long j=(divnum*2); j<=max_fill_number; j+=divnum){
	       if (j%2){
		    SET_BIT(sieve, (j/2)-1);
	       }
	  }
     }
     //Print primes
     for (unsigned long i=0; i<needed_nums; i++){
	  if (BIT_CLEARED(sieve, i)){
	       fprintf(stdout, "%lu\n", (i*2)+3);
	  }
     }

     //Free resources
     free(sieve);
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

void check_primes_ull(unsigned long long max){
     fputc('2', stdout);
     fputc('\n', stdout);
     for (unsigned long long i=3; i<=max; i+=2){
	  if(is_prime_ull(i)){
	       fprintf(stdout, "%llu\n", i);
	  }
     }
}

void sieve_ull(unsigned long long max){
     fputc('2', stdout);
     fputc('\n', stdout);
     unsigned long long half_max = max/2;
     //Allocate memory
     size_t needed_nums = half_max-1+(max%2);
     size_t needed_mem_size = (needed_nums/8)+((needed_nums%8)>0);
     uint8_t* sieve = malloc(needed_mem_size);
     //Fill sieve
     init_mem_uint8(needed_mem_size, sieve);
     for (unsigned long long divnum=3; divnum<=half_max; divnum+=2){
	  unsigned long long max_fill_number = max-(max%divnum);
	  for (unsigned long long j=(divnum*2); j<=max_fill_number; j+=divnum){
	       if (j%2){
		    SET_BIT(sieve, (j/2)-1);
	       }
	  }
     }
     //Print primes
     for (unsigned long long i=0; i<needed_nums; i++){
	  if (BIT_CLEARED(sieve, i)){
	       fprintf(stdout, "%llu\n", (i*2)+3);
	  }
     }

     //Free resources
     free(sieve);
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
	       //check_primes_u(max_num_sm);
	       sieve_u(max_num_sm);
	       return 0;
	  }

	  //Unsigned long int
	  unsigned long max_num_sm = max_num;
	  //check_primes_ul(max_num_sm);
	  sieve_ul(max_num_sm);
	  return 0;
     } else {
	  //Unsigned long long int
	  //check_primes_ull(max_num);
	  sieve_ull(max_num);
	  return 0;
     }
}
	       
