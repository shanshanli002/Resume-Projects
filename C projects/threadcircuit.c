#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdint.h>
/*pthread.h allows us to use native thread functions like pthread_create */
#include <pthread.h>
#include <unistd.h>
//lab direction stated number of threads will be 6.
#define TOTAL_THREADS 6
/* Return 1 if 'i'th bit of 'n' is 1; 0 otherwise */
#define EXTRACT_BIT(n,i) ((n&(1<<i))?1:0)

/* check_circuit was from threadseqcircuit.zip from cop4338 */
int check_circuit (int z, int t_id) {
  int v[16];        /* Each element is a bit of z */
  int i;

  for (i = 0; i < 16; i++) v[i] = EXTRACT_BIT(z,i);
  if ((v[0] || v[1]) && (!v[1] || !v[3]) && (v[2] || v[3])
      && (!v[3] || !v[4]) && (v[4] || !v[5])
      && (v[5] || !v[6]) && (v[5] || v[6])
      && (v[6] || !v[15]) && (v[7] || !v[8])
      && (!v[7] || !v[13]) && (v[8] || v[9])
      && (v[8] || !v[9]) && (!v[9] || !v[10])
      && (v[9] || v[11]) && (v[10] || v[11])
      && (v[12] || v[13]) && (v[13] || !v[14])
      && (v[14] || v[15])) {
    printf ("%d) %d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d\n", t_id,
	    v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7],v[8],v[9],
	    v[10],v[11],v[12],v[13],v[14],v[15]);
    return 1;
  } else return 0;
}
/*defining what each thread is going to have*/
typedef struct thread_info
{
    /*each tread is going to have an id from 0-5 and */	
    int thread_id;
    double body;
}thread_info;
/*pthread_mutex acts as a lock */
pthread_mutex_t mutex;
int total;
/*this function will be passed into pthread_create when declared.*/
void* thread_helper(void *arg)
{
    int count, i;
    count = 0;
    thread_info *single_thread = (thread_info*)arg;
    int current_thread_id = single_thread->thread_id;
    	
    /*mutex_lock fuction from pthread. this function takes the mutex variable. this locking function ensures that the next thread will have to wait until the mutex is unlocked.*/
    pthread_mutex_lock(&mutex);    
    /*this for loop was given from starter code from lab4.*/
    for(i=0; i<65536; i++)
    {
        /*added the current_thread_id so it can print out the thread id along with the output*/
	count +=check_circuit(i, current_thread_id);
        total = count;
    }
    /*stop after the last thread and print this out to reveal the number of solutions.*/
    if(current_thread_id == ((TOTAL_THREADS-1)))
    {
	/*changed count variable to total from the skeleton code provided */    
        printf("There are %d solutions\n", total);
    }	    

    /*unlocking the mutex and exits the thread*/
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);    
}

int main (int argc, char *argv[])
{
    int i;
    /*creating the array of threads, will have 6 elements to represent the total number of threads*/
    pthread_t threads_array[TOTAL_THREADS];
    thread_info arr_threads_info[TOTAL_THREADS];
    /*initializing the mutex to be used*/
    pthread_mutex_init(&mutex, NULL);
    for(i = 0; i<TOTAL_THREADS; i++)
    {
        /*assign each thread_id for each thread in the array with an id associated with i. Where it is in the array is the id.*/
        arr_threads_info[i].thread_id = i;
	/*this is creating thread using helper function and is from the pthread library*/
        pthread_create(&threads_array[i], NULL, thread_helper, &arr_threads_info[i]);
    }

    /* this loop will run each thread*/
    for(i = 0; i<TOTAL_THREADS; i++)
    {
        pthread_join(threads_array[i], NULL);
    }
    return 0;
}
