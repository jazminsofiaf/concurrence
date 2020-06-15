#ifndef MACHINE_H
#define MACHINE_H


#define CHILD_PID 0

#include <iostream>
#include <unistd.h>
#include <sstream>

#include "Semaforo.h"
#include "MemoriaCompartida.h"
#include "Constants.h"

class Machine {
private:
    pid_t pid;
protected:
    int num;
    MemoriaCompartida<char> write_buffer;
    MemoriaCompartida<char> read_buffer;
    Machine();
    void initMachine(int amount, Semaforo *sem_write, Semaforo *sem_read,
                    int previous_write, int read, int write , int next_read);

    virtual void doTask(int index) = 0;

public:
    void shutDown();
    virtual ~Machine();
};

struct Pizza {
    int amasadora;
    int cortadora;
    int rallador;
    std::string toString(){
        return  "Pizza { amasado: " + std::to_string(amasadora)
                +", corte de ingredientes: " + std::to_string(cortadora)
                +", rallado de muzzarella: " + std::to_string(rallador) +" }";
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
