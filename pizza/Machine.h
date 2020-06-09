#ifndef MACHINE_H
#define MACHINE_H


#define CHILD_PID 0

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sstream>

#include "Semaforo.h"
#include "MemoriaCompartida.h"
#include "Constants.h"

class Machine {
public:
    void initMachine(int amount, Semaforo *semaforo, int semaforo_id , int previous_id, std::string msg);
private:
    void doTask(MemoriaCompartida<char> buffer);
};

struct Pizza {
    int amasadora;
    int cortadora;
    int rallador;
    std::string toString(){
        return  "Pizza { amasado: " + std::to_string(amasadora)
                +", corte de ingredientes: " + std::to_string(cortadora)
                +", rallado de muzarella: " + std::to_string(rallador) +" }";
    }
    const char * serialize() {
        std::ostringstream out;
        out  << amasadora << '|' << cortadora << '|' << rallador;
        return out.str().c_str();
    }

    void deserialize(const char * msg){
        char  pipe1 =0, pipe2 = 0;
        std::istringstream in(msg);
        in  >> amasadora >> pipe1 >> cortadora >> pipe2 >> rallador;
    }
};


#endif //MACHINE_H
