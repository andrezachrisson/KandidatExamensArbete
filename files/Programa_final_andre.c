

/////  alpha is the volume fraction with in the initial area
/////  kappa is the strength of the channel interaction   50 is already infinite
////   delta is the size of the channel  larger than 6-10

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>



#define L 432 ////(108*2)
// #define MCSA 2
// #define MCS 10000
// #define total_iteraciones  16.0*L*L*MCS
// #define total_iteraciones_A  16.0*L*L*MCSA
#define n_VEC 8
#define RADIO ((L-1)/6)
#define FREE_SURFACE 1
#define lambda 1.0
#define TARGET_area 36.0




//#include "jj_figraul.h"

// #include "jj_fig7_1.h"
// #include "jj_fig12.h"
// #include "jj_fig18.h"
// #include "jj_fig22.h"

#include "jj_done.h"

double TEMPERATURA;
int delta;
int dist;
int nr_n;
int *xa;
int *xm;
double alpha;
double kappa;
int N_INITIAL;
int N;

int matrix[L*L];
double JA[3][3];
int size[L*L/2];

void output_files(int *Mo, int num,int *labels1);
void init_JA();
int fill_matrix(int *labels1);
void neighbors_content(int i, int *vecinos, int *v);
double calculate_energy(int *v, int i, int *vecinos, int state_i,int *labels1);
void Mo_auxiliar(int value, int* Mo);
double calculate_energy_area(int i);
void makecellexchange_test(int *vecinos,int *v, int *labels1, double T);
int glue_line_up(int i);
void setParameters();
void create_lines();
void makecellexchange_initial( int *vecinos,int *v, int *labels1, double T);


int main (void){

  setParameters();
  create_lines();



	double num_it;
	int i;

	int* Mo;
	Mo = malloc(L*L * sizeof (int));

	int* v;
        v = malloc(8 * sizeof (int));

	int* vecinos;
        vecinos = malloc(8 * sizeof (int));

	int* DEFINED_AREA;
        DEFINED_AREA = malloc(L*L * sizeof (int));

	int clusters;

	int NC=0; //Variable que acumula el número total de clusters.

	int size[L*L/2];

	int hist[L*L/2];
        int monte;

	fill_matrix(DEFINED_AREA);
        init_JA();

        printf("T= %f %d %d \n",TEMPERATURA,dist,delta);


	int updFrequency = 1;
        int N_MCS=0,A_MCS,temp=0;
        int SIZE_MCS = 16*L*L;
        double num_it_1,num_it_2;
        int Pre_iterations = N_INITIAL*16*L*L;
        int Pre_iteraciones_A = 2*16*L*L;

        for (num_it_1 = 0; num_it_1 < Pre_iterations; num_it_1++){

      		makecellexchange_initial(vecinos, v, DEFINED_AREA, TEMPERATURA);

          temp =  N_MCS;
          N_MCS = (int)(num_it_1/SIZE_MCS);

          if ( (N_MCS % updFrequency==0 && temp!=N_MCS) ) {

            for (num_it_2 = 0; num_it_2 < Pre_iteraciones_A; num_it_2++){

              makecellexchange_initial(vecinos, v, DEFINED_AREA, 0);

            }

      			printf("%f %d %f %d \n",num_it_1,N_MCS,num_it_1/SIZE_MCS,SIZE_MCS); fflush(0);

          }
          if(num_it_1 == 0) output_files(Mo,99999,DEFINED_AREA);
        }

        printf("Insert channels");
        N_MCS=0;
        temp=0;

        int total_iteraciones = N*16*L*L;
        int total_iteraciones_A = 2*16*L*L;

        for (num_it_1 = 0; num_it_1 < total_iteraciones; num_it_1++){

          makecellexchange_test(vecinos, v, DEFINED_AREA, TEMPERATURA);

          temp =  N_MCS;
          N_MCS = (int)(num_it_1/SIZE_MCS);

          if ( (N_MCS % updFrequency==0 && temp!=N_MCS) ) {

            for (num_it_2 = 0; num_it_2 < total_iteraciones_A; num_it_2++){

              makecellexchange_test(vecinos, v, DEFINED_AREA, 0);

           }

           printf("%f %d %f %d \n",num_it_1,N_MCS,num_it_1/SIZE_MCS,SIZE_MCS); fflush(0);

           output_files(Mo,N_MCS,DEFINED_AREA);
         }
         if(num_it_1 == 0) output_files(Mo,0,DEFINED_AREA);
         // if ( N_MCS/updFrequency > 10 ) updFrequency *= 10;
         //printf("%f %d\n",num_it_1,N_MCS );  fflush(0);
       }
     }

