#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <string.h>




#define L  216 ////(108*2)
#define n_outputfiles 30
#define max_nr_orient 200
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

int CellsGlued[n_outputfiles];
int MCS[n_outputfiles];
int MORE_THAN[n_outputfiles];
int max_size = 0;

double AVG_cells[4];
int DELTA_VEC[4];

// int setParameters(int);
int count_more_than_6();

void create_lines(int);
void read_input(int, int);
int calculations();
int check_xa(int, int);
int check_xm(int, int);

int count_unique_cells();
void output_files(int);

void output_DIST(int);
void output_avg();
double AVG(int);

int main(){


int DELTA;
int k = 0;

  for( DELTA = 4; DELTA < 8; DELTA++){
    create_lines(DELTA);

    int freq=1;
    int i = 0;
    int j = 0;

    int tot;

      while(i <= max_mcs){

       if (i%freq == 0){

         read_input(DELTA,i);
         CellsGlued[j] = calculations();
         MCS[j] = i;
         printf("CellsGlued[j] = %d mcs[j] = %d ",CellsGlued[j], MCS[j]);

         MORE_THAN[j] = count_more_than_6();
         printf(" tot %d\n", MORE_THAN[j]);
         j++;

       }
       if ( i/freq > 10 ) {freq *= 10;}
       else {i++;}



       for(int p = 0; p< max_cells;p++) {
         Glue[p] = 0;
         Check[p] = 0;
       }


     }
     AVG_cells[k] = AVG(DELTA);
     DELTA_VEC[k] = DELTA;
     printf("avg %f delta %d\n", AVG_cells[k], DELTA_VEC[k]);
     k++;

     output_files(DELTA);
     output_DIST(DELTA);
     output_avg();

     for (int i = 0; i <n_outputfiles; i++){
       CellsGlued[i] = 0;
       MCS[i] = 0;
       MORE_THAN[i] =0;
     }
   }



  return 0;
}
void create_lines(int DELTA){
  xa = (int*)malloc(nr_n*sizeof(*xa));
  xm = (int*)malloc(nr_n*sizeof(*xm));
   int dist = L/nr_n;

   int Xa = 0;
   int Xm = 0;

   // printf("%d ",DELTA);

   DELTA = DELTA*6;
   // printf("%d \n",DELTA);
   for (int i = 0; i < nr_n; i++){
     Xa = (i+1)*dist-dist/2;

     xa[i] = Xa - DELTA/2;
     xm[i] = Xa + DELTA/2;

      printf("xa[i] %d xm[i] %d dist %d \n",xa[i],xm[i],dist);
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
  int indexa, indexm,k;

  for(int i = 0; i < nr_n; i++){

    // checking next to xa
    // indexa = (xa[i] + 1)*L;

   //  for(indexa= (xa[i] + 1)*L; indexa < (xa[i] + 2)*L; indexa++){

   for(indexa= (xa[i]+1)*L; indexa < (xa[i]+2)*L; indexa++){

     if (matrix[indexa] != 0){ // there is a cell next to the wall

        if(Check[matrix[indexa]] == 0){ // havent checked this cell-index before

           if (check_xa(matrix[indexa], xa[i]) == 1){ //whole cell is inside
             Glue[matrix[indexa]] = 1;
           }
           else{
             Glue[matrix[indexa]] = 0;
           }
        }

       Check[matrix[indexa]] = 1;

      }

    }
      //checking for xm

     for(indexm= (xm[i]-1)*L; indexm < xm[i]*L; indexm++){

       if (matrix[indexm] != 0){ // there is a cell next to the wall

         if(Check[matrix[indexm]] == 0){ // havent checked this cell-index before


          if (check_xm(matrix[indexm], xm[i]) == 1){ //whole cell is inside
            Glue[matrix[indexm]] = 1;
          }
          else{
            Glue[matrix[indexm]] = 0;
          }
        }

        Check[matrix[indexm]] = 1;

      }

    }

   }
   int nr_unique_cells = count_unique_cells();


    return nr_unique_cells;

}

int check_xa(int label, int x_val){

  for (int i = 0; i <L*L; i++){
    int x = i/L;
    if (matrix[i] == label && x < x_val){
      return 0;
    }
  }
  return 1;
}

int check_xm(int label, int x_val){

  for (int i = 0; i <L*L; i++){
    int x = i/L;
    if (matrix[i] == label && x > x_val){
      return 0;
    }
  }
  return 1;
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


void output_files(int DELTA){

  char write[200];
  FILE  *file;

	sprintf(write,"processed/distribution_DELTA%d", DELTA);

  file = fopen(write, "w");


  for (int j=0; j < n_outputfiles; j++){
    fprintf(file,"%d %d\n",MCS[j] , CellsGlued[j] );
  }
  fclose(file);
}
void output_DIST(int DELTA){
  char write[200];
  FILE  *file;

	sprintf(write,"processed/Orient_DELTA%d", DELTA);

  file = fopen(write, "w");


  for (int j=0; j < n_outputfiles; j++){

    fprintf(file,"%d %d\n", MCS[j], MORE_THAN[j]);
  }
  fclose(file);

}
int count_more_than_6(){
  int tot = 0;
  int cnt = 0;
  for (int i = 0; i<max_cells;i++){

    if (Glue[i]!=0){
      for(int j = 0; j<2; j++){
        for(int k = (xa[j]+1)*L; k < (xa[j]+2)*L; k++){
          if(matrix[k] == i){
            cnt++;
          }
        }
        for(int l= (xm[j]-1)*L; l < xm[j]*L; l++){
          if(matrix[l] == i){
            cnt++;
          }
        }
      }
    }

    if (cnt>=8){
      tot++;
    }
    cnt=0;
    }

    return tot;
}
void output_avg(){

  FILE  *file;
  file = fopen("processed/AVG_all", "w");


  for (int j=0; j < 4; j++){
    fprintf(file,"%d %f\n",DELTA_VEC[j], AVG_cells[j]);
  }
  fclose(file);
}
double AVG(int DELTA){
  double total_cells =0;
  for (int i = 0; i < n_outputfiles; i++){
    total_cells += CellsGlued[i];
  }
  return (double)total_cells/n_outputfiles;
}
