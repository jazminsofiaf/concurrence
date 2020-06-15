
#ifndef COCINERO_H
#define COCINERO_H
#include <unistd.h>
#include "Constants.h"
#include "Semaforo.h"
#include "Machine.h"
#include "Horno.h"
#include "MemoriaCompartida.h"

class Cocinero {

public:
    Cocinero();
    void cocinar(int amount, Semaforo *sem_write, Semaforo *sem_read, const int rallador_write_id, const int cocinero_read_id);
    ~Cocinero();

};


#endif //COCINERO_H
