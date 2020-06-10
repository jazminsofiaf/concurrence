#include "Horno.h"

Horno::Horno(){}

int Horno::calcularRandom(){
    srand ( time(NULL) );
    int resultado = rand() % 10 + 1;
    return resultado;
}

int Horno::encender(){
    int tiempo_de_coccion = this->calcularRandom();
    sleep(tiempo_de_coccion);
    return tiempo_de_coccion;
}

Horno::~Horno(){}
