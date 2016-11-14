/*
 * MMDP.cpp
 *
 *  Created on: 06/02/2013
 *      Author: pedroa
 */

#include "MMDP.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>  // Para establecer la semilla srand() y generar números aleatorios rand()
#include <limits>
#include <cmath>

using namespace std;

namespace mh {

MMDP::MMDP() {
}

MMDP::~MMDP() {
}

int MMDP::reservarMemoriaInstancia() {
	vector<float> aux;
	aux.resize(data.n, 0.0);
	for (int i=0; i<data.n; i++){
		data.d.push_back(aux);
	}
	return 1;
}

int MMDP::getN(){
	return data.n;
}

void MMDP::liberarMemoriaInstancia() {
	data.d.erase(data.d.begin(), data.d.end());
}

void MMDP::liberarMemoriaSolucion(struct datosSolucionMMDP &sol){
	sol.x.erase(sol.x.begin(), sol.x.end());
}

int MMDP::leerInstancia(char *archivo) {

	char cadena[30];
	int n, m, i, j;
	float distancia;

	ifstream f(archivo);

	if(!f){
		cout<<"Error. No se ha abierto correctamente el archivo."<<endl;
		return 0;
	}else{
		f.getline(cadena, 50);
		sscanf(cadena, "%d %d", &n, &m);
		data.n=n;
		data.m=m;
		reservarMemoriaInstancia();
		while(!f.eof()){
			f.getline(cadena, 50);
			sscanf(cadena, "%d %d %f", &i, &j, &distancia);
			data.d[i][j]=distancia;
		}
	}
	return 1;
}


float MMDP::evaluarSolucion(struct datosSolucionMMDP sol){
	float minimo=1000000.0;

	for (int i=0; i<data.n; i++){
		if(sol.x[i]==1){
			for(int j=i+1; j<data.n; j++){
				if (sol.x[j]==1){
					if (data.d[i][j] < minimo)
						minimo=data.d[i][j];
				}
			}
		}
	}
	return minimo;
}

struct datosSolucionMMDP  MMDP::generarSolucionRandom() {
	struct datosSolucionMMDP sol;
    int total = data.n;
    sol.x.resize(total, 0);
    vector<int> numerosPorElegir;
    // Inicializar la lista de elecciones posibles
    for(int i = 0; i < total; i++)
            numerosPorElegir.push_back(i);

    for(int i=0; i < data.m; i++){
    	int numeroElegido = rand() % (total-i);
        // Recordar el numero elegido
        sol.x[i]=numerosPorElegir[numeroElegido];
        // Ponemos en numeros por elegir, el ultimo que era valido, asi
        // son todos validos hasta data.n-i-1
        numerosPorElegir[numeroElegido]=numerosPorElegir[total-i-1];
    }
	return sol;
}

void MMDP::imprimirSolucion(struct datosSolucionMMDP sol) {
	for(int i=0; i<data.n; i++){
		cout << sol.x[i] << " ";
	}
}

void MMDP::imprimirInstancia() {
	for (int i=0; i<data.n; i++){
		for (int j=0; j<data.n; j++){
			cout << data.d[i][j] << " ";
		}
		cout << endl;
	}
}

struct datosSolucionMMDP MMDP::generarVecinos(struct datosSolucionMMDP sol, int p, int cont){

	int c=0;
	for (int i=0; i<data.n; i++){
		if (sol.x[i]==1){
			c++;
			if(c==cont){
				for(int j=p; j<data.n; j++){
					if (sol.x[j]==0){
						sol.x[i]=0;
						sol.x[j]=1;
						return sol;
					}
				}
			}
		}

	}
	return sol;
}
bool MMDP::aceptacion(struct datosSolucionMMDP sol, struct datosSolucionMMDP sol2){

	int min, min2;

	min=evaluarSolucion(sol);
	min2=evaluarSolucion(sol2);

	if (min2>min)
		return 1;
	else
		return 0;
}

struct datosSolucionMMDP MMDP::aplicarBusquedaLocal(struct datosSolucionMMDP sol, bool firstImprovement, int iterRelaTamano){
	int cont=0;
	if (firstImprovement){
		for (int i=0; i<50*data.n; i++){
			if (i%data.n==0)
				cont++;
			struct datosSolucionMMDP sol2=generarVecinos(sol, i%data.n, cont%data.m);
			if(aceptacion(sol, sol2))
				return sol2;
		}
	}else{
		for (int i=0; i<50*data.n; i++){
			if (i%data.n==0)
				cont++;
			struct datosSolucionMMDP sol2=generarVecinos(sol, i%data.n, cont%data.m);
			if(aceptacion(sol, sol2))
				sol=sol2;
		}
		return sol;
	}
	return sol;
}
struct datosSolucionMMDP MMDP::aplicarEnfriamientoSimulado(struct datosSolucionMMDP sol, float tFinal, float gamma, int iterRelaTamano){

	struct datosSolucionMMDP mejorSol, solActual;
	int acabado=0, i=0, mejoras=0, soluciones=0, cont=0;
	float tActual;
	int nMejoras=data.n*(0.1);
	int incremento;

	float valorActual=evaluarSolucion(sol);
	tActual=10*valorActual/(-log(0.3));
	mejorSol=sol;
	do{
		do{
			if (i%data.n==0)
				cont++;
			struct datosSolucionMMDP sol2=generarVecinos(solActual, i%data.n, cont%data.m);
			valorActual=evaluarSolucion(solActual);
			soluciones++;
			incremento=valorActual-evaluarSolucion(sol2);
			if(incremento<0 || (rand()%100)/100 <= exp(-incremento*evaluarSolucion(sol)/tActual))
				solActual=sol2;
			if(evaluarSolucion(sol2)>evaluarSolucion(mejorSol)){
				mejorSol=sol2;
				mejoras++;
			}
			if (i%data.n==0 && cont==data.m)
				acabado=1;
			i++;

		}while(i<data.n && mejoras<nMejoras && acabado==0 && soluciones<iterRelaTamano);
		tActual=tActual*gamma;
	}while(tActual<tFinal && soluciones<iterRelaTamano);
	return mejorSol;
}

}

