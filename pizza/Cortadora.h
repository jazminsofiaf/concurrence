#ifndef CORTADORA_H
#define CORTADORA_H

#include "Machine.h"

class Cortadora : public Machine {
public:
    Cortadora(int amount, Semaforo *semaforo_write, Semaforo *semaforo_read,
            int amasador_write_id,  int cortadora_read_id ,int cortadora_write_id, int rallador_read_id);
    ~Cortadora();
private:
    void doTask(int index) override;
};

#endif //CORTADORA_H
