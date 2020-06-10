#include "Machine.h"
using namespace std;

Machine::Machine():num(1){}

void Machine::initMachine(int amount, Semaforo *semaforo,  int semaforo_id, int previous_id){
    this->pid = fork();
    if ( pid == CHILD_PID ) {
        for(int i=0; i < amount; i++ ) {
            if(previous_id != NONE){
                semaforo->pWait(previous_id);
            }
            doTask();
            semaforo->vSignal(semaforo_id);
            semaforo->waitZero(semaforo_id);
        }
        cout << "(pid " << getpid() << "): termino"<< endl;
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
}

Machine::~Machine() {}