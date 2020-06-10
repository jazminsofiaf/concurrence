
#ifndef HORNO_H
#define HORNO_H


#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
class Horno {
private:
    int calcularRandom();

public:
    Horno();
    int encender();
    ~Horno();

};

#endif //HORNO_H
