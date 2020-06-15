#include "Cocinero.h"

using namespace std;

Cocinero::Cocinero(){}

void Cocinero::cocinar(int amount, Semaforo *sem_write, Semaforo *sem_read,
                        const int rallador_write_id, const int cocinero_read_id) {
    static const int OVEN_LIMIT = 5;
    Horno horno;

    MemoriaCompartida<char> read_buffer;
    read_buffer.crear(PREPIZZA_CON_CEBOLLA_Y_QUESO, ITEM_SIZE, MEM_SIZE);
    char pizza_str[ITEM_SIZE];
    int index = 0;
    while(amount > 0 ) {
        int pizzas = 0;
        while(pizzas < OVEN_LIMIT && pizzas < amount) {
            sem_read->pWait(cocinero_read_id);
            memset(pizza_str, '\0', ITEM_SIZE);
            read_buffer.leer(index, pizza_str);
            sem_write->vSignal(rallador_write_id);
            Pizza pizza_armada;
            pizza_armada.deserialize(pizza_str);
            cout << "Cocinero => recibe la prepizza armada " << pizza_armada.toString() << endl;
            cout << "Cocinero => mete la pizza en el horno" << endl;
            pizzas ++;
            index ++;
            if(index == MEM_SIZE){
                index = 0;
            }
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
