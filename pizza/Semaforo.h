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

    int waitZero (const int id) const; // esperar a que sea cero
    int debug (const int id) const; // esperar a que sea cero
	int pWait (const int id, const int num) const; // decrementa en num
	int vSignal (const int id, const int num) const; // incrementa en num
    int pWait (const int id) const; // decrementa
    int vSignal (const int id) const; // incrementa
	void eliminar () const;

};

#endif /* SEMAFORO_H_ */
