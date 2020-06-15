#ifndef MEMORIACOMPARTIDA_H_
#define MEMORIACOMPARTIDA_H_

#define LETRA			'a'
#define READ_WRITE		0644
#define SHM_OK			 0
#define	ERROR   		-1
#define	ERROR_FTOK		-2
#define ERROR_SHMGET	-3
#define	ERROR_SHMAT		-4

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>
#include <cerrno>
#include <iostream>


template <class T> class MemoriaCompartida {

private:
    int shmId;
    T*	ptrDatos;
    size_t  item_size;
    int length;
    int cantidadProcesosAdosados () const;

public:
    MemoriaCompartida ();
    ~MemoriaCompartida ();
    int crear (const std::string& archivo, const size_t item_size, int length);
    void liberar ();
    void escribir (const int index,const T process_data[]);
    void leer (const int index, T result[]) const ;
};

template <class T> MemoriaCompartida<T> :: MemoriaCompartida() : shmId(0), ptrDatos(NULL) {}
template <class T> MemoriaCompartida<T> :: ~MemoriaCompartida() {}

template <class T> int MemoriaCompartida<T>::crear( const std::string& archivo, const size_t item_size, int length) {
    if(length < 1){
        std::cerr << "length must be grater than 0 " << std::endl;
        return ERROR;
    }

    // generacion de la clave
    key_t clave = ftok ( archivo.c_str(), LETRA);
    if ( clave == -1 ) {
        std::cerr << "error en ftok " << std::strerror(errno) <<std::endl;
        return ERROR_FTOK;
    }

    // creacion de la memoria compartida
    this->item_size = item_size;
    this->length = length;
    this->shmId = shmget(clave, sizeof(T) * this->item_size * this->length, READ_WRITE | IPC_CREAT );
    if( this->shmId == -1 ) {
        std::cerr << "error en shmget " << std::strerror(errno) << std::endl;
        return ERROR_SHMGET;
    }

    // attach del bloque de memoria al espacio de direcciones del proceso
    void* ptrTemporal = shmat(this->shmId, NULL, 0);
    if( ptrTemporal == (void *) -1 ) {
        std::cerr << "error en shmat " << std::strerror(errno) << std::endl;
        return ERROR_SHMAT;
    }

    this->ptrDatos = static_cast<T*> (ptrTemporal);
    return SHM_OK;
}


template <class T> void MemoriaCompartida<T>::liberar () {
    // detach del bloque de memoria
    shmdt( static_cast<void*> (this->ptrDatos) );
    int procAdosados = this->cantidadProcesosAdosados ();

    if( procAdosados == 0 ) {
        shmctl(this->shmId, IPC_RMID, NULL );
    }
}

template <class T> void MemoriaCompartida<T>::escribir(const int index, const T process_data[]) {
    if( index < 0 || index >= this->length){
        std::string mensaje = std::string("out of shared memory bound: ") + std::string(strerror(errno));
        throw mensaje;
    }
    T *shared_data = this->ptrDatos + (sizeof(T) * this->item_size * index);
    memcpy(shared_data, process_data, this->item_size);
}

template <class T> void MemoriaCompartida<T>::leer(const int  index, T result[] ) const{
    if(index < 0 || index >= this->length){
        std::string mensaje = std::string("out of shared memory bound: ") + std::string(strerror(errno));
        throw mensaje;
    }
    T *shared_data = this->ptrDatos + (sizeof(T) * this->item_size * index);
    memcpy(result, shared_data, this->item_size);
}

template <class T> int MemoriaCompartida<T>::cantidadProcesosAdosados () const {
    shmid_ds estado;
    shmctl ( this->shmId,IPC_STAT,&estado );
    return estado.shm_nattch;
}


#endif /* MEMORIACOMPARTIDA_H_ */
