#ifdef PIZZA

#include "Semaforo.h"
#include "Amasador.h"
#include "Cortadora.h"
#include "Rallador.h"
#include "Cocinero.h"

using namespace std;

int getArgument(int argc, char** argv);

int main (int argc, char** argv) {
    int amount = getArgument(argc, argv);
	static const string NOMBRE = "main.cc";
	static const int MACHINES = 3;
    static const int AMASADOR_ID = 0;
    static const int CORTADORA_ID = 1;
    static const int RALLADOR_ID = 2;
	Semaforo semaforo(NOMBRE, MACHINES, 0);

    Cocinero cocinero;
    Amasador * amasador = new Amasador(amount, &semaforo, AMASADOR_ID);
    Cortadora * cortadora = new Cortadora(amount, &semaforo, CORTADORA_ID ,AMASADOR_ID);
    Rallador * rallador = new Rallador(amount, &semaforo, RALLADOR_ID ,CORTADORA_ID);

    cocinero.cocinar(amount, &semaforo, RALLADOR_ID);

	amasador->shutDown();
	cortadora->shutDown();
    rallador->shutDown();
    semaforo.eliminar();

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
