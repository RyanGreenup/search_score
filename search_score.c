
/* * Includes */
#include <math.h>
#include <stdio.h>
#include <time.h> // for clock_t, clock(), CLOCKS_PER_SEC

/* * Symbolic Constants */
// TODO this should probably be a dynamic array.
#define MAXFILES = 10 ^ 6 /*Maximum number of Notes to search,*/
// Choose length of vector, I'm limited to (int)1.3E6 here but
// (binom(128, 3)<500E3) choose 3)<500E3
// #define VECSIZE (500*1000)
#define VECSIZE (10) // TODO Testing

/* * Global Variables */
int i;

/* * Function Declarations */
float arr_sum(float arr[], int arr_size);
void fill_array(float arr[], int n);
// TODO this (arrays) should use ints until it needs to become a float, it's
// easier to code just for floats at the moment though
void read_file(char *filename, float *count_array);
void norm1_scale(float *source_array, float *target_array);
float euclidean_length(float *source_array);



// TODO exit if two args are not given
void read_query(char *term, float *count_array) {
  printf("The second Argument should be a query:\n");
  int i = 0; /* This will become the length of the Query */
  while (term[i] != '\0') {
    printf("%c", term[i]);
    i++;  
  }
  printf("\n");
}

/* * Main */
int main(int argc, char *argv[]) {
  float doc_vec[VECSIZE];       /* Delcare a Vector for the Document */
  float query_vec[VECSIZE];       /* Delcare a Vector for the query*/
  fill_array(doc_vec, VECSIZE); /* Fill that vector with 0s */
  float doc_vec_norm1[VECSIZE]; /* Declare a Vector for the scaled values */
  // give it some values
  doc_vec[1] = 3;
  doc_vec[3] = 4;
  doc_vec[7] = 0;
  // Scale that vector to 1
  norm1_scale(doc_vec, doc_vec_norm1);
  printf("the first value of the array is %f", doc_vec_norm1[1]);

  // What is the Euclidean length of this vector
  /* norm2_length(doc_vec); */
  printf("\n The euclidean length is: %f\n", euclidean_length(doc_vec));

  read_file(argv[1], doc_vec); 	/* First argument is file */
  read_query(argv[2], query_vec); /* Second argument is query term */

  /* float myvec[VECSIZE]; */
  /* printf("sum is: %f\n\n", arr_sum(doc_vec, VECSIZE)); */
  /* return 0; */
}

/* * Sub-Functions */
void norm1_scale(float *source_array, float *target_array) {
  float sum_array = arr_sum(source_array, VECSIZE);
  printf("\nThe sum of the elements is %f\n", sum_array);
  printf("\nThe sum of the elements is %f", arr_sum(source_array, VECSIZE));
  for (int i = 0; i < VECSIZE; ++i) {
    target_array[i] = source_array[i] / sum_array;
  }
}

float euclidean_length(float *source_array) {
  float SS = 0;
  float sum_array = arr_sum(source_array, VECSIZE);
  printf("\nThe sum of the elements is %f\n", sum_array);
  printf("\nThe sum of the elements is %f", arr_sum(source_array, VECSIZE));
  for (int i = 0; i < VECSIZE; ++i) {
    SS += (source_array[i] * source_array[i]);
  }
  /* printf("\naaaaaa%f", sqrtf(SS)); // NOTE remember gcc -lm */
  return sqrtf(SS);
}

void fill_array(float arr[], int n) {
  int i;
  for (i = 0; i < n; ++i) {
    float x = 0;
    arr[i] = x;
    /* printf("\n%i", i); */
  }
}

float arr_sum(float arr[], int arr_size) {
  float running_sum = 0; /* Running tally */
  int i;                 /* counting */
  for (i = 0; i < arr_size; ++i) {
    if (arr[i] != 0) {
      running_sum += arr[i];
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
  int c; // declare c as int so it can store '\0'
  if (fp == NULL) {
    perror("Error Opening File");
  } else {
    while ((c = fgetc(fp)) != EOF) {
      //      printf("%c", c); 		/* Cat the File */
    }
  }

  count_array[1] = 11;
}
