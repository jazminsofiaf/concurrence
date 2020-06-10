
#include "Rallador.h"

Rallador::Rallador(int amount, Semaforo *semaforo, int semaforo_id , int previous_id){
    this->read_buffer.crear(PREPIZZA_CON_CEBOLLA, MEM_SIZE);
    this->write_buffer.crear(PREPIZZA_CON_CEBOLLA_Y_QUESO, MEM_SIZE);
    this->initMachine(amount, semaforo, semaforo_id, previous_id);
}

void Rallador::doTask(){
    char pizza_str[MEM_SIZE];
    Pizza prepizza;
    this->read_buffer.leer(pizza_str);
    prepizza.deserialize(pizza_str);
    std::string msg = "Maquina ralladora => toma la prepizza con cebolla cortada ";
    std::cout << "(pid " << getpid() << "): " << msg << prepizza.toString() << std::endl;
    prepizza.rallador = this->num++;
    this->write_buffer.escribir(prepizza.serialize());
    msg ="Maquina ralladora => termino de rallar la muzarella y se lo puso a la masa ";
    std::cout << "(pid " << getpid() << "): "<< msg << prepizza.toString() <<std::endl;
}

Rallador::~Rallador(){
    std::cout << "(pid " << getpid() << "): delete rallador" <<std::endl;
    this->read_buffer.liberar();
    this->write_buffer.liberar();
}

