#ifndef SEMAFORO_H_
#define SEMAFORO_H_

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <string>
#include <iostream>
#include <cerrno>

class Semaforo {

private:
	int id;
	int valorInicial;
	int cantidad;

	int inicializar () const;

public:
	Semaforo ( const std::string& nombre, const int cantidad, const int valorInicial );
	~Semaforo();

    int waitZero (const int num) const; // esperar a que sea cero
	int pWait (const int num) const; // decrementa
	int vSignal (const int num) const; // incrementa
	void eliminar () const;

};

#endif /* SEMAFORO_H_ */
