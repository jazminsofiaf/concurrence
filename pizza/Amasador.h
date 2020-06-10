
#ifndef AMASADOR_H
#define AMASADOR_H

#include "Machine.h"

class Amasador : public Machine{
public:
    Amasador(int amount, Semaforo *semaforo, int semaforo_id);
    ~Amasador();
private:
    void doTask() override;
};


#endif //AMASADOR_H
