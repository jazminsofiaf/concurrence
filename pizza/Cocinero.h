
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
    void cocinar(int amount, Semaforo *semaforo, const int semaforo_previous_id);
    ~Cocinero();

};


#endif //COCINERO_H
