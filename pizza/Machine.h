#ifndef MACHINE_H
#define MACHINE_H


#define CHILD_PID 0

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

#include "Semaforo.h"
#include "MemoriaCompartida.h"
#include "Constants.h"

class Machine {

public:
    void initMachine(int amount, Semaforo *semaforo, int semaforo_id , int previous_id, std::string msg);

private:
    void doTask(MemoriaCompartida<char> buffer);

};


#endif //MACHINE_H
