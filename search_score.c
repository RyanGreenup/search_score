#include <stdio.h>
#include <time.h>       // for clock_t, clock(), CLOCKS_PER_SEC

// TODO this should probably be a dynamic array.
#define MAXFILES                                                               \
  = 10 ^ 6 /* Manimum number of Notes to search, 10^6<1GB memory */
#define VECSIZE (9999+1)

/* Variables */
int i;
float x;

/* Function Declarations */
float arr_sum(float arr[], int arr_size);
void fill_array(float arr[], int n);

/* Main */

int main() {
  float myvec[VECSIZE];
  fill_array(myvec, VECSIZE);
  printf("sum is: %f\n\n", arr_sum(myvec, VECSIZE));
  return 0;
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

