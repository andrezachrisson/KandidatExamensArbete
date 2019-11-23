#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <string.h>




#define L  216 ////(108*2)
#define n_outputfiles 30
#define max_nr_orient 20
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
int CellsGlued[n_outputfiles];
int MCS[n_outputfiles];
int max_size = 0;
int N_orient[max_nr_orient];

// int setParameters(int);
void create_lines(int);
void read_input(int, int);
int calculations();
int check_xa(int, int);
int check_xm(int, int);

int count_glued(int, int);
int count_unique_cells();
void output_files(int);
int calc_dist();
void output_DIST(int, int);


int main(){


int DELTA;

  for( DELTA = 4; DELTA <= 7; DELTA++){
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
      // printf("CellsGlued[j] = %d mcs[j] = %d \n",CellsGlued[j], MCS[j]);
         j++;
       }
       if ( i/freq > 10 ) freq *= 10;
       else i++;

       for(int p = 0; p< max_cells;p++) {


            Check[p] = 0;
       }


     }
     tot = calc_dist(); // calculate total cell index oriented
     output_DIST(DELTA, tot);

      //output total cell oriented
     output_files(DELTA);
     for(int i = 0; i < max_cells;i++){
       Glue[i] = 0;
       Orient[i] = 0;
     }
     for (int k = 0; k < max_nr_orient; k++){
       N_orient[k]=0;
     }


     for (int i = 0; i <n_outputfiles; i++){
       CellsGlued[i] = 0;
       MCS[i] = 0;
     }
     // for(int i = (xa[1])*L; i < (xa[1]+2)*L; i++){
     //
     //   printf("%d ", matrix[i]);
     // }

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
             Orient[matrix[indexa]] = count_glued(matrix[indexa], (xa[i] + 1)*L);

           }
           else{
             Glue[matrix[indexa]] = 0;
           }
        }

       Check[matrix[indexa]] = 1;

      }

    }
      //checking for xm
      // indexm = (xm[i])*L;

      // for(indexm = (xm[i])*L; indexm > (xm[i]- 2)*L; indexm --){
     for(indexm= (xm[i]-1)*L; indexm < xm[i]*L; indexm++){

       if (matrix[indexm] != 0){ // there is a cell next to the wall

         if(Check[matrix[indexm]] == 0){ // havent checked this cell-index before


          if (check_xm(matrix[indexm], xm[i]) == 1){ //whole cell is inside
            Glue[matrix[indexm]] = 1;
            Orient[matrix[indexm]] = count_glued(matrix[indexm], (xm[i] - 1)*L);

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
// int count_glued_xm(int label, int index){
//   int x = ((index/L) +1)*L;
//   int n_glued = 0;
//   for (index; index < x; index++){
//     if (matrix[index] == label){
//       n_glued ++;
//     }
//   }
//   return n_glued;
// }

int count_glued(int label, int index){
  int n_glued = 0;

  for (int i = index; i < (index+L); i++){
    if (matrix[i] == label){
      n_glued ++;
    }
  }
// printf("%d\n", n_glued);
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
        max_size = Orient[i];
      }
    }
  }
  return tot;
}

void output_files(int DELTA){

  char write[200];
  FILE  *file;

	sprintf(write,"processed/distribution_DELTA%d", DELTA);

  file = fopen(write, "w");


  for (int j=0; j < n_outputfiles; j++){
    fprintf(file,"%d %d\n",MCS[j], CellsGlued[j] );
  }
  fclose(file);
}
void output_DIST(int DELTA, int tot){
  char write[200];
  FILE  *file;

	sprintf(write,"processed/Orient_DELTA%d", DELTA);

  file = fopen(write, "w");


  for (int j=1; j < max_nr_orient; j++){

    fprintf(file,"%d %f\n", j, (double)N_orient[j]/tot);
  }
  fclose(file);

}