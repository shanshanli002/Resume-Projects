#include <stdio.h>
#include <unistd.h>
#include <mpi.h>

#define N_NUM 25000

/*prime function replaced check_circuit function in original circuit.c file. this function will be used to validate the prime numbers. the return of an int is going to be added to the count variable to update total number of primes found.*/
int prime (int id, int max) {
  int i;
  int j;
  int z = max;
  /*subcounter holds number of factors for each num*/
  int sub_counter = 0;
  /*total number of primes from n to n*/
  int total_counter = 0;

  /*i holds the value of num, each num is going to be checked if it is a prime number. each process will start at 2  to N_NUM because 0 and 1 are not primes.*/
  for(i = 2; i<= z; i++){
    /*sub_counter needs to be reset after each for loop, so it can hold the number of factors found after each loop*/
    sub_counter = 0;

    /*this nested for loop is going to divide the number being checked by 1 up to the number itself.*/
    for(j = 1; j<=i; j++){
      /*if the loop finds a factor, it's going to increase the subcounter. the subcounter is not total count; used to verify if it's a prime number. */
      if(i%j == 0){
        sub_counter = sub_counter + 1;
      }
    }
    /*prime numbers should only have factors 1 and itself, so the subcounter should be 2. if the subcount is not 2, that means it has more factors, and it's not a prime number.*/
    if(sub_counter == 2){
      total_counter = total_counter + 1;
      /*circuit.c had printf line where process id and value was also outputted in this function, but was not able to get it working. id and primes found are in main.*/
    }
  }
  return total_counter;
}

int main (int argc, char *argv[]){
  int count;            /* Solutions found by this proc */
  double elapsed_time;  /* Time to find, count solutions */
  int global_count ;     /* Total number of solutions */
  int i;
  int id;               /* Process rank */
  int p;                /* Number of processes */
  char hostname[1024];
  

  MPI_Init (&argc, &argv);
  /*id of first process is 0*/
  MPI_Comm_rank (MPI_COMM_WORLD, &id);
  /*fprintp = 0*/
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  //printf("%d process\n", p);
  /*removed print statement displaying hostname*/
  hostname[1023] = '\0';
  gethostname(hostname, 1023);
  
  /* Start timer */
  MPI_Barrier (MPI_COMM_WORLD);
  elapsed_time = - MPI_Wtime();

  count = 0;
  /*each process is going to call the prime function and output will add to count for that process.*/
  for(i = id; i< 7; i+=p ){
    /*made another variable called p_count to hold value of singular process prime total. this value gets updated based on the process*/
    int p_count = prime(id, N_NUM);
    id = i;
    /*value used to get global count*/
    count += prime(id, N_NUM);
    /*print each id and primary num count*/
    printf("ID %d) %d primes\n", id, p_count);
  }
  
  /*lecture stated only process 0 will get the result. saving the global_count variable.*/
  MPI_Reduce (&count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); 
  	
  /* Stop timer */
  elapsed_time += MPI_Wtime();
  
  /*Master process, which will print out the execution time and total number of all the primes found. stops at 6 since there are only 7 processes and process id starts at 0  */
  if(id == 6){
    printf("Execution time %8.6f\n", elapsed_time);
    printf("There are %d total prime numbers\n", global_count);
  }
  
  MPI_Finalize();
  return 0;
}
