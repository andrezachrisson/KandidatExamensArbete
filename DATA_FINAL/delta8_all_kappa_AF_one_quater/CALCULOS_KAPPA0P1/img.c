#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <string.h>




#define L  216 ////(108*2)
#define n_outputfiles 200
#define max_nr_orient 40
#define max_cells 2600
#define max_mcs 900
#define nr_n 2

int *xa;
int *xm;
double alpha;
double kappa;
int N_INITIAL;
int N_T;
int *matrix;

int Glue[max_cells];
int Check[max_cells];
int Orient[max_cells];
int delta;
int CellsGlued[n_outputfiles];
int MCS[n_outputfiles];
int max_size = 0;
int N_orient[max_nr_orient];

// int setParameters(int);
void create_lines();
void read_input(int, int);
int calculations();
int check_xa(int, int);
int check_xm(int, int);
int count_glued_xm(int, int);
int count_glued_xa(int, int);
int count_unique_cells();
void output_files(int);
int calc_dist();
void output_DIST(int, int);


int main(){


  int nr_of_cells_glued;

  create_lines();

  for(int DELTA = 8; DELTA < 9; DELTA++){

    int freq=1;
    int i = 0;
    int j = 0;
    while(i <= max_mcs){

      if (i%freq == 0){

      read_input(DELTA,i);

      CellsGlued[j] = calculations();
      MCS[j] = i;

       j++;
     }
     if ( i/freq > 10 ) {
         freq *= 10;}
       else{
         i++;
       }
     }

     int tot = calc_dist();
     output_DIST(DELTA, tot);
     for (int k = 0; k < max_nr_orient; k++){
       N_orient[k]=0;
     }

     output_files(DELTA);
     for (int i = 0; i <n_outputfiles; i++){
       CellsGlued[i] = 0;
       MCS[i] = 0;
     }

     for (int i = 0; i < max_cells; i++){
       Glue[i] = 0;
       Check[i] = 0;
       Orient[i] = 0;
     }
   }



  return 0;
}
// int setParameters(int DELTA){
//
//   char read[12];
//   sprintf(read,"DELTA%d/INPUT/inputparam.txt", DELTA);
//
//   FILE *fp;
//   fp = fopen(read, "r");
//   while(fscanf(fp ,"%d %lf %lf %lf %d %d",&delta,&TEMPERATURA,&alpha,&kappa,&N_INITIAL,&N_T)==EOF){}
//   fclose(fp);
//
//                 // (L - delta)/(dist + delta) + 1;
//
//
//     return DELTA;
// }
void create_lines(){
  xa = (int*)malloc(nr_n*sizeof(*xa));
  xm = (int*)malloc(nr_n*sizeof(*xm));
  int dist = L/nr_n;

  int Xa = 0;
  int Xm = 0;
  int i;

  for (i = 0; i < nr_n; i++){
    Xa = (i+1)*dist-dist/2;
    xa[i] = Xa - delta/2;
    xm[i] = Xa + delta/2;

     // printf("%d %d %d \n",xa[i],xm[i],dist);
  }

}
void read_input(int DELTA, int N_MCS){
  char read[200];
  sprintf(read,"DELTA%d/OUTPUT/foto_final_fila%d.txt", DELTA, N_MCS);

  int n= L*L;
  matrix = (int*)malloc(n*sizeof(*matrix));

  FILE *fp;
  fp = fopen(read, "r");

  for(int i = 0;i < L*L; i++){
    fscanf(fp ,"%d",&matrix[i]);

  }
  fclose(fp);
}

int calculations(){
  int index;

  for(int i = 0; i < nr_n; i++){

    // checking next to xa
    index = (xa[i]+1)*L;

    for(index; index < (xa[i]+2)*L; index++){

      if(Check[matrix[index]] == 0){ // havent checked this cell-index before

        if (matrix[index] != 0){ // there is a cell next to the wall

          if (check_xa(matrix[index], xa[i]) == 1){ //whole cell is inside

            Glue[matrix[index]] = 1;
            Orient[matrix[index]] = count_glued_xa(matrix[index], (xa[i] + 1)*L);

          }
          else{
            Glue[matrix[index]] = 0;
          }
        }

        Check[matrix[index]] = 1;

      }
    }

      //checking for xm
      index = (xm[i] -1)*L;

      for(index; index > (xm[i]- 2)*L; index --){

        if(Check[matrix[index]] == 0){ // havent checked this cell-index before

          if (matrix[index] != 0){ // there is a cell next to the wall

            if (check_xm(matrix[index], xm[i]) == 1){ //whole cell is inside

              Glue[matrix[index]] = 1;
              Orient[matrix[index]] = count_glued_xm(matrix[index], (xm[i] -1)*L);

            }
            else{
              Glue[matrix[index]] = 0;
            }
          }

          Check[matrix[index]] = 1;

        }
      }
    }
    return count_unique_cells();

}
int check_xa(int label, int index_xa){

  for (int i = 0; i <L*L; i++){
    int x = i/L;
    if (matrix[i] == label && x <= index_xa){
      return 0;
    }
  }
  return 1;
}
int check_xm(int label, int index_xm){

  for (int i = 0; i <L*L; i++){
    int x = i/L;
    if (matrix[i] == label && x >= index_xm){
      return 0;
    }
  }
  return 1;
}
int count_glued_xm(int label, int index){
  int i = ((index/L) -1)*L;
  int n_glued = 0;
  for (index; index > i; index--){
    if (matrix[index] == label){
      n_glued ++;
    }
  }
  return n_glued;
}
int count_glued_xa(int label, int index){
  int i = ((index/L) +1)*L;
  int n_glued = 0;
  for (index; index < i; index++){
    if (matrix[index] == label){
      n_glued ++;
    }
  }
  return n_glued;
}
int count_unique_cells(){
  int nr_unique = 0;
  for (int i = 0; i < max_cells; i++){
    if(Glue[i] != 0){
      nr_unique++;
    }
  }
  return nr_unique;
}
int calc_dist(){
  max_size = 0;
  int tot =0;
  for (int i = 0; i < max_cells; i++){
    if(Orient[i]>0){

      N_orient[Orient[i]]++;
      tot ++;

      if (Orient[i]>max_size){
        max_size =Orient[i];
      }
    }
  }
  return tot;
}

void output_files(int DELTA){

  char write[100];
  FILE  *file;

	sprintf(write,"processed/distribution_DELTA%d", DELTA);

  file = fopen(write, "w");


  for (int j=0; j < n_outputfiles; j++){
    fprintf(file,"%d %d\n",MCS[j], CellsGlued[j] );
  }
  fclose(file);
}
void output_DIST(int DELTA, int tot){
  char write[100];
  FILE  *file;

	sprintf(write,"processed/Orient_DELTA%d", DELTA);

  file = fopen(write, "w");


  for (int j=1; j < max_nr_orient; j++){

    fprintf(file,"%d %f\n", j, (double)N_orient[j] / tot );
  }
  fclose(file);

}
