#include "Semaforo.h"

Semaforo :: Semaforo( const std::string& nombre, const int cantidad,  const int valorInicial ):valorInicial(valorInicial) {
	key_t clave = ftok(nombre.c_str(), 'a');
	this->id = semget (clave, cantidad, 0666 | IPC_CREAT );
    this->cantidad = cantidad;
	this->inicializar ();
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


int Semaforo::waitZero (const int num) const {
    struct sembuf operacion;

    operacion.sem_num = num;	// numero de semaforo
    operacion.sem_op  = 0;	// espera hasta que el semaforo sea cero
    operacion.sem_flg = SEM_UNDO;

    int resultado = semop (this->id, &operacion, 1);
    return resultado;
}

int Semaforo::pWait(const int num) const {
	struct sembuf operacion;

	operacion.sem_num = num;	// numero de semaforo
	operacion.sem_op  = -1;	// restar 1 al semaforo
	operacion.sem_flg = SEM_UNDO;

	int resultado = semop ( this->id,&operacion,1 );
	return resultado;
}

int Semaforo::vSignal(const int num) const {
	struct sembuf operacion;

	operacion.sem_num = num;	// numero de semaforo
	operacion.sem_op  = 1;	// sumar 1 al semaforo
	operacion.sem_flg = SEM_UNDO;

	int resultado = semop ( this->id,&operacion,1 );
	return resultado;
}

void Semaforo::eliminar () const {
	semctl(this->id, 0, IPC_RMID );
}
