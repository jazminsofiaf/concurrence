#ifdef PIZZA

#include "Semaforo.h"
#include "Amasador.h"
#include "Cortadora.h"
#include "Rallador.h"
#include "Cocinero.h"
#include "Constants.h"

using namespace std;

int getArgument(int argc, char** argv);

int main (int argc, char** argv) {
    int amount = getArgument(argc, argv);

	static const int MACHINES = 3;

    static const string NOMBRE_READ = "main.cc";
    static const int CORTADORA_READ_ID = 0;
    static const int RALLADOR_READ_ID = 1;
    static const int COCINERO_READ_ID = 2;
    Semaforo semaforo_read(NOMBRE_READ, MACHINES, 0);

    static const string NOMBRE_WRITE = "Machine.h";
    static const int AMASADOR_WRITE_ID = 0;
    static const int CORTADORA_WRITE_ID = 1;
    static const int RALLADOR_WRITE_ID = 2;
    Semaforo semaforo_write(NOMBRE_WRITE, MACHINES, MEM_SIZE);

    Amasador * amasador = new Amasador(amount, &semaforo_write, &semaforo_read,
                                        AMASADOR_WRITE_ID, CORTADORA_READ_ID);
    Cortadora * cortadora = new Cortadora(amount, &semaforo_write, &semaforo_read,
                                          AMASADOR_WRITE_ID, CORTADORA_READ_ID , CORTADORA_WRITE_ID, RALLADOR_READ_ID);
    Rallador * rallador = new Rallador(amount, &semaforo_write, &semaforo_read ,
                                       CORTADORA_WRITE_ID, RALLADOR_READ_ID , RALLADOR_WRITE_ID, COCINERO_READ_ID);

    Cocinero cocinero;
    cocinero.cocinar(amount, &semaforo_write, &semaforo_read, RALLADOR_WRITE_ID, COCINERO_READ_ID);

	amasador->shutDown();
	cortadora->shutDown();
    rallador->shutDown();


    semaforo_write.eliminar();
    semaforo_read.eliminar();


	exit(OK);
}

int getArgument(int argc, char** argv){
    if(argc < ARG){
        std::cerr << "Debe ingresar la cantidad de pizzas" << std::endl;
        throw std::runtime_error("Error: Invalid Arguments");
    }
    std::string argument = argv[ARG];
    try{
        return std::stoi(argument);
    } catch (std::invalid_argument const &e){
        std::cerr << "Bad input: not int value" << argument <<std::endl;
    } catch (std::out_of_range const &e){
        std::cerr << "Integer overflow " << std::endl;
    }
    return 0;
}

#endif
