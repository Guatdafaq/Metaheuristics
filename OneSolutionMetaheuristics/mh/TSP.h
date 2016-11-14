/*
 * TSP.h
 *
 *  Created on: 06/02/2013
 *      Author: pedroa
 */

#ifndef TSP_H_
#define TSP_H_

#include "Problema.h"
#include "BusquedaLocal.h"
#include "EnfriamientoSimulado.h"

using namespace std;

namespace mh {

struct datosInstanciaTSP{
	int n;
	vector < vector <float> > d;
};

struct datosSolucionTSP{
	vector <int> x;
};

class TSP: 	public mh::Problema<struct datosInstanciaTSP,struct datosSolucionTSP>,
			public mh::EnfriamientoSimulado<struct datosSolucionTSP>,
			public mh::BusquedaLocal<struct datosSolucionTSP>{

public:
	TSP();
	virtual ~TSP();
	int leerInstancia(char *archivo);
	int getN();
	float evaluarSolucion(struct datosSolucionTSP sol);
	struct datosSolucionTSP generarSolucionRandom();
	void imprimirSolucion(struct datosSolucionTSP  sol);
	void imprimirInstancia();
	void liberarMemoriaSolucion(struct datosSolucionTSP &sol);
	struct datosSolucionTSP generarVecinos(struct datosSolucionTSP sol, int p, int cont);
	struct datosSolucionTSP generarVecinos1(datosSolucionTSP sol, int p, int cont, vector <int> cv, int cambio);
	bool aceptacion(datosSolucionTSP sol, datosSolucionTSP sol2);
	struct datosSolucionTSP aplicarBusquedaLocal(struct datosSolucionTSP sol, bool firstImprovement, int iterRelaTamano);
	struct datosSolucionTSP aplicarEnfriamientoSimulado(struct datosSolucionTSP sol, float tFinal, float gamma, int iterRelaTamano);
	vector <int> listaCandidatos(datosSolucionTSP sol, int p);
private:
	int reservarMemoriaInstancia();
	void liberarMemoriaInstancia();
};

}

#endif /* TSP_H_ */
