#ifdef PIZZA

#define CHILD_PID 0
#define OK 0
#define ARG 1
#define NONE -1
#define MEM_SIZE 14
#define SHM "Semaforo.cpp"

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sstream>
#include <sys/wait.h>

#include "Semaforo.h"
#include "MemoriaCompartida.h"


using namespace std;

int calcularRandom ();
void initMachine(int amount, Semaforo *semaforo, int semaforo_id , int previous_id, std::string msg);
int getArgument(int argc, char** argv);

struct Pizza {
    int amasadora;
    int cortadora;
    int rallador;
    std::string toString(){
        return  "Pizza { amasado: " + std::to_string(amasadora)
        +", corte de ingredientes: " + std::to_string(cortadora)
        +", rallado de muzarella: " + std::to_string(rallador) +" }";
    }
    const char * serialize() {
        std::ostringstream out;
        out  << amasadora << '|' << cortadora << '|' << rallador;
        return out.str().c_str();
    }

    void deserialize(const char * msg){
        char  pipe1 =0, pipe2 = 0;
        std::istringstream in(msg);
        in  >> amasadora >> pipe1 >> cortadora >> pipe2 >> rallador;
    }
};

int main (int argc, char** argv) {
    int amount = getArgument(argc, argv);
	static const string NOMBRE = "main.cc";
	static const int MACHINES = 3;
    static const int OVEN_LIMIT = 5;
    static const int AMASADOR_ID = 0;
    static const int CORTADORA_ID = 1;
    static const int RALLADOR_ID = 2;

	Semaforo semaforo(NOMBRE, MACHINES, 0);


    initMachine(amount, &semaforo, AMASADOR_ID ,NONE, "Maquina amasadora => termina de amazar la masa de una pizza");
    initMachine(amount, &semaforo, CORTADORA_ID ,AMASADOR_ID, "Maquina cortadora => termino de cortar los ingredientes y se lo puso a la masa");
    initMachine(amount, &semaforo, RALLADOR_ID ,CORTADORA_ID, "Maquina ralladora => termino de rallar la muzarella y se lo puso a la masa ");

    MemoriaCompartida<char> buffer;
    buffer.crear(SHM, MEM_SIZE);
    while(amount > 0 ) {
        int pizzas = 0;
        while(pizzas < OVEN_LIMIT && pizzas < amount) {
            semaforo.pWait(2);
            char pizza_str[MEM_SIZE];
            buffer.leer(pizza_str);
            Pizza pizza_armada;
            pizza_armada.deserialize(pizza_str);
            cout << "Cocinero => recibe la prepizza armada " << pizza_armada.toString() << endl;
            cout << "Cocinero => se mete la pizza en el horno" << endl;
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
	for(int i=0; i < MACHINES; i++ ) {
		wait(NULL);
	}
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

void initMachine(int amount, Semaforo *semaforo,  int semaforo_id, int previous_id, std::string msg){
    pid_t pid = fork();
    if ( pid == CHILD_PID ) {

        MemoriaCompartida<char> buffer;
        buffer.crear(SHM, MEM_SIZE);

        for(int i=0; i < amount; i++ ) {
            if(previous_id != NONE){
                semaforo->pWait(previous_id);
            }
            cout << "(pid " << getpid() << "): "<< msg << endl;

            Pizza pizza;
            pizza.amasadora = 0;
            pizza.cortadora =0;
            pizza.rallador = 0;
            buffer.escribir(pizza.serialize());

            semaforo->vSignal(semaforo_id);
            semaforo->waitZero(semaforo_id);
        }
        cout << "(pid " << getpid() << "): termino"<< endl;
        exit(OK);
    }
}



int calcularRandom () {
	srand ( time(NULL) );
	int resultado = rand() % 10 + 1;
	return resultado;
}

#endif
