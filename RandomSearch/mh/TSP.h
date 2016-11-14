/*
 * TSP.h
 *
 *  Created on: 06/02/2013
 *      Author: pedroa
 */

#ifndef TSP_H_
#define TSP_H_

#include "Problema.h"

using namespace std;

namespace mh {

struct datosInstanciaTSP{
	int n;
	vector < vector <int> > d;
};

struct datosSolucionTSP{
	vector <int> x;
};

class TSP: public mh::Problema<struct datosInstanciaTSP,struct datosSolucionTSP> {

public:
	TSP();
	virtual ~TSP();
	int leerInstancia(char *archivo);
	float evaluarSolucion(struct datosSolucionTSP sol);
	struct datosSolucionTSP generarSolucionRandom();
	void imprimirSolucion(struct datosSolucionTSP  sol);
	void imprimirInstancia();
	void liberarMemoriaSolucion(struct datosSolucionTSP &sol);
private:
	int reservarMemoriaInstancia();
	void liberarMemoriaInstancia();
};

}

#endif /* TSP_H_ */
