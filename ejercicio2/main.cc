/*"A partir de un proceso padre, crear 10 procesos hijo. Cada proceso hijo
deberá dormir (sleep) una cant. aleatoria de segundos y finalizar al padre la
cantidad de segundos que durmió. El proceso padre deberá imprimir las
cantidades de segundos que fueron durmiendo los hijos."*/
#ifdef EJERCICIO_2

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "MemoriaCompartida2.h"
int calcularRandom (int i);
int get_index(pid_t arr[], pid_t element);

int main () {

	std::string archivo = "/bin/ls";

  pid_t childrenIds[10];

  for(int i= 0; i < 10; i++){
	     pid_t procId = fork ();
	      if ( procId == 0 ) {
      		// codigo del hijo
          		try {
              			MemoriaCompartida2<int> buffer ( archivo,'A',10);

                    int random = calcularRandom (i);
                    	std::cout << "Hijo"<< i << ": voy a dormir " << random  << " ("<< getpid() <<")" << std::endl;
                    sleep ( random );
              			std::cout << "Hijo"<< i << ": escribo " << random << " en la memoria compartida" << " ("<< getpid() <<")" << std::endl;
              			buffer.escribir(i, random);


              			std::cout << "Hijo"<< i << ": fin del proceso"  << " ("<< getpid() <<")" << std::endl;
          		} catch ( std::string& mensaje ) {
                		std::cerr << mensaje << std::endl;
          		}
    		      exit(0);
        }
        else{
          childrenIds[i] = procId;
        }
	}
  // codigo del padre
  for(int i= 0; i < 10; i++){
    		try {
        			MemoriaCompartida2<int> buffer ( archivo,'A',10 );
              // espera a que termine el hijo
        			std::cout << "Padre: esperando a que termine el hijo" << std::endl;
        			pid_t childId =  wait(NULL);
              int index = get_index(childrenIds, childId);
              std::cout << "Padre: mi hijo "<< childId <<" escribio en la posicion " <<index <<" de memoria compartida "  << std::endl;

        			int resultado = buffer.leer(index);
        			std::cout << "Padre: mi hijo "<< childId <<" durmio " << resultado << " segundos." << std::endl;

    		} catch ( std::string& mensaje ) {
    			    std::cerr << mensaje << std::endl;
    		}
	}
  exit(0);

}

int get_index(pid_t arr[], pid_t element){
  for (int i = 0; i < 10; i++){
       if (element  == arr[i]){
           return i;
       }
   }
   return -1;
}

int calcularRandom (int i) {
	srand ( (unsigned int) time(NULL)*i );
	int resultado = rand() % 10 + 1;
	return resultado;
}

#endif
