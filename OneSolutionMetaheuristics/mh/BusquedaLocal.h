/*
 * BusquedaLocal.h
 *
 *  Created on: 06/03/2015
 *      Author: pedroa
 */

// Manejo de errores
// -1 error al abrir el fichero
// -2 error al leer el formato del fichero
// -3 error en la reserva de memoria
#ifndef BUSQUEDALOCAL_H
#define BUSQUEDALOCAL_H

namespace mh {

template<typename DATOS_SOLUCION>
class BusquedaLocal{
public:
	virtual DATOS_SOLUCION aplicarBusquedaLocal(DATOS_SOLUCION sol,  bool firstImprovement, int iterRelaTamano)=0;
protected:
	~BusquedaLocal(void){};
};

}

#endif /* BUSQUEDALOCAL_H */
