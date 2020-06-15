
#include "Amasador.h"

Amasador::Amasador(int amount,Semaforo *sem_write, Semaforo *sem_read, int write_id, int next_read_id){
    this->write_buffer.crear(PREPIZZA,ITEM_SIZE, MEM_SIZE);
    this->initMachine(amount, sem_write, sem_read, NONE, NONE, write_id, next_read_id);
}

void Amasador::doTask(int index){
    Pizza prepizza;
    prepizza.amasadora = this->num++;
    prepizza.cortadora = 0;
    prepizza.rallador = 0;

    this->write_buffer.escribir(index, prepizza.serialize());
    std::string task_msg = "Maquina amasadora => termina de amasar la masa de ";
    std::cout << "(pid " << getpid() << "): "<< task_msg <<prepizza.toString() <<  std::endl;
}

Amasador::~Amasador(){
    this->write_buffer.liberar();
}

