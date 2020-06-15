#include "Machine.h"
using namespace std;

Machine::Machine():num(1){}

void Machine::initMachine(int amount, Semaforo *sem_write, Semaforo *sem_read,
                          int previous_write, int read, int write , int next_read){
    this->pid = fork();
    if ( pid == CHILD_PID ){
        int index;
        for(int i=0; i < amount; i++ ) {
            if(read != NONE){
                sem_read->pWait(read); //espero a que haya algo para leer
            }
            sem_write->pWait(write);
            index = i % MEM_SIZE;
            doTask(index); //(quizas leo del buffer anterior) y escribo en mi buffer
            if(previous_write != NONE) {
                sem_write->vSignal(previous_write); //aviso que pueden seguir escribiendo en el buffer de lectura
            }
            sem_read->vSignal(next_read); //aviso que pueden leer del buffer en el que escribi
        }
        sem_read->waitZero(next_read); //antes de terminar espero que se hayan leido todos los datos del uktimo buffer
        exit(OK);
    }
}


void Machine::shutDown(){
    int status;
    pid_t rc_pid = waitpid(this->pid, &status, 0);
    if (rc_pid < 0) {
        if (errno == ECHILD) {
            std::cerr <<" child does not exist" << std::endl;
            return;
        }
        else {
            std::cerr << " bad argument passed to waitpid" << this->pid << std::endl;
            return;
        }
    }
    if(WIFSIGNALED(status)){//true if child was killed by any signal from other process or same process
        std::cerr << this->pid <<" terminates by signal : " << WTERMSIG(status) << std::endl;
    }
    delete this;
}

Machine::~Machine() {}
