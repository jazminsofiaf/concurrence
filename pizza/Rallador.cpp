
#include "Rallador.h"

Rallador::Rallador(int amount, Semaforo *semaforo_write, Semaforo *semaforo_read,
                   int cortadora_write_id, int rallador_read_id, int rallador_write_id, int cocinero_read_id){
    this->read_buffer.crear(PREPIZZA_CON_CEBOLLA, ITEM_SIZE, MEM_SIZE);
    this->write_buffer.crear(PREPIZZA_CON_CEBOLLA_Y_QUESO, ITEM_SIZE, MEM_SIZE);
    this->initMachine(amount, semaforo_write, semaforo_read,
                        cortadora_write_id, rallador_read_id, rallador_write_id,  cocinero_read_id);
}

void Rallador::doTask( int index){
    char pizza_str[ITEM_SIZE];
    Pizza prepizza;
    this->read_buffer.leer(index, pizza_str);
    prepizza.deserialize(pizza_str);
    std::string msg = "Maquina ralladora => toma la prepizza con cebolla cortada ";
    std::cout << "(pid " << getpid() << "): " << msg << prepizza.toString() << std::endl;
    prepizza.rallador = this->num++;
    this->write_buffer.escribir(index, prepizza.serialize());
    msg ="Maquina ralladora => termino de rallar la muzarella y se lo puso a la masa ";
    std::cout << "(pid " << getpid() << "): "<< msg << prepizza.toString() <<std::endl;
}

Rallador::~Rallador(){
    this->read_buffer.liberar();
    this->write_buffer.liberar();
}

