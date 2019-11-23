#include <stdlib.h> 
#include <cstdlib>
#include <cstdio>
#include <algorithm>


       
int main(int argc, char** argv)
{
    
     int m_iterations;
     
     
     FILE *p = popen("gnuplot", "w");

     for(m_iterations=1;m_iterations<=300;m_iterations++){


             fprintf(p, "p 'OUTPUT/foto_final_label%d.txt' matrix with image ;",m_iterations);
             fprintf(p, "unset key ; rep;");          
        
    }
    pclose(p);
    
    return 0;
}
