/*
 * EnfriamientoSimulado.h
 *
 *  Created on: 06/03/2015
 *      Author: pedroa
 */

// Manejo de errores
// -1 error al abrir el fichero
// -2 error al leer el formato del fichero
// -3 error en la reserva de memoria
#ifndef ENFRIAMIENTOSIMULADO_H_
#define ENFRIAMIENTOSIMULADO_H_

namespace mh {

template<typename DATOS_SOLUCION>
class EnfriamientoSimulado {
public:
	virtual DATOS_SOLUCION aplicarEnfriamientoSimulado(DATOS_SOLUCION sol, float tFinal, float gamma, int iterRelaTamano)=0;

protected:
	~EnfriamientoSimulado(void){};
};


}

#endif /* ENFRIAMIENTOSIMULADO_H_ */