void output_files(int *Mo, int num,int *labels1){


	int clusters,i;

	int size[L*L];
	int hist[L*L];
        FILE  *file;

/***********************************/

        char foto_final[100];
	sprintf(foto_final,"OUTPUT/foto_final_label%d.txt",num);

        file = fopen(foto_final, "w");


         for (i=0; i<L*L; i++){
                int A=labels1[matrix[i]];
               // if (A==1) A=0;
		if ((i+1)%L==0 ) fprintf(file,"%d \n",A);
                else   fprintf(file,"%d ",A);

	}
        fclose(file);


        sprintf(foto_final,"OUTPUT/foto_final_%d.txt",num);

        file = fopen(foto_final, "w");


         for (i=0; i<L*L; i++){

		if ((i+1)%L==0 ) fprintf(file,"%d \n",matrix[i]);
                else   fprintf(file,"%d ",matrix[i]);

	}
        fclose(file);


        sprintf(foto_final,"OUTPUT/foto_final_fila%d.txt",num);

        file = fopen(foto_final, "w");


         for (i=0; i<L*L; i++){

		fprintf(file,"%d \n",matrix[i]);


	}
        fclose(file);

}

void init_JA(){

    JA[0][0] = J00;
    JA[0][1] = J01;
    JA[0][2] = J02;
    JA[1][0] = J01;
    JA[1][1] = J11;
    JA[1][2] = J12;
    JA[2][0] = J02;
    JA[2][1] = J12;
    JA[2][2] = J22;

}



int fill_matrix(int *labels1){

	int i, x, y, x_center, y_center,p,done;
	double r_value;

	int test[L*L];



	for (i=0; i<L*L; i++){

		r_value = (((double)rand() / (RAND_MAX)));

		if(r_value > alpha)

			test[i]=1;

		else
			test[i]=2;

	}

  i = 0;
  for (int j = 0; j < 4; j++){
        FILE  *file;

        file = fopen("INPUT/input_file_fig4_b.dat","r");

        printf("j2 %d\n", j%2);
	while(fscanf(file,"%d ",&p)!=EOF){

    x=i/L;
		y=i-x*L;



		x_center=(L/4)*(1 + (j%2)*2);
		y_center=(L/4)*(1 + (j%2)*2);

		if (pow(x-x_center,2) + pow(y-y_center,2) < pow(RADIO,2)){

      if ((i+1)%216 == 0 ){
        i+=216;
      }
                  matrix[i] = p;
			            labels1[p]= test[p];

                }
                else{
                    matrix[i]= 0;
                    labels1[0] = 0;
                }
                i++ ;
        }
        fclose(file);
      printf("i %d\n", (j%2)*216 + 215);
      }
}

