#include <stdio.h>
#include <time.h>       // for clock_t, clock(), CLOCKS_PER_SEC

// TODO this should probably be a dynamic array.
#define MAXFILES = 10 ^ 6 /* Manimum number of Notes to search,
			     10^6<1GB memory */
#define VECSIZE (500*1000) // TODO I'm limited to (int)1.3E6 here /* (128 choose 3)<500E3 */

/* Variables */
int i;
float x;

/* Function Declarations */
float arr_sum(float arr[], int arr_size);
void fill_array(float arr[], int n);
void read_file(char *filename, int *count_array);


/* Main */

int main(int argc, char *argv[]) {
  char *filename = argv[1];
  int doc_vec[VECSIZE];
  read_file(filename, doc_vec);
  printf("the value of the array is %i", doc_vec[1]);
  /* float myvec[VECSIZE]; */
  /* fill_array(myvec, VECSIZE); */
  /* printf("sum is: %f\n\n", arr_sum(myvec, VECSIZE)); */
  /* return 0; */
}


void fill_array(float arr[], int n) {
  int i; 
  for (i = 0; i < n; ++i) {
    x = i;
    arr[i] = x;
    /* printf("\n%i", i); */
  }
}

float arr_sum(float arr[], int arr_size) {
  float running_sum = 0;	/* Running tally */
  int i; 			/* counting */
    for (i = 0; i < arr_size; ++i) {
	x = i;
	if (arr[i] != 0) {
	    running_sum+=arr[i];
	}
	    }
    return running_sum;
}


void read_file(char *filename, float *count_array) {
  printf("The First Argument should be a file:\n");
  int i = 0;
  while (filename[i] != '\0') {
    printf("%c", filename[i]);
    i++;
  }
  printf("\n");

  FILE *fp = fopen(filename, "r");
  int c; //declare c as int so it can store '\0'
  if (fp == NULL) {
    perror("Error Opening File");
  } else {
    while ((c=fgetc(fp)) != EOF) {
      //      printf("%c", c); 		/* Cat the File */
    } 
  }

  count_array[1] = 11;

}
