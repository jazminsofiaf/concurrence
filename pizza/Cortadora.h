#ifndef CORTADORA_H
#define CORTADORA_H

#include "Machine.h"

class Cortadora : public Machine {
public:
    Cortadora(int amount, Semaforo *semaforo, int semaforo_id , int previous_id);
private:
    void doTask() override;
};

#endif //CORTADORA_H
