
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
#define VECSIZE (3) // TODO Testing

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
void read_query(char *term, float *count_array);



// TODO exit if two args are not given

/* * Main */
int main(int argc, char *argv[]) {
  /* ** Create Arrays */
  float doc_vec[VECSIZE];       /* Delcare a Vector for the Document */
  fill_array(doc_vec, VECSIZE); /* Fill that vector with 0s */
  // Declare a Vector for the scaled values
  float doc_vec_norm1[VECSIZE];  // Does not require Filling

  float query_vec[VECSIZE];       /* Delcare a Vector for the query*/
  fill_array(query_vec, VECSIZE); /* Fill that vector with 0s */
  // Declare a Vector for the scaled values
  float query_vec_norm1[VECSIZE];  // Does not require Filling

  // give it some values
  doc_vec[0] = 3;
  doc_vec[1] = 6;
  doc_vec[2] = 9;

  query_vec[0] = 3;
  query_vec[1] = 6;
  query_vec[2] = 9;
  // Scale that vector to 1
  norm1_scale(doc_vec, doc_vec_norm1);

  // What is the Euclidean length of this vector
  /* norm2_length(doc_vec); */

  read_file(argv[1], doc_vec); 	/* First argument is file */
  read_query(argv[2], query_vec); /* Second argument is query term */

  /* float myvec[VECSIZE]; */
  /* printf("sum is: %f\n\n", arr_sum(doc_vec, VECSIZE)); */
  /* return 0; */
}

/* * Sub-Functions */

/* ** Read in First Argument (File Contents)  */
void read_file(char *filename, float *count_array) {
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
/* ** Read Second Argument (search Query) */
void read_query(char *term, float *count_array) {
  int i = 0; /* This will become the length of the Query */
  while (term[i] != '\0') {
    printf("%c", term[i]);
    i++;  
  }
  printf("\n");
}

/* ** Scale to 1 */
void norm1_scale(float *source_array, float *target_array) {
  float sum_array = arr_sum(source_array, VECSIZE);
  for (int i = 0; i < VECSIZE; ++i) {
    target_array[i] = source_array[i] / sum_array;
  }
}
/* ** Euclidean Length (Mod||) */
float euclidean_length(float *source_array) {
  float SS = 0;
  for (int i = 0; i < VECSIZE; ++i) {
    SS += (source_array[i] * source_array[i]);
  }
  return sqrtf(SS);
}

/* ** Fill array with 0 */
void fill_array(float arr[], int n) {
  int i;
  for (i = 0; i < n; ++i) {
    float x = 0;
    arr[i] = x;
  }
}

/* ** Sum array */
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

