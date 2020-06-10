
#ifndef RALLADOR_H
#define RALLADOR_H


#include "Machine.h"

class Rallador : public Machine{
public:
    Rallador(int amount, Semaforo *semaforo, int semaforo_id, int previous_id);
private:
    void doTask() override ;
};


#endif //INC_06_SEMAFOROS_RALLADOR_H
