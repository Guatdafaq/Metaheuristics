/*
 * MMDP.h
 *
 *  Created on: 06/02/2013
 *      Author: pedroa
 */

#ifndef MMDP_H_
#define MMDP_H_

#include "Problema.h"
#include "BusquedaLocal.h"
#include "EnfriamientoSimulado.h"


using namespace std;

namespace mh {

struct datosInstanciaMMDP{
	int n;
	int m;
	vector < vector <float> > d;
};

struct datosSolucionMMDP{
	vector <bool> x;
};

class MMDP: public mh::Problema<struct datosInstanciaMMDP,struct datosSolucionMMDP>,
			public mh::EnfriamientoSimulado<struct datosSolucionMMDP>,
            public mh::BusquedaLocal<struct datosSolucionMMDP>{

public:
	MMDP();
	virtual ~MMDP();
	int leerInstancia(char *archivo);
	int getN();
	float evaluarSolucion(struct datosSolucionMMDP sol);
	struct datosSolucionMMDP generarSolucionRandom();
	void imprimirSolucion(struct datosSolucionMMDP  sol);
	void imprimirInstancia();
	void liberarMemoriaSolucion(struct datosSolucionMMDP &sol);
	struct datosSolucionMMDP generarVecinos(struct datosSolucionMMDP sol, int p, int cont);
	bool aceptacion(struct datosSolucionMMDP sol, struct datosSolucionMMDP sol2);
	struct datosSolucionMMDP aplicarBusquedaLocal(struct datosSolucionMMDP sol, bool firstImprovement, int iterRelaTamano);
	struct datosSolucionMMDP aplicarEnfriamientoSimulado(struct datosSolucionMMDP sol, float tFinal, float gamma, int iterRelaTamano);
private:
	int reservarMemoriaInstancia();
	void liberarMemoriaInstancia();

};

}

#endif /* MMDP_H_ */
