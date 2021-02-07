// TODO measure how many triples might occur in a document and
//      write a version of this that works on triples by using modulo
//      of the array size to choose the index to increment.
// TODO did I scale the lists to 1? Do i need to?... Yes.
// TODO Should loop over files to avoid shell
// TODO Should test for arguments
// TODO should print help
// TODO Would TF-IDF weighting help?
// TODO this is still case sensitive
// TODO I should really limit the scope of consideration to what I
// would expect to see in the query, so a-z0-9 with spaces=.=, =,=,
// that would reduce the need to have such a large NC.
// TODO If I'm very careful, could I turn the DTM into a TFIDF in place
       // to reduce the amount of memory used?
       // What if I extracted the IDF as a vector and then turned the DTM into the TF.
       // I could then take that TF, multiply through the IDF and then that would be
       // NOTE This is absolutely necessary
// TODO make sure that the DTM TFIDF stuff is using floats to reduce memory usage
// the TFIDF
/* * Includes */
// For String Comparison
#include <ctype.h> // tolower()
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // for clock_t, clock(), CLOCKS_PER_SEC
// For directory search
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

/* * Symbolic Constants */
// TODO this should probably be a dynamic array.  TODO How can I know
//      if a character is ASCII, I should Drop non ASCII Characters TODO I
// should consider using Sparse Matrices

// Choose length of vector, I'm limited to (int)1.3E6 here if inside a
// function, so it has to be global, static variables tend to be
// faster anyway. (binom(128, 3)<500E3) choose 3)<500E3

#define VECSIZE                                                                \
  (30 * 10) // 150^3 is SLOW, 3-tuple 100 sloewr
              // than 2-tuple
// #define VECSIZE (2*128*128)
#define NR 10 * 1000 // The number of Columns of the DTM, i.e. max no. of files
#define NC                                                                     \
  VECSIZE // The number of columns of DTM, i.e. each different
          // occuring tupple, this is limit this to a value
          // that is as big as would be expected for
          // performance concerns, in the event that it is
          // exceeded the pattern loops over and increments
          // some other tupple.

/* * Global Variables */
int i;
/* Large arrays > 10^6 must be declared globally or static see : */
/* https://stackoverflow.com/a/43015175 */
float doc_vec[VECSIZE];     /* Delcare a Vector for the Document */
float query_vec[VECSIZE];   /* Delcare a Vector for the query*/
char *file_list[10 * 1000]; // 10k files up to 4096 in length
int fc; // TODO the file count should be local to the function recursing through
        // dirs. Hmm, this doesn't look easy because of the recursion.
int tc; // The largest index value used to store a tupple, so the
        // widest column used in the DTM

/* ** Create the DTM */
// This MUST be allocated outside main (or as static) because it is
// too large for stack allocation
float DTM[NR + 1][NC]; // Add an extra row for the query, make 0 the query
float TFIDF[NR + 1][NC];
float TF[NR][NC];
float IDF[NC];

/* Declare vectors to become scaled */
float doc_vec_scaled[VECSIZE];
float query_vec_scaled[VECSIZE];

/* * Function Declarations */
float arr_sum(float arr[], int arr_size);
void fill_array(float arr[], int n);
// TODO this (arrays) should use ints until it needs to become a float, it's
// easier to code just for floats at the moment though
void read_file(char *filename, float DTM[NR][NC], int row);
void norm1_scale(float *source_array, float *target_array);
float euclidean_length(float *source_array, int N);
void read_query(char *term, float DTM[NR][NC]);
float dot(float *vec1, float *vec2, int N);
float dot(float *u, float *v, int N);
float cos_dist(float *vec1, float *vec2, int N);
float similarity(float *vec1, float *vec2, int N);
void listFilesRecursively(char *basePath, char *extensions[],
                          char *query_string);
