#ifndef MEMORIACOMPARTIDA2_H_
#define MEMORIACOMPARTIDA2_H_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>
#include <string.h>
#include <iostream>
#include <errno.h>

template <class T> class MemoriaCompartida2 {

private:
	int	shmId;
	T*	ptrDatos;
	unsigned length;

	int	cantidadProcesosAdosados() const;

public:
	MemoriaCompartida2 ();
	void crear ( const std::string& archivo, const char letra, unsigned length );
	void liberar ();

	MemoriaCompartida2 ( const std::string& archivo, const char letra , unsigned length );
	MemoriaCompartida2 ( const MemoriaCompartida2& origen );
	~MemoriaCompartida2 ();
	MemoriaCompartida2<T>& operator= ( const MemoriaCompartida2& origen );
	void escribir ( unsigned index, const T& dato );
	T leer (unsigned index) const;
};

template <class T> MemoriaCompartida2<T>::MemoriaCompartida2 ():shmId(0),ptrDatos(NULL), length(1) {
}

template <class T> void MemoriaCompartida2<T>::crear ( const std::string& archivo,const char letra, unsigned length) {
	key_t clave = ftok ( archivo.c_str(),letra );

	if ( clave > 0 ) {
		this ->length = length;
		this->shmId = shmget ( clave,sizeof(T)* length,0644|IPC_CREAT );

		if ( this->shmId > 0 ) {
			void* tmpPtr = shmat ( this->shmId,NULL,0 );
			if ( tmpPtr != (void*) -1 ) {
				this->ptrDatos = static_cast<T*> (tmpPtr);
			} else {
				std::string mensaje = std::string("Error en shmat(): ") + std::string(strerror(errno));
				throw mensaje;
			}
		} else {
			std::string mensaje = std::string("Error en shmget(): ") + std::string(strerror(errno));
			throw mensaje;
		}
	} else {
		std::string mensaje = std::string("Error en ftok(): ") + std::string(strerror(errno));
		throw mensaje;
	}
}

template <class T> void MemoriaCompartida2<T>::liberar() {
	int errorDt = shmdt ( (void *) this->ptrDatos );

	if ( errorDt != -1 ) {
		int procAdosados = this->cantidadProcesosAdosados ();
		if ( procAdosados == 0 ) {
			shmctl ( this->shmId,IPC_RMID,NULL );
		}
	} else {
		std::string mensaje = std::string("Error en shmdt(): ") + std::string(strerror(errno));
		throw mensaje;
	}
}

//parametrized constructer with default arguments
template <class T> MemoriaCompartida2<T>::MemoriaCompartida2 ( const std::string& archivo, const char letra, unsigned length):shmId(0),ptrDatos(NULL) {
	key_t clave = ftok ( archivo.c_str(),letra );

	if ( clave > 0 ) {
		this ->length = length;
		this->shmId = shmget ( clave,sizeof(T)*length,0644|IPC_CREAT );

		if ( this->shmId > 0 ) {
			void* tmpPtr = shmat ( this->shmId,NULL,0 );
			if ( tmpPtr != (void*) -1 ) {
				this->ptrDatos = static_cast<T*> (tmpPtr);
			} else {
				std::string mensaje = std::string("Error en shmat(): ") + std::string(strerror(errno));
				throw mensaje;
			}
		} else {
			std::string mensaje = std::string("Error en shmget(): ") + std::string(strerror(errno));
			throw mensaje;
		}
	} else {
		std::string mensaje = std::string("Error en ftok(): ") + std::string(strerror(errno));
		throw mensaje;
	}
}

//constructor por copia
template <class T> MemoriaCompartida2<T>::MemoriaCompartida2 ( const MemoriaCompartida2& origen )
:shmId(origen.shmId), length(origen.length) {
	void* tmpPtr = shmat ( origen.shmId,NULL,0 );

	if ( tmpPtr != (void*) -1 ) {
		this->ptrDatos = static_cast<T*> (tmpPtr);

	} else {
		std::string mensaje = std::string("Error en shmat(): ") + std::string(strerror(errno));
		throw mensaje;
	}
}

//deconstructor
template <class T> MemoriaCompartida2<T>::~MemoriaCompartida2 () {
	int errorDt = shmdt ( static_cast<void*> (this->ptrDatos) );

	if ( errorDt != -1 ) {
		int procAdosados = this->cantidadProcesosAdosados ();
		if ( procAdosados == 0 ) {
			shmctl ( this->shmId,IPC_RMID,NULL );
		}
	} else {
		std::cerr << "Error en shmdt(): " << strerror(errno) << std::endl;
	}
}

//operador asignacion
template <class T> MemoriaCompartida2<T>& MemoriaCompartida2<T>::operator= ( const MemoriaCompartida2& origen ) {
	this->shmId = origen.shmId;
	this ->length = origen.length;
	void* tmpPtr = shmat ( this->shmId,NULL,0 );

	if ( tmpPtr != (void*) -1 ) {
		this->ptrDatos = static_cast<T*> (tmpPtr);
	} else {
		std::string mensaje = std::string("Error en shmat(): ") + std::string(strerror(errno));
		throw mensaje;
	}

	return *this;
}

template <class T> void MemoriaCompartida2<T>::escribir (const unsigned index,  const T& dato ) {
	if(index >= length){
		std::string mensaje = std::string("out of shared memory bound: ") + std::string(strerror(errno));
		throw mensaje;
	}
	*(this->ptrDatos + (sizeof(T) * index)) = dato;
}

template <class T> T MemoriaCompartida2<T>::leer(const unsigned index) const {
	if(index >= length){
		std::string mensaje = std::string("out of shared memory bound: ") + std::string(strerror(errno));
		throw mensaje;
	}
	return *(this->ptrDatos + (sizeof(T) * index ));
}

template <class T> int MemoriaCompartida2<T> :: cantidadProcesosAdosados () const {
	shmid_ds estado;
	shmctl ( this->shmId,IPC_STAT,&estado );
	return estado.shm_nattch;
}

#endif
