
#include "Amasador.h"

Amasador::Amasador(int amount, Semaforo *semaforo, int semaforo_id){
    this->write_buffer.crear(PREPIZZA, MEM_SIZE);
    this->initMachine(amount, semaforo, semaforo_id, NONE);
}

void Amasador::doTask(){
    Pizza prepizza;
    prepizza.amasadora = this->num++;
    prepizza.cortadora = 0;
    prepizza.rallador = 0;
    this->write_buffer.escribir(prepizza.serialize());
    std::string task_msg = "Maquina amasadora => termina de amasar la masa de ";
    std::cout << "(pid " << getpid() << "): "<< task_msg << prepizza.toString() <<  std::endl;
}

Amasador::~Amasador(){}

