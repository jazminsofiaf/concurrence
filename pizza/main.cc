#ifdef PIZZA


#include <iostream>
#include <unistd.h>
#include <stdlib.h>

#include "Semaforo.h"
#include "Machine.h"
#include "MemoriaCompartida.h"
#include "Amasador.h"
#include "Cortadora.h"
#include "Rallador.h"

using namespace std;

int calcularRandom ();
int getArgument(int argc, char** argv);

int main (int argc, char** argv) {
    int amount = getArgument(argc, argv);
	static const string NOMBRE = "main.cc";
	static const int MACHINES = 3;
    static const int OVEN_LIMIT = 5;
    static const int AMASADOR_ID = 0;
    static const int CORTADORA_ID = 1;
    static const int RALLADOR_ID = 2;

	Semaforo semaforo(NOMBRE, MACHINES, 0);

    Amasador * amasador = new Amasador(amount, &semaforo, AMASADOR_ID);
    Cortadora * cortadora = new Cortadora(amount, &semaforo, CORTADORA_ID ,AMASADOR_ID);
    Rallador * rallador = new Rallador(amount, &semaforo, RALLADOR_ID ,CORTADORA_ID);

    MemoriaCompartida<char> read_buffer;
    read_buffer.crear(PREPIZZA_CON_CEBOLLA_Y_QUESO, MEM_SIZE);
    while(amount > 0 ) {
        int pizzas = 0;
        while(pizzas < OVEN_LIMIT && pizzas < amount) {
            semaforo.pWait(RALLADOR_ID);
            char pizza_str[MEM_SIZE];
            read_buffer.leer(pizza_str);
            Pizza pizza_armada;
            pizza_armada.deserialize(pizza_str);
            cout << "Cocinero => recibe la prepizza armada " << pizza_armada.toString() << endl;
            cout << "Cocinero => mete la pizza en el horno" << endl;
            pizzas ++;
        }
        cout << "Cocinero => se enciende el horno a 180° con " << pizzas<< " pizzas" << endl;
        int tiempoDeCoccion = calcularRandom();
        sleep(tiempoDeCoccion);
        cout << "Cocinero => el horno termino de cocinar " << pizzas << " pizzas en " << tiempoDeCoccion
             << " minutos." << endl;
        amount -= pizzas;
    }

	// espero a que terminen los hijos antes de liberar los recursos
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


int calcularRandom () {
	srand ( time(NULL) );
	int resultado = rand() % 10 + 1;
	return resultado;
}

#endif