void print_if_ext(char *filename, char *extensions[], char *query_string);
unsigned int cantor_pairing(int a, int b);
void print(char *string);
void DTM_to_TFIDF(float DTM[NR][NC], float TFIDF[NR][NC]);
void DTM_to_TF(float DTM[NR][NC], float TF[NR][NC]);
void DTM_to_IDF(float DTM[NR][NC], float IDF[NC]);
void colSum(float source[NR][NC], float *destination);
void num_above_average(float DTM[NR][NC], float *destination);

/* * Main */
int main(int argc, char *argv[]) {

  char *extensions[3];
  extensions[0] = ".md";
  extensions[1] = ".org";
  extensions[2] = ".txt";

  char *query_string = argv[2];
  listFilesRecursively(argv[1], extensions, query_string);
  if ((fc + 1) >= NR) {
    printf("More Files than currently allowed, to increase"
           "this limit modify the NR value around the Top of the source");
    return 1;
  } else {
    printf("\n\n%i, different files detected\n", fc);
  }

  /* ** Fill the DTM */
  /* *** Zero the DTM */ // TODO this should be done as necessary, adds 1 ms
                         /* *** Add the Query to row 0 of DTM */
  read_query(query_string, DTM); /* Second argument is query term */

  /* *** Add the Files to the DTM */
  for (int i = 0; i < fc; i++) {
    /* **** Fill Arrays with Occurrence of Strings */
    read_file(file_list[i], DTM, i); /* First argument is file */
  }

  // Create the DTM
  DTM_to_TFIDF(DTM, TFIDF);

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      printf("%f\t", TFIDF[i][j]);
    }
    printf("\n");
  }

  /* /\* *** Scale the Arrays to 1                  *\/ */
  /* norm1_scale(doc_vec, doc_vec_scaled); */
  /* norm1_scale(query_vec, query_vec_scaled); */

  /* /\* *** Calculate the similarity *\/ */
  /* float sim_score = similarity(doc_vec_scaled, query_vec_scaled, VECSIZE); */
  /* for (; fc >= 0; --fc) { */
  /*   printf("%f\t%s\n", sim_score, file_list[fc]); */
  /* } */

  return 0;
}

/* * Sub-Functions */
/* ** Read Arguments */
/* *** Read in First Argument (File Contents) */
void read_file(char *filename, float DTM[NR][NC], int row) {
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
    int char_3 = 32;
    // Zero the DTM
    for (int j = 0; j < NC; ++j) {
      DTM[row][j] = 0;
    }
    // Go over the characters
    while ((c = tolower(fgetc(fp))) != EOF) {
      // Replace tabs and whitespaces
      if (c == 10 || c == 13 || c == 78 || c == 9) {
        /* c = 32; */
        continue;
      }
      char_1 = char_2;
      char_2 = char_3;
      char_3 = c;
      /* printf("\n%c", (char_1*char_2*char_3));  /\* Cat the File *\/ */
      int index =
          (cantor_pairing(cantor_pairing(char_1, char_2), char_3) % VECSIZE);
      DTM[row][index] += 1;
      if (index > tc) {
        tc = index;
      }
    }
  }
  fclose(fp);
}
/* *** Read Second Argument (search Query) */
void read_query(char *term, float DTM[NR][NC]) {
  int rownum = 0;  // the row of the DTM to put the query into
  int i = 0;       /* This will become the length of the Query */
  int char_1 = 32; // NOTE Treat first char as space
  int char_2 = 32;
  int char_3 = 32;
  int c; // declare c as int so it can store '\0'
  for (int j = 0; j < NC; j++) {
    DTM[rownum][j] = 0;
  }
  while ((c = term[i]) != '\0') {
    // Replace tabs and whitespaces
    if (c == 10 || c == 13 || c == 78 || c == 9) {
      /* c = 32; */
      continue;
    }
    char_1 = char_2;
    char_2 = char_3;
    char_3 = c;
    int index =
        (cantor_pairing(cantor_pairing(char_1, char_2), char_3) % VECSIZE);
    DTM[rownum][index] += 1;
    i++; // TODO why isn't it getting the last one.
  }
  // Files have a trailing LineFeed (10) strings don't so make
  // sure to count one on the string for accuracy.
  char_1 = char_2;
  char_2 = char_3;
  char_3 = 32; // should be 10 LF, but I swapped LF for SPC above
  int index =
      (cantor_pairing(cantor_pairing(char_1, char_2), char_3) % VECSIZE);
  DTM[rownum][index] += 1;
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
    u_dist2 += u_val * u_val;
    v_dist2 += v_val * v_val;
  }
  return dot_val / (sqrt(u_dist2 * v_dist2));
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

