#include <math.h>
#include <stdio.h>

#define NR 3
#define N 3 // DTM, N is num docs
#define NC 4

void printvec(float *array, int l) {

  for (; l >= 0; l--) {
    printf(" %f ", array[l]);
    printf("\n");
  }
}

void colSum(float source[3][4], float *destination) {
  float running_sum = 0;

  for (int j = 0; j < NC; j++) {
    running_sum = 0;
    for (int i = 0; i < NC; i++) {
      running_sum += source[i][j];
    }
    destination[j] = running_sum;
  }
}


void rowSum(float source[3][4], float *destination) {
  float running_sum = 0;

  for (int i = 0; i < NC; i++) {
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
  float *ft = colsums;

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

  printvec(IDF, NC);
  printf("---\n---\n");
  printmat(TF);

  for (int i = 0; i < NR; i++) {
    for (int j = 0; j < NC; j++) {
      float tf_val = TF[i][j];
      float idf_val = IDF[j];
      TFIDF[i][j] = tf_val * idf_val;
    }
  }
}

DTM_raw_to_freq(float DTM[NR][NC]) {
  float rowsums[NC];
  rowSum(DTM, rowsums);

  for (int i = 0; i < NR; ++i) {
    for (int j = 0; j < NC; ++j) {
      DTM[i][j] = DTM[i][j];
    }
  }
}

int main() {

  /* Delcara array */
  float my_array[3][4];

  /* Assign Array */
  for (int i = 0; i < NR; i++) {
    for (int j = 0; j < NC; j++) {
      my_array[i][j] = ((i + 1) * (j + 1) % 13);
    }
  }

  /* DTM_raw_to_freq(my_array); */
  printmat(my_array);

  /* Implement TF-TF */
  float TFIDF[NR][NC];

  DTM_to_TFIDF(my_array, TFIDF);

  printf("---\n---\n");
  printmat(TFIDF);

  /* Return Success */
  return 0;
}
