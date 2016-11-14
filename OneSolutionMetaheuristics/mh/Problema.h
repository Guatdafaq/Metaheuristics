/*
 * Problema.h
 *
 *  Created on: 06/02/2013
 *  Updated on: 12/02/2015
 *      Author: pedroa
 */

// Manejo de errores
// -1 error al abrir el fichero
// -2 error al leer el formato del fichero
// -3 error en la reserva de memoria
#ifndef PROBLEMA_H_
#define PROBLEMA_H_
#include <vector>

namespace mh {
// Plantilla de clase
// Establece la estructura de las clases que representarán a los problemas (MMDP, CWP, TSP y CPH)
// Estas clases deberán heredar de Problema y definir los métodos virtuales necesarios
// Cada una de estas clases deberá definir dos estructuras, una para los datos de la instancia
// y otra para los datos de la solución. Estas estructuras son las que aparecen como argumentos
// en la plantilla.
template<typename DATOS_INSTANCIA, typename DATOS_SOLUCION>
class Problema {
public:
	virtual ~Problema(){};
	virtual int leerInstancia(char * archivo)=0;
	virtual float evaluarSolucion(DATOS_SOLUCION sol)=0;
	virtual DATOS_SOLUCION generarSolucionRandom()=0;
	virtual DATOS_SOLUCION generarVecinos(DATOS_SOLUCION sol, int p, int cont)=0;
	virtual bool aceptacion(DATOS_SOLUCION sol, DATOS_SOLUCION sol2)=0;
	DATOS_SOLUCION aplicarBusquedaLocal(DATOS_SOLUCION sol, bool firstImprovement, int iterRelaTamano);
	DATOS_SOLUCION aplicarEnfriamientoSimulado(DATOS_SOLUCION sol, float tFinal, float gamma, int iterRelaTamano);
	virtual void imprimirSolucion(DATOS_SOLUCION sol)=0;
	virtual void imprimirInstancia()=0;
	virtual void liberarMemoriaSolucion(DATOS_SOLUCION &sol)=0;
protected:
	DATOS_INSTANCIA data;
	virtual int reservarMemoriaInstancia()=0;
	virtual void liberarMemoriaInstancia()=0;
};

}

#endif /* PROBLEMA_H_ */
