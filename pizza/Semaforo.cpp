#include "Semaforo.h"

Semaforo :: Semaforo( const std::string& nombre, const int cantidad,  const int valorInicial ):valorInicial(valorInicial) {
	key_t clave = ftok(nombre.c_str(), 'a');
	this->id = semget (clave, cantidad, 0666 | IPC_CREAT );
    this->cantidad = cantidad;
	this->inicializar();
}

Semaforo::~Semaforo() {
}

int Semaforo :: inicializar () const {

    union semnum {
        int val;
        struct semid_ds *buf;
        ushort *array;
    };

    semnum init;
    init.val = this->valorInicial;

    int resultado = 0;
    for (int i = 0; i < this->cantidad; i++){
        int res = semctl(this->id, i, SETVAL, init);
        if(res == -1){
            std::cerr << "error al crear semaforo" << std::strerror(errno) <<std::endl;
        }
    }
	return resultado;
}


int Semaforo::waitZero (const int id) const {
    struct sembuf operacion;

    operacion.sem_num = id;	// numero de semaforo
    operacion.sem_op  = 0;	// espera hasta que el semaforo sea cero
    operacion.sem_flg = SEM_UNDO;

    int resultado = semop (this->id, &operacion, 1);
    if(resultado == -1){
        std::cerr << "error en wait 0 en "<< id << std::strerror(errno) <<std::endl;
    }
    return resultado;
}

int Semaforo::debug (const int id) const {
    return semctl(this->id, id, GETVAL);
}

int Semaforo::pWait(const int id) const {
    return this->pWait(id, 1);
}

int Semaforo::pWait(const int id, const int num) const {
	struct sembuf operacion;

	operacion.sem_num = id;	// numero de semaforo
	operacion.sem_op  = -num;	// restar 1 al semaforo
	operacion.sem_flg = SEM_UNDO;

	int resultado = semop ( this->id,&operacion,1 );
    if(resultado == -1){
        std::cerr << "error en p (wait) "<< id << std::strerror(errno) <<std::endl;
    }
	return resultado;
}

int Semaforo::vSignal(const int id) const {
    return this->vSignal(id, 1);
}

int Semaforo::vSignal(const int id, const int num) const {
	struct sembuf operacion;

	operacion.sem_num = id;	// numero de semaforo
	operacion.sem_op  = num;	// sumar 1 al semaforo
	operacion.sem_flg = SEM_UNDO;

	int resultado = semop ( this->id,&operacion,1 );
    if(resultado == -1){
        std::cerr << "error en v (sinal) "<< id << std::strerror(errno) <<std::endl;
    }
	return resultado;
}

void Semaforo::eliminar () const {
	semctl(this->id, 0, IPC_RMID );
}
