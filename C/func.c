#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#define L (216)

int TEMPERATURA;
int delta;
int dist;
int nr_n;
int *xa;
int *xm;

void create_lines();
void setParameters();
int glue_line_up(int i);


int main(){

  setParameters();
  printf("dist %d delta %d TEMPERATURA %d \n",dist, delta, TEMPERATURA );

  create_lines();

  for(int i = 0; i < nr_n; i++){
    printf("%d %d \n", xa[i], xm[i]);
  }
  int p = 2;
  int response = glue_line_up(p);
  printf("%d\n",response);


  return 0;
}
void setParameters(){
  FILE *fp;
  fp = fopen("INPUT/inputparam.txt", "r");
  while (fscanf(fp , "%d %d %d", &dist, &delta, &TEMPERATURA)!= EOF){
	}
	fclose(fp);
	nr_n = (L - delta)/(dist + delta) + 1;
  xa = malloc(nr_n*sizeof(*xa));
	xm = malloc(nr_n*sizeof(*xm));
}
void create_lines(){
  int Xa = L/2 + (delta-1)/2;
  int Xm = L/2 - (delta-1)/2;

  for (int i = (nr_n)/2; i < nr_n; i++){
    xa[i] = Xa;
    xm[i] = Xm;
    Xa += delta + dist;
    Xm += delta + dist;
  }

  Xa = L/2 + delta/2;
  Xm = L/2 - delta/2;

  for (int i = (nr_n)/2 - 1; i >= 0; i--){
    Xa -= delta + dist;
    Xm -= delta + dist;
    xa[i] = Xa;
    xm[i] = Xm;
  }
}
int glue_line_up(int i){
   int response,x,y,nx;
   x=i;
   y=i-x*L;

   int search = x/(dist+delta);

   if (x == xa[search] - 1){
     response = 1;
   }else if(x == xm[search] + 1){
     response = 2;
   }else {
     response = 0;
   }

   return(response);
}
