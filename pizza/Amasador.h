
#ifndef AMASADOR_H
#define AMASADOR_H

#include "Machine.h"

class Amasador : public Machine{
public:
    Amasador(int amount, Semaforo *sem_write, Semaforo *sem_read, int write_id, int read_id);
    ~Amasador();
private:
    void doTask(int index) override;
};


#endif //AMASADOR_H
