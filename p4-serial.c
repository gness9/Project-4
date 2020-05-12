#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <omp.h>

#define WIKI_ARRAY_SIZE 50 //Default : 2000000
#define WIKI_STRING_SIZE 2003 /* The number of characters in each wiki entry. Must account for newline and terminating characters. */
#define WORDS_ARRAY_SIZE 75 /* The number of words being searched for in each wiki entry. Should be 50000 for production. */
#define WORDS_STRING_SIZE 11 /* The number of characters taken up by a word. Must account for newline and terminating characters. */


int  ascii_sum_array[WIKI_ARRAY_SIZE];
char wiki_array[WIKI_ARRAY_SIZE][WIKI_STRING_SIZE];
int line_num = 0;

void init_array(){
	for(int i = 0; i < WIKI_ARRAY_SIZE; i++){
		ascii_sum_array[i] = 0;
	}
}

/* Read all of the wiki entries and words into local data structures from thier resprctive files. */
int read_to_memory()
{
  /* Read the wiki article into memory line by line. */
  FILE *file = fopen("wiki.50short", "r");

  if(file == NULL)
  {
    printf("fail");
    return -1;
  }
  
  /* Read each wiki line into memory. */
  
  char line[WIKI_STRING_SIZE];
  while(fgets(line, WIKI_STRING_SIZE, file) != NULL)
  {
    strcpy(wiki_array[line_num], line);
    line_num++;
  }
  fclose(file);
  return 0;
}

void calc_difference(){
	for(int i = 0; i < line_num; i++){
		for(int k = 0; k < WIKI_STRING_SIZE; k++){
			ascii_sum_array[i] += (int)wiki_array[i][k];
		}
	}
	
	for(int i = 0; i < line_num-1; i++){
		printf("Line %d - Line %d = %d\n", i+2, i+1, (ascii_sum_array[i+1] - ascii_sum_array[i]));
	}
}

int main(){
	init_array();
	if(read_to_memory() == 0)
	{
		calc_difference();
	}
	else{
		return -1;
	}
}



























