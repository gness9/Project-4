#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <mpi.h>


#define WIKI_ARRAY_SIZE 50 //Default : 2000000
#define WIKI_STRING_SIZE 2003 /* The number of characters in each wiki entry. Must account for newline and terminating characters. */
#define WORDS_ARRAY_SIZE 75 /* The number of words being searched for in each wiki entry. Should be 50000 for production. */
#define WORDS_STRING_SIZE 11 /* The number of characters taken up by a word. Must account for newline and terminating characters. */
//#define NUM_THREADS 4
int NUM_THREADS;
int  ascii_sum_array[WIKI_ARRAY_SIZE];
char wiki_array[WIKI_ARRAY_SIZE][WIKI_STRING_SIZE];
int line_num = 0;

void init_array(){
	int i;
	for(i = 0; i < WIKI_ARRAY_SIZE; i++){
		ascii_sum_array[i] = 0;
	}
}

/* Read all of the wiki entries and words into local data structures from thier resprctive files. */
int read_to_memory()
{
  /* Read the wiki article into memory line by line. */
  FILE *file = fopen("wiki.50short","r");//fopen("/homes/dan/625/wiki_dump.txt", "r");

  if(file == NULL)
  {
    printf("fail");
    return -1;
  }
  
  /* Read each wiki line into memory. */
  
  char line[WIKI_STRING_SIZE];
  while(fgets(line, WIKI_STRING_SIZE, file) != NULL)
  {
	if(line_num == WIKI_ARRAY_SIZE){
		break;
	}
    strcpy(wiki_array[line_num], line);
    line_num++;
  }
  fclose(file);
  return 0;
}

void *calc_difference(void *rank){
	int i, k, startPos, endPos;
	int myID = *((int*)rank);
	
	startPos = myID * (line_num/NUM_THREADS);
	endPos = startPos + (line_num/NUM_THREADS);
	if(myID == NUM_THREADS-1){
		endPos = line_num;
	}
	printf("myID = %d startPos = %d endPos = %d \n", myID, startPos, endPos);
	for(i = startPos; i < endPos; i++){
		for(k = 0; k < WIKI_STRING_SIZE; k++){
			ascii_sum_array[i] += (int)wiki_array[i][k];
		}
	}	
	
}

void print_output(){
	int i;
	for(i = 0; i < line_num-1; i++){
		printf("Line %d - Line %d = %d\n", i+1, i+2, (ascii_sum_array[i] - ascii_sum_array[i+1]));
	}
}

int main(){
	
	struct timeval t1, t2, t3, t4, t5;
	double elapsedTime;
	int numSlots, myVersion = 3; //base = 1, pthreads = 2, openmp = 3, mpi = 4
	int i, rc;
	int numtasks, rankl
	MPI_Status Status;
	
	rc = MPI_Init(&argc,&argv);
	if(rc != MPI_SUCCESS){
		printf("ERRROR starting MPI Program. Terminating. \n");
		MPI_ABORT(MPI_COMM_WORLD, rc);
	}
	
	MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
	MPI_Comm_size(MPI_COMM_WORLD,&rank);
	
	NUM_THREADS = numtasks;
	printf("size = %d rand = %d\n", numtasks, rank);
	fflush(stdout);
	
	gettimeofday(&t1, NULL);
	if(rank == 0){
		init_array();
	}
	gettimeofday(&t2, NULL);
	if(read_to_memory() == 0)
	{
		gettimeofday(&t3, NULL);
		
		MPI_Bcast(wiki_array, WIKI_ARRAY_SIZE * WIKI_STRING_SIZE, MPI_CHAR, 0, MPI_COMM_WORLD);
		calc_difference(&rank);
		MPI_Reduce(ascii_sum_array, ascii_sum_array, WIKI_ARRAY_SIZE, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
		
		gettimeofday(&t4, NULL);
		
		if(rank == 0){
			print_output();
		}
	}
	else{
		return -1;
	}
	
	
	MPI_Finalize();
	return 0;
	gettimeofday(&t5, NULL);
	
	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0; //sec to ms
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0; // us to ms
	printf("Time to Init Array: %f\n", elapsedTime);

	elapsedTime = (t3.tv_sec - t2.tv_sec) * 1000.0; //sec to ms
	elapsedTime += (t3.tv_usec - t2.tv_usec) / 1000.0; // us to ms
	printf("Time to read: %f\n", elapsedTime);

	elapsedTime = (t4.tv_sec - t3.tv_sec) * 1000.0; //sec to ms
	elapsedTime += (t4.tv_usec - t3.tv_usec) / 1000.0; // us to ms
	printf("Time to calculate chars: %f\n", elapsedTime);

	elapsedTime = (t5.tv_sec - t1.tv_sec) * 1000.0; //sec to ms
	elapsedTime += (t5.tv_usec - t1.tv_usec) / 1000.0; // us to ms
	printf("DATA, %d, %s, %f, %d\n", myVersion, getenv("SLURM_CPUS_ON_NODE"),  elapsedTime, NUM_THREADS);

	printf("Main: program completed. Exiting.\n");
}



























