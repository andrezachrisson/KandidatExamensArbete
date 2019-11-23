#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <string.h>




#define L  216 ////(108*2)


double TEMPERATURA;
int delta;
int dist;
int nr_n;
int *xa;
int *xm;
double alpha;
double kappa;
int N_INITIAL;
int N_T;
int *matrix;

int Glue[2600];
int Check[2600];
int Orient[2600];

void setParameters(int);
void create_lines();
void read_input(int, int);
int calculations();
int check_xa(int, int);
int check_xm(int, int);
int count_glued(int, int);
int count_unique_cells();
void output_files(int, int, int);


int main(){
  int nr_of_cells_glued;

  for(int DELTA = 4; DELTA < 8; DELTA++){
    for (int i = 0; i < 2600; i++){
      Glue[i] = 0;
      Check[i] = 0;
      Orient[i] = 0;
    }

    setParameters(DELTA);
    create_lines();

    int freq=1;
    int i = -1;
    while(i <= 500){

      if (i%freq == 0){

      // printf("foto final_%d \n",i);
      read_input(DELTA,i);

      nr_of_cells_glued = calculations();
       if (i>0) printf("%d %d %d \n",i,DELTA,nr_of_cells_glued);
       output_files(DELTA, i, nr_of_cells_glued);
     }
     if ( i/freq > 10 ) {
         freq *= 10;}
       else{
         i++;
       }

  }


}



  return 0;
}
void setParameters(int DELTA){
  char read[12];
  sprintf(read,"DELTA%d/INPUT/inputparam.txt", DELTA);

  FILE *fp;
  fp = fopen(read, "r");
  while(fscanf(fp ,"%d %lf %lf %lf %d %d",&delta,&TEMPERATURA,&alpha,&kappa,&N_INITIAL,&N_T)==EOF){}
  fclose(fp);

	nr_n = 2;                 // (L - delta)/(dist + delta) + 1;
    dist = L/nr_n;
    xa = (int*)malloc(nr_n*sizeof(*xa));
    xm = (int*)malloc(nr_n*sizeof(*xm));
}
void create_lines(){

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
  char read[12];
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
    index = xa[i]*L;

    for(index; index < L*L; index += L){

      if(Check[matrix[index]] == 0){ // havent checked this cell-index before

        if (matrix[index] != 0){ // there is a cell next to the wall

          if (check_xa(matrix[index], index) == 1){ //whole cell is inside

            Glue[matrix[index]] = 1;
            Orient[matrix[index]] = count_glued(matrix[index], index);

          }
          else{
            Glue[matrix[index]] = 0;
          }
        }

        Check[matrix[index]] = 1;

      }
    }

      //checking for xm
      index = xm[i]*L;

      for(index; index < L*L; index += L){

        if(Check[matrix[index]] == 0){ // havent checked this cell-index before

          if (matrix[index] != 0){ // there is a cell next to the wall

            if (check_xm(matrix[index], index) == 1){ //whole cell is inside

              Glue[matrix[index]] = 1;
              Orient[matrix[index]] = count_glued(matrix[index], index);

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
int check_xa(int real_index, int index_xa){

  for (int i = 0; i <L*L; i++){
    int x = i/L;
    if (matrix[i] == real_index && x < (index_xa)/L){
      return 0;
    }
  }
  return 1;
}
int check_xm(int real_index, int index_xm){

  for (int i = 0; i <L*L; i++){
    int x = i/L;
    if (matrix[i] == real_index && x > (index_xm)/L){
      return 0;
    }
  }
  return 1;
}
int count_glued(int label, int index){
  int n_glued = 0;
  for (index; index < L*L; index += L){
    if (matrix[index] == label){
      n_glued ++;
    }
  }
  return n_glued;
}
int count_unique_cells(){
  int nr_unique =0;
  for (int i = 0; i < 2600; i++){
    if(Glue[i] != 0){
      nr_unique++;
    }
  }
  return nr_unique;
}

void output_files(int DELTA, int mcs, int nr_of_cells_glued){
  char write[100];
  FILE  *file;

	sprintf(write,"processed/distribution_DELTA%d_n_mcs%d.txt", DELTA, mcs);

  file = fopen(write, "w");

  fprintf(file, "nr of cells glued %d\n", nr_of_cells_glued);
  for (int i=0; i < 2600; i++){
    fprintf(file,"%d %d\n", i, Orient[i]);
  }
  fclose(file);
}
