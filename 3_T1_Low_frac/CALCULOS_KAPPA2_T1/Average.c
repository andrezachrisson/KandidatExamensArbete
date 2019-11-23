#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <string.h>


#define n_outputfiles 30
double AVG[n_outputfiles][2];

double** read_input(int);
void output_files();

int main(){
  double **tmp;


  int delta = 4;
  for (int delta = 4; delta < 8; delta++){
    tmp = read_input(delta);

    for(int i = 0; i <n_outputfiles; i++){
      for(int j = 0; j < 2; j++){
        AVG[i][j]+=tmp[i][j];
      }
    }


  }
  for(int i = 0; i < n_outputfiles; i++){
    for(int j = 0; j < 2; j++){
      if(j==0){
        AVG[i][j] /= 4;
      }
      else{
        AVG[i][j] /=3;
      }
    }
  }


  printf("tmp :\n");
  for(int i = 0; i<n_outputfiles; i++){
    for(int j = 0; j < 2; j++){
      printf("%lf",AVG[i][j]);
    }
    printf("\n");
  }
  output_files();

return 0;
}






double** read_input(int delta){
  double** input =malloc(n_outputfiles*sizeof(double*));
  for (int i = 0; i < n_outputfiles; i++){
    input[i]=malloc(2*sizeof(double));
  }

  char read[200];
  sprintf(read,"processed/distribution_DELTA%d", delta);

  FILE *fp;
  fp = fopen(read, "r");

  if(fp==NULL){
    printf("file could not be opened");
    return input;
  }


  for (int i = 0;i < n_outputfiles; i++){

    for (int j = 0; j < 2; j++){

      if (!fscanf(fp, " %lf\n", &input[i][j]))
           break;
           // printf("%lf\n",input[i][j]);
    }
  }
  fclose(fp);


  return input;
}
void output_files(){

  char write[200];
  FILE  *file;

	sprintf(write,"processed/distribution_total");

  file = fopen(write, "w");


  for (int j=0; j < n_outputfiles; j++){
    fprintf(file,"%f %f\n",AVG[j][0] , AVG[j][1] );
  }
  fclose(file);
}
