
/* * Includes */
#include <math.h>
#include <stdio.h>
#include <time.h> // for clock_t, clock(), CLOCKS_PER_SEC

/* * Symbolic Constants */
// TODO this should probably be a dynamic array.  TODO How can I know
//      if a character is ASCII, I should Drop non ASCII Characters TODO I
// should consider using Sparse Matrices
#define MAXFILES = 10 ^ 6 /*Maximum number of Notes to search,*/

// Choose length of vector, I'm limited to (int)1.3E6 here if inside a
// function, so it has to be global, static variables tend to be
// faster anyway. (binom(128, 3)<500E3) choose 3)<500E3

#define VECSIZE (2*150*150) // 150^3 is SLOW, 3-tuple 100 sloewr
				// than 2-tuple
// #define VECSIZE (2*128*128) 
			    
/* * Global Variables */
int i;
/* Large arrays > 10^6 must be declared globally or static see : */
/* https://stackoverflow.com/a/43015175 */
float doc_vec[VECSIZE];       /* Delcare a Vector for the Document */
float query_vec[VECSIZE];       /* Delcare a Vector for the query*/

/* Declare vectors to become scaled */
float vec1_scale[VECSIZE];
float vec2_scale[VECSIZE];


/* * Function Declarations */
float arr_sum(float arr[], int arr_size);
void fill_array(float arr[], int n);
// TODO this (arrays) should use ints until it needs to become a float, it's
// easier to code just for floats at the moment though
void read_file(char *filename, float *count_array);
void norm1_scale(float *source_array, float *target_array);
float euclidean_length(float *source_array, int N);
void read_query(char *term, float *count_array);
float dot(float *vec1, float *vec2, int N);
float dot(float *u, float *v, int N);
float cos_dist(float *vec1, float*vec2, int N);
float similarity(float *vec1, float *vec2, int N);



/* * Main */
int main(int argc, char *argv[]) {
  /* ** Create Arrays */
  fill_array(doc_vec, VECSIZE); /* Fill that vector with 0s */
  fill_array(query_vec, VECSIZE);     /* Fill that vector with 0s */


  /* ** Fill Arrays with Occurrence of Strings */
  read_file(argv[1], doc_vec); 	/* First argument is file */
  read_query(argv[2], query_vec); /* Second argument is query term */

  /* ** Calculate the similarity */
  float sim_score = similarity(doc_vec, query_vec, VECSIZE);
  printf("%f", sim_score);

  /* float myvec[VECSIZE]; */
  /* printf("sum is: %f\n\n", arr_sum(doc_vec, VECSIZE)); */
  /* return 0; */
}

/* * Sub-Functions */
/* ** Read Arguments */
/* *** Read in First Argument (File Contents) */
void read_file(char *filename, float *count_array) {
  int i = 0;
  while (filename[i] != '\0') {
    i++;
  }

  FILE *fp = fopen(filename, "r");
  int c; // declare c as int so it can store '\0'
  if (fp == NULL) {
    perror("Error Opening File");
  } else {
    int char_1 = 32; // NOTE Treat first char as space
    int char_2 = 32;
    while ((c = fgetc(fp)) != EOF) {
      // Replace tabs and whitespaces
      if (c == 10 || c==13 || c==78 || c==9) {
      c = 32;
      }
      char_1 = char_2;
      char_2 = c;
      /* printf("\n%c", (char_1*char_2));  /\* Cat the File *\/ */
      int index=(char_1*char_2);
      count_array[index] += 1;
    }
  }
}
/* *** Read Second Argument (search Query) */
void read_query(char *term, float *count_array) {
  int i = 0; /* This will become the length of the Query */
  int char_1 = 32; // NOTE Treat first char as space
  int char_2 = 32;
  int c; // declare c as int so it can store '\0'
  while ((c = term[i]) != '\0') {
    // Replace tabs and whitespaces
    if (c == 10 || c==13 || c==78 || c==9) {
      c = 32;
    }
    char_1 = char_2;
    char_2 = c;
    int index = (char_1*char_2);
    count_array[index] += 1;
    i++;  // TODO why isn't it getting the last one.
  }
  // Files have a trailing LineFeed (10) strings don't so make
  // sure to count one on the string for accuracy.
  char_1 = char_2;
  char_2 = 32; // should be 10 LF, but I swapped LF for SPC above
  int index = char_1*char_2;
  count_array[index] += 1;

}

/* ** Cosine Similarity */

float similarity(float *u, float *v, int N) {
  float dot_val = 0;
  float u_dist2 = 0;
  float v_dist2 = 0;
  for (i = 0; i < N; ++i) {
    float u_val = u[i];
    float v_val = v[i];
    dot_val += u_val * v_val;
    u_dist2 += u_val*u_val;
    v_dist2 += v_val*v_val;
  }
  return dot_val/(sqrt(u_dist2 * v_dist2));
}

/* ** Scale to 1 */
void norm1_scale(float *source_array, float *target_array) {
  float sum_array = arr_sum(source_array, VECSIZE);
  for (int i = 0; i < VECSIZE; ++i) {
    target_array[i] = source_array[i] / sum_array;
  }
}
/* ** Euclidean Length (Mod||) */
/* TODO should take a parameter for vector length */
float euclidean_length(float *source_array, int N) { 
  float SS = 0;
  for (int i = 0; i < N; ++i) {
    SS += (source_array[i] * source_array[i]);    }
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

