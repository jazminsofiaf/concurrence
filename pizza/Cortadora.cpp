
#include "Cortadora.h"

Cortadora::Cortadora(int amount, Semaforo *semaforo_write, Semaforo *semaforo_read,
                     int amasador_write_id,  int cortadora_read_id ,int cortadora_write_id, int rallador_read_id){
    this->read_buffer.crear(PREPIZZA, ITEM_SIZE, MEM_SIZE);
    this->write_buffer.crear(PREPIZZA_CON_CEBOLLA, ITEM_SIZE, MEM_SIZE);
    this->initMachine(amount, semaforo_write, semaforo_read, amasador_write_id, cortadora_read_id, cortadora_write_id, rallador_read_id);
}

void Cortadora::doTask(int index){
    char pizza_str[ITEM_SIZE];
    Pizza prepizza;
    this->read_buffer.leer(index, pizza_str);
    prepizza.deserialize(pizza_str);
    std::string msg = "Maquina cortadora => toma una prepizza recien amasada ";
    std::cout << "(pid " << getpid() << "): " << msg << prepizza.toString() << std::endl;
    prepizza.cortadora = this->num++;
    this->write_buffer.escribir(index, prepizza.serialize());
    msg ="Maquina cortadora => termino de cortar la cebolla y se lo puso a la masa ";
    std::cout << "(pid " << getpid() << "): "<< msg << prepizza.toString() <<std::endl;
}

Cortadora::~Cortadora(){
    this->read_buffer.liberar();
    this->write_buffer.liberar();
}