void neighbors_content(int i, int *vecinos, int *v){


	int d;

	vecinos[0] = i - L - 1;
        vecinos[1] = i - L;
        vecinos[2] = i - L + 1;

        vecinos[3] = i - 1;
        vecinos[4] = i + 1;

        vecinos[5] = i + L - 1;
        vecinos[6] = i + L;
        vecinos[7] = i + L + 1;


       // Corregir PBC

        if (i<L) { //Primera fila
		vecinos[0] = i + (L*L- L) - 1;
		vecinos[1] = i + (L*L- L);
		vecinos[2] = i + (L*L- L) + 1;
        }

	if (i>L*(L-1)){ //Última fila
		vecinos[5] = i - (L*L)+ L - 1;
		vecinos[6] = i - (L*L)+ L;
		vecinos[7] = i - (L*L)+ L + 1;
	}

	if (i%L==0){ //Primera columna
		vecinos[0]= i - 1;
		vecinos[3]= i + L - 1;
		vecinos[5]= i + 2*L - 1;
	}
	if ((i+1)%L==0){ //Última columna
		vecinos[2]= i - 2*L + 1;
		vecinos[4]= i - L + 1;
		vecinos[7]= i + 1;
	}

	//EXTREMOS

	if (i==0){
		vecinos[0]=L*L - 1;
	}

	if (i==L-1){
		vecinos[2]=L*L - L;
	}

	if (i==L*(L-1)){
		vecinos[5]=i - L*L + 2*L -1;
		vecinos[6]=i - L*L + L;
		vecinos[7]=i - L*L + L + 1;

	}

	if (i==L*L-1){
		vecinos[7]= i - L*L + 1;
	}


	for (d=0;d<n_VEC; d++){

       		v[d] = matrix[vecinos[d]];

        }

}

double calculate_energy(int *v, int i, int *vecinos, int state_i,int *labels1){


	double energy=0.0;
	int r, delta_ij, sigma_i, sigma_j, J,H1,H2,tau_i,tau_j;

                neighbors_content(i, vecinos, v);

                sigma_i = state_i;

		for (r = 0; r < n_VEC; r++){

                        sigma_j = v[r];

                        if (sigma_i == sigma_j) delta_ij = 1.0;
                        else delta_ij = 0.0;

                        tau_i = labels1[sigma_i];
                        tau_j = labels1[sigma_j];

			energy = energy + JA[tau_i][tau_j]*(1.0 - delta_ij);

		}

	return (energy);
}

void Mo_auxiliar(int value, int* Mo){

	int k;

	for (k=0; k<L*L; k++){
		if (matrix[k]==value)
			Mo[k] = 1;
		else
			Mo[k] = 0;

	}
}



double calculate_energy_area(int i){


	double energy=0.0;
        int  clusters;

      	size[0]=0;
        for (i=0;i<L*L;i++)  size[matrix[i]]++;

		for (i=1;i<L*L/2;i++) {
             if (size[i]!=0) energy += (size[i]-TARGET_area)*(size[i]-TARGET_area);
             size[i]=0;
        }

        energy = energy*lambda;

   return(energy);
}
void makecellexchange_initial( int *vecinos,int *v, int *labels1, double T){

	double r_value,random_value2,x,energy_new=0.0,energy=0.0;
	int  j,state1,state2, i, aux1, accept, r_index;

	    i = rand() % (L*L); // Index between 0 and (L*L)-1;

     // if (labels1[matrix[i]]>0){ //Si estamos dentro del círculo
                // printf("ok %d %d\n",i,labels1[i]);  fflush(0);

		neighbors_content(i, vecinos, v);

        r_value = ((double)rand() / (RAND_MAX));    //Random value between 0 and 1
		r_index = (int)ceil(n_VEC*(r_value)) - 1;   // Integer index betwe en 0 and  n_VEC to select the neighbor:


/*#ifdef FREE_SURFACE
                while( labels1[ matrix[vecinos[r_index] ]]== 0 ){
                   r_value = ((double)rand() / (RAND_MAX));
                   r_index = (int)ceil(n_VEC*(r_value)) - 1;
                   //printf("%d %d \n",i,vecinos[r_index]);
                }
#endif */



        j = vecinos[r_index];

                                        // printf("ok 2 \n");

		state1 = matrix[i];
		energy = calculate_energy(v, i, vecinos, state1,labels1);

        state2 = matrix[j];

        // neighbors_content(j, vecinos, v);
        // energy += calculate_energy(v, j, vecinos, state2,labels1);
        energy += calculate_energy_area(j);

		   //Exchange of the values in the matrix


       // matrix[j] = state1;
       	matrix[i] = state2;

	    energy_new  = calculate_energy(v, i, vecinos, state2,labels1);

      //  neighbors_content(j, vecinos, v);
      //  energy_new += calculate_energy(v, j, vecinos, state1,labels1);

        energy_new += calculate_energy_area(i);



                //  if ( labels1[matrix[i]]>0 && delta>0) {
                //      int location = glue_line_up(i);
                //
                //       if( location > 0 ) {
                //            if( location == 1) energy_new += kappa*JA[2][2];
                //            else energy_new = -10000000000000000000.0;
                //
                //       }
                //
                // }


		if (energy_new <  energy)
			accept = 1;
		else {

			x =  exp(-(energy_new-energy)/T);
            random_value2 =  ((double)rand()/(RAND_MAX));

			if (x >=random_value2) accept=1;
			else{
				accept=0;
				matrix[i] = state1;
                // Actualizamos la matriz a su estado inicial.
                // matrix[j] = state2;
            }
		}
//	 }

}

