
#ifndef RALLADOR_H
#define RALLADOR_H


#include "Machine.h"

class Rallador : public Machine{
public:
    Rallador(int amount, Semaforo *semaforo_write, Semaforo *semaforo_read,
             int cortadora_write_id, int rallador_read_id, int rallador_write_id, int cocinero_read_id );
    ~Rallador();
private:
    void doTask(int index) override ;
};


#endif //RALLADOR_H
