/*
 * CPH.h
 *
 *  Created on: 06/02/2013
 *      Author: pedroa
 */

#ifndef CPH_H_
#define CPH_H_

#include "Problema.h"
#include "AlgoritmoGenetico.h"

using namespace std;

namespace mh {
	struct nodo{
		int x;
		int y;
		int demanda;
	};

	struct datosInstanciaCPH{
		
		int n;
		int c;
		int p;
		float **distancia;
		struct nodo *nodos;
		int *demandaV;
	};

	struct datosSolucionCPH{
		
		int *x;
		float aptitud;

	};

	class CPH: 	public mh::Problema<struct datosInstanciaCPH,struct datosSolucionCPH>,
				public clases::AlgoritmoGenetico <struct datosSolucionCPH>{

	public:
		CPH();
		virtual ~CPH();
		int leerInstancia(char *archivo);
		float evaluarSolucion(struct datosSolucionCPH * sol);
		struct datosSolucionCPH * generarSolucionRandom();
		void imprimirSolucion(struct datosSolucionCPH  * sol);
		void imprimirInstancia();
		void liberarMemoriaSolucion(struct datosSolucionCPH * sol);
		struct datosSolucionCPH * aplicarAlgoritmoGenetico(int tamanoPoblacion, float pCruce, float pMutacion, int nEval, bool estacionario);
	private:
		int reservarMemoriaInstancia();
		void liberarMemoriaInstancia();
		void operadorMutacion(struct datosSolucionCPH * ind);
		void operadorCruce(struct datosSolucionCPH * ind1, struct datosSolucionCPH * ind2);
		struct datosSolucionCPH ** seleccionPorTorneo(struct datosSolucionCPH ** pob, int tamanoTorneo, int tamanoPoblacion, int numeroSeleccion);
		struct datosSolucionCPH ** seleccionPorRuleta(struct datosSolucionCPH ** pob, int tamanoPoblacion, int numeroSeleccion);
		struct datosSolucionCPH * mejorSolucionPoblacion(struct datosSolucionCPH ** pob, int tamanoPoblacion);
		struct datosSolucionCPH * reservaMemoriaSolucion();

	};

}

#endif /* CPH_H_ */
