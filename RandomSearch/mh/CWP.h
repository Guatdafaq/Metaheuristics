/*
 * MMDP.h
 *
 *  Created on: 06/02/2013
 *      Author: pedroa
 */

/*
 * CWP.h
 *
 *  Created on: 06/02/2013
 *      Author: pedroa
 */

#ifndef CWP_H_
#define CWP_H_

#include "Problema.h"

using namespace std;

namespace mh {

struct datosInstanciaCWP{
	int n;
	int m;
	vector < vector <bool> > d;
};

struct datosSolucionCWP{
	vector <int> x;
};

class CWP: public mh::Problema<struct datosInstanciaCWP,struct datosSolucionCWP> {

public:
	CWP();
	virtual ~CWP();
	int leerInstancia(char *archivo);
	float evaluarSolucion(struct datosSolucionCWP sol);
	struct datosSolucionCWP generarSolucionRandom();
	void imprimirSolucion(struct datosSolucionCWP  sol);
	void imprimirInstancia();
	void liberarMemoriaSolucion(struct datosSolucionCWP &sol);
private:
	int reservarMemoriaInstancia();
	void liberarMemoriaInstancia();
};

}

#endif /* CWP_H_ */
