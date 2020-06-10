
#include "Cortadora.h"

Cortadora::Cortadora(int amount, Semaforo *semaforo, int semaforo_id, int previous_id){
    this->read_buffer.crear(PREPIZZA, MEM_SIZE);
    this->write_buffer.crear(PREPIZZA_CON_CEBOLLA, MEM_SIZE);
    this->initMachine(amount, semaforo, semaforo_id, previous_id);
}

void Cortadora::doTask(){
    char pizza_str[MEM_SIZE];
    Pizza prepizza;
    this->read_buffer.leer(pizza_str);
    prepizza.deserialize(pizza_str);
    std::string msg = "Maquina cortadora => toma una prepizza recien amasada ";
    std::cout << "(pid " << getpid() << "): " << msg << prepizza.toString() << std::endl;
    prepizza.cortadora = this->num++;
    this->write_buffer.escribir(prepizza.serialize());
    msg ="Maquina cortadora => termino de cortar la cebolla y se lo puso a la masa ";
    std::cout << "(pid " << getpid() << "): "<< msg << prepizza.toString() <<std::endl;

}
