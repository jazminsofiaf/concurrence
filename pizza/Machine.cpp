#include "Machine.h"
using namespace std;

void Machine::initMachine(int amount, Semaforo *semaforo,  int semaforo_id, int previous_id, std::string msg){
    pid_t pid = fork();
    if ( pid == CHILD_PID ) {

        MemoriaCompartida<char> buffer;
        buffer.crear(SHM, MEM_SIZE);

        for(int i=0; i < amount; i++ ) {
            if(previous_id != NONE){
                semaforo->pWait(previous_id);
            }
            cout << "(pid " << getpid() << "): "<< msg << endl;

            this->doTask(buffer);
            semaforo->vSignal(semaforo_id);
            semaforo->waitZero(semaforo_id);
        }
        cout << "(pid " << getpid() << "): termino"<< endl;
        exit(OK);
    }
}

void Machine::doTask(MemoriaCompartida<char> buffer){

    //Pizza pizza;
    //pizza.amasadora = 0;
    //pizza.cortadora =0;
    //pizza.rallador = 0;
    buffer.escribir("pizza.serialize()");

}