void makecellexchange_test( int *vecinos,int *v, int *labels1, double T){

	double r_value,random_value2,x,energy_new=0.0,energy=0.0;
	int  j,state1,state2, i, aux1, accept, r_index;

	    i = rand() % (L*L); // Index between 0 and (L*L)-1;

     // if (labels1[matrix[i]]>0){ //Si estamos dentro del círculo
                // printf("ok %d %d\n",i,labels1[i]);  fflush(0);

		neighbors_content(i, vecinos, v);

        r_value = ((double)rand() / (RAND_MAX));    //Random value between 0 and 1
		r_index = (int)ceil(n_VEC*(r_value)) - 1;   // Integer index betwe en 0 and  n_VEC to select the neighbor:


/*#ifdef FREE_SURFACE
                while( labels1[ matrix[vecinos[r_index] ]]== 0 ){
                   r_value = ((double)rand() / (RAND_MAX));
                   r_index = (int)ceil(n_VEC*(r_value)) - 1;
                   //printf("%d %d \n",i,vecinos[r_index]);
                }
#endif */



        j = vecinos[r_index];

                                        // printf("ok 2 \n");

		state1 = matrix[i];
		energy = calculate_energy(v, i, vecinos, state1,labels1);

        state2 = matrix[j];

        // neighbors_content(j, vecinos, v);
        // energy += calculate_energy(v, j, vecinos, state2,labels1);
        energy += calculate_energy_area(j);

		   //Exchange of the values in the matrix


       // matrix[j] = state1;
       	matrix[i] = state2;

	    energy_new  = calculate_energy(v, i, vecinos, state2,labels1);

      //  neighbors_content(j, vecinos, v);
      //  energy_new += calculate_energy(v, j, vecinos, state1,labels1);

        energy_new += calculate_energy_area(i);



                 if ( labels1[matrix[i]]>0 && delta>0) {
                     int location = glue_line_up(i);

                      if( location > 0 ) {
                           if( location == 1) energy_new += kappa*JA[2][2];
                           else energy_new = -10000000000000000000.0;

                      }

                }


		if (energy_new <  energy)
			accept = 1;
		else {

			x =  exp(-(energy_new-energy)/T);
            random_value2 =  ((double)rand()/(RAND_MAX));

			if (x >=random_value2) accept=1;
			else{
				accept=0;
				matrix[i] = state1;
                // Actualizamos la matriz a su estado inicial.
                // matrix[j] = state2;
            }
		}
//	 }

}

int glue_line_up(int i){

  int response,x,y,nx;
	x=i/L;
	y=i-x*L;

  int search = x/dist;
    // printf("%d %d %d \n",xa[search],xm[search],x);

    if ( (x == xa[search] + 1) || (x == xm[search] - 1)) response = 1;
    else {

         if ( (x == xa[search]) || (x == xm[search])) response = 2;
         else response = 0;

    }



    return(response);
  }


void setParameters(){
  FILE *fp;
  fp = fopen("INPUT/inputparam.txt", "r");

  while (fscanf(fp ,"%d %lf %lf %lf %d %d",&delta,&TEMPERATURA,&alpha,&kappa,&N_INITIAL,&N)!= EOF){
	}

  fclose(fp);

	nr_n = 6;                 // (L - delta)/(dist + delta) + 1;
    dist = L/nr_n;
    xa = malloc(nr_n*sizeof(*xa));
	xm = malloc(nr_n*sizeof(*xm));
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
