#include <math.h>
#include <stdio.h>
#include <stdlib.h> // rand
#include <time.h>    // time


#define NR 3
#define N 3 // DTM, N is num docs
#define NC 4

void printvec(float *array, int l) {

  for (int k = 0; k < l; k++) {
    printf(" %f ", array[k]);
    printf("\n");
  }
}

void colSum(float source[3][4], float *destination) {
  float running_sum = 0;

  for (int j = 0; j < NC; j++) {
    running_sum = 0;
    for (int i = 0; i < NR; i++) {
      running_sum += source[i][j];
    }
    destination[j] = running_sum;
  }
}

/* This function will take a DTM and a destination vector as
   arguments, the destination vector will be filled with values
   f_t. the values f_t represent the number of documents in which
   tupple t occurs more than the average. If the distribution is very
   flat, f_t should be about 0.5*N, but if the term occurs only in a
   few documents it should be much smaller, taking the reciprocal of
   this means that the term is considered very relevant. */
void num_above_average(float DTM[3][4], float *destination) {
  float running_sum = 0;
  int i = 0; // rows or documents, smallish
  int j = 0; // columns or terms, Very large 

  for (j = 0; j < NC; j++) {
    running_sum = 0;
    // Calculate the average of the column
    for (i = 0; i < NR; i++) {
      running_sum += DTM[i][j];
    }
    float average = running_sum/NR;
    // Count the number above the average
    int ft = 0;
    for (i = 0; i < NR; i++) {
      if (DTM[i][j] > average) {
	ft++;
      }
    }
    destination[j] = ft;
  }
}

void rowSum(float source[3][4], float *destination) {
  float running_sum = 0;

  for (int i = 0; i < NR; i++) {
    running_sum = 0;
    for (int j = 0; j < NC; j++) {
      running_sum += source[i][j];
    }
    destination[i] = running_sum;
  }
}

void DTM_to_TF(float DTM[NR][NC], float TF[NR][NC]) {
  for (int i = 0; i < NR; i++) {
    for (int j = 0; j < NC; j++) {
      TF[i][j] = logf(DTM[i][j] + 1);
    }
  }
}

void DTM_to_IDF(float DTM[NR][NC], float IDF[NC]) {
  float colsums[NC];
  colSum(DTM, colsums);
  float ft[NC];
  num_above_average(DTM, ft);
			

  for (int j = 0; j < NC; j++) {
    IDF[j] = logf(N / ft[j]);
  }
}

void printmat(float mat[NR][NC]) {
  for (int i = 0; i < NR; ++i) {
    for (int j = 0; j < NC; ++j) {
      printf(" %f ", mat[i][j]);
    }
    printf("\n");
  }
}

void DTM_to_TFIDF(float DTM[NR][NC], float TFIDF[NR][NC]) {
  float TF[NR][NC];
  float IDF[NC];

  DTM_to_TF(DTM, TF);
  DTM_to_IDF(DTM, IDF);

  printf("---\nThe IDF is:\n");
  printvec(IDF, NC);
  printf("\n---\nThe TF is:\n");
  printmat(TF);

  for (int i = 0; i < NR; i++) {
    for (int j = 0; j < NC; j++) {
      float tf_val = TF[i][j];
      float idf_val = IDF[j];
      TFIDF[i][j] = tf_val * idf_val;
    }
  }

  printf("\n---\nThe TFIDF is:\n");
  printmat(TFIDF);

}

void DTM_raw_to_freq(float DTM[NR][NC]) {
  float RS[NR];
  rowSum(DTM, RS);

  for (int i = 0; i < NR; ++i) {
    for (int j = 0; j < NC; ++j) {
      DTM[i][j] = DTM[i][j]/RS[i];
    }
  }
}

int main() {

  /* Delcara array */
  float my_array[3][4];

 /* Intializ random number generator */
   time_t t;
   srand((unsigned) time(&t));

  /* Assign Array */
  for (int i = 0; i < NR; i++) {
    for (int j = 0; j < NC; j++) {
      /* my_array[i][j] = ((i + 1) * (j + 1) % 13); */
      my_array[i][j] = (rand() % 24);
    }
  }

  printf("\nRandom Matrix:\n");
  printf("\n---\n");
  printmat(my_array);

  /* Implement TF-IDF */
  float TFIDF[NR][NC];
  DTM_to_TFIDF(my_array, TFIDF);

  /* Return Success */
  return 0;
}
