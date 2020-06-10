#include "Cocinero.h"

using namespace std;

Cocinero::Cocinero(){}

void Cocinero::cocinar(int amount, Semaforo *semaforo, const int semaforo_previous_id) {
    static const int OVEN_LIMIT = 5;
    static const int SEMAFORO_K_VALUE = 2;
    Horno horno;

    MemoriaCompartida<char> read_buffer;
    read_buffer.crear(PREPIZZA_CON_CEBOLLA_Y_QUESO, MEM_SIZE);
    while(amount > 0 ) {
        int pizzas = 0;
        while(pizzas < OVEN_LIMIT && pizzas < amount) {
            semaforo->pWait(semaforo_previous_id, SEMAFORO_K_VALUE);
            char pizza_str[MEM_SIZE];
            read_buffer.leer(pizza_str);
            Pizza pizza_armada;
            pizza_armada.deserialize(pizza_str);
            cout << "Cocinero => recibe la prepizza armada " << pizza_armada.toString() << endl;
            cout << "Cocinero => mete la pizza en el horno" << endl;
            pizzas ++;
        }
        cout << "Cocinero => se enciende el horno a 180° con " << pizzas<< " pizzas" << endl;
        int tiempo_de_coccion = horno.encender();
        cout << "Cocinero => el horno termino de cocinar " << pizzas << " pizzas en " << tiempo_de_coccion
             << " minutos." << endl;
        amount -= pizzas;
    }
    read_buffer.liberar();
}
Cocinero::~Cocinero(){}