/* ** Cantor Pairing Function */
unsigned int cantor_pairing(int a, int b) {
  return b + (a + b) * (a + b + 1) / 2;
}

/* ** List Files in Directories */
/* *** Print if Extension match */
/* *** Check Extension */
void print_if_ext(char *filename, char *extensions[], char *query_string) {

  for (int i = 0; i < 3; ++i) {
    char *ptr = strstr(filename, extensions[i]);
    if (ptr != NULL) {
      file_list[fc] = (char *)malloc(strlen(filename) + 1);
      /* file_list[fc] = filename; */
      strncpy(file_list[fc], filename,
              strlen(filename) +
                  1); // this is a saver version of that assignment, the +1 is
                      // for trailing \0, strncpy is safer than strcpy because
                      // it takes length arg.
      // see https://stackoverflow.com/a/41653464

      fc++; // Increment the file count
    }
  }
}

/* *** Recursive List */
/**
 * Lists all files and sub-directories recursively
 * considering path as base path.
 *  https://codeforwin.org/2018/03/c-program-to-list-all-files-in-a-directory-recursively.html
 */
void listFilesRecursively(char *basePath, char *extensions[],
                          char *query_string) {
  char path[1000];
  struct dirent *dp;
  DIR *dir = opendir(basePath);

  // Unable to open directory stream
  if (!dir)
    return;

  while ((dp = readdir(dir)) != NULL) {
    if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {

      // Construct new path from our base path
      strcpy(path, basePath);
      strcat(path, "/");
      strcat(path, dp->d_name);

      // Print the realpath file
      print_if_ext(path, extensions, query_string);

      // Recurse into the directory
      listFilesRecursively(path, extensions, query_string);
    }
  }

  closedir(dir);
}
/* ** DTM */
/* *** DTM to IDF */
void DTM_to_TFIDF(float DTM[NR][NC], float TFIDF[NR][NC]) {
  DTM_to_TF(DTM, TF);
  DTM_to_IDF(DTM, IDF);

  for (int i = 0; i < NR; i++) {
    for (int j = 0; j < NC; j++) {
      float tf_val = TF[i][j];
      float idf_val = IDF[j];
      TFIDF[i][j] = (tf_val * idf_val);
    }
    printf("\n");
  }
}

/* **** DTM To TF */
void DTM_to_TF(float DTM[NR][NC], float TF[NR][NC]) {
  for (int i = 0; i < NR; i++) {
    for (int j = 0; j < NC; j++) {
      TF[i][j] = logf(DTM[i][j] + 1);
    }
  }
}

/* **** DTM to IDF */

void DTM_to_IDF(float DTM[NR][NC], float IDF[NC]) {
  float colsums[NC];
  colSum(DTM, colsums);
  float ft[NC];
  num_above_average(DTM, ft);

  for (int j = 0; j < NC; j++) {
    IDF[j] = (fc / ft[j]);
  }
}

/* **** Helpers */

void colSum(float source[NR][NC], float *destination) {
  float running_sum = 0;

  for (int j = 0; j < NC; j++) {
    running_sum = 0;
    for (int i = 0; i < NR; i++) {
      running_sum += source[i][j];
    }
    destination[j] = running_sum;
  }
}

void num_above_average(float DTM[NR][NC], float *destination) {
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
    // Nope for now do the number not zero
    int ft = 0;
    for (i = 0; i < NR; i++) {
      /* if (DTM[i][j] > average) { */
      if (DTM[i][j] > 0) {
	ft++;
      }
    }
    destination[j] = ft;
  }
}
