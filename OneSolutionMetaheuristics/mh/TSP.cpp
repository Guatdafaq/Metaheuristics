/*
 * TSP.cpp
 *
 *  Created on: 06/02/2013
 *      Author: pedroa
 */

#include "TSP.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>  // Para establecer la semilla srand() y generar números aleatorios rand()
#include <limits>
#include <algorithm>
#include <cmath>

using namespace std;

namespace mh {

TSP::TSP() {
}

TSP::~TSP() {
}

int TSP::reservarMemoriaInstancia() {
	vector<float> aux;
	aux.resize(data.n, 0.0);
	for (int i=0; i<data.n; i++){
		data.d.push_back(aux);
	}
	return 1;
}

void TSP::liberarMemoriaInstancia() {
	data.d.erase(data.d.begin(), data.d.end());
}

void TSP::liberarMemoriaSolucion(struct datosSolucionTSP &sol){
	sol.x.erase(sol.x.begin(), sol.x.end());
}

int TSP::getN(){
	return data.n;
}

int TSP::leerInstancia(char *archivo) {

	char cadena[50];
	int n, i=0, j=0;
	int distancia;

	ifstream f(archivo);

	if(!f){
		cout<<"Error. No se ha abierto correctamente el archivo."<<endl;
		return 0;
	}else{
		f.getline(cadena, 200);
		sscanf(cadena, "%d", &n);
		data.n=n;
		reservarMemoriaInstancia();
		for (i=0; i<data.n;i++){
			for (j=0; j<data.n;j++){
				f >> distancia;
				data.d[i][j]=distancia;
			}

		}
	}
	return 1;
}


float TSP::evaluarSolucion(struct datosSolucionTSP sol){
	float suma=0.0;

	for (int i=0; i<data.n; i++){
		suma+=data.d[sol.x[i]][sol.x[(i+1)%(data.n)]];
	}

	return suma;
}

struct datosSolucionTSP  TSP::generarSolucionRandom() {
	struct datosSolucionTSP sol;
    int total = data.n;
    sol.x.resize(total, 0);
    vector<int> numerosPorElegir;
    // Inicializar la lista de elecciones posibles
    for(int i = 0; i < total; i++)
            numerosPorElegir.push_back(i);

    for(int i=0; i < data.n; i++){
    	int numeroElegido = rand() % (total-i);
        // Recordar el numero elegido
        sol.x[i]=numerosPorElegir[numeroElegido];
        // Ponemos en numeros por elegir, el ultimo que era valido, asi
        // son todos validos hasta data.n-i-1
        numerosPorElegir[numeroElegido]=numerosPorElegir[total-i-1];
    }
	return sol;
}

void TSP::imprimirSolucion(struct datosSolucionTSP sol) {
	cout << "{";
	for(int i=0; i<data.n; i++){
		cout << sol.x[i] << ", ";
	}
	cout << "}" << endl;
}

void TSP::imprimirInstancia() {
	for (int i=0; i<data.n; i++){
		for (int j=0; j<data.n; j++){
			cout << data.d[i][j] << " ";
		}
		cout << endl;
	}
}

struct datosSolucionTSP TSP::generarVecinos1(datosSolucionTSP sol, int p, int cont, vector <int> cv, int cambio){
	//p=0 BLf; p=1 BLb; p=2 ES
	int aux, candidato, totalBeta=data.n*0.5;
	//Generación de vecinos
	if (p==0 || p==2){
		candidato=cont%(totalBeta);
		aux=sol.x[(cv[candidato]+1)%totalBeta];
		sol.x[(cv[candidato]+1)%totalBeta]=sol.x[cambio];
		sol.x[cambio]=aux;
	}else if(p==1){
		candidato=cont%(cv.size());
		aux=sol.x[(cv[candidato]+1)%data.n];
		sol.x[(cv[candidato]+1)%data.n]=sol.x[cambio];
		sol.x[cambio]=aux;
	}
	return sol;
}
bool TSP::aceptacion(datosSolucionTSP sol, datosSolucionTSP sol2){

	int min, min2;

		min=evaluarSolucion(sol);
		min2=evaluarSolucion(sol2);

		if (min2<min)
			return 1;
		else
			return 0;
}

struct datosSolucionTSP TSP::aplicarBusquedaLocal(struct datosSolucionTSP sol, bool firstImprovement, int iterRelaTamano){
	int p, cambio, totalBeta=data.n*0.5, soluciones=0;
	vector <int> cv, numerosPorElegir, cambios;
	struct datosSolucionTSP sol2;
	if (!firstImprovement){
		p=1;
		cv=listaCandidatos(sol, p);
		numerosPorElegir=sol.x;
		for(int i=0; i < totalBeta && soluciones < iterRelaTamano; i++){
			for (int t=0; t < data.n; t++){
				int numeroElegido = rand() % ((data.n)-t);
				// Recordar el numero elegido
				cambio=numerosPorElegir[numeroElegido];
				// Ponemos en numeros por elegir, el ultimo que era valido, asi
				// son todos validos hasta data.n-i-1
				numerosPorElegir[numeroElegido]=numerosPorElegir[data.n-t-1];
				if (cambio!=((cv[i%totalBeta]-1)%data.n) && cambio!=((cv[i%totalBeta]+1)%data.n) && cambio!=cv[i%totalBeta]){
					sol2 = generarVecinos1(sol, p, cv[i%totalBeta], cv, cambio);
					soluciones++;
					if (aceptacion(sol, sol2))
						sol=sol2;
				}
			}
		return sol;
		}
	}else{
		p=0;
		cv=listaCandidatos(sol, p);
		for (int i=0; i < totalBeta && soluciones < iterRelaTamano; i++){
			for (int j=0; j < data.n; j++){
				if (j!=((cv[i%totalBeta]-1)%data.n) && j!=((cv[i%totalBeta]+1)%data.n) && j!=cv[i%totalBeta]){
					sol2 = generarVecinos1(sol, p, cv[i%totalBeta], cv, cambios[j]);
					soluciones++;
					if (aceptacion(sol, sol2))
						return sol2;
				}
			}
		}
		return sol;
	}

	return sol;
}
struct datosSolucionTSP TSP::aplicarEnfriamientoSimulado(struct datosSolucionTSP sol, float tFinal, float gamma, int iterRelaTamano){

	int p=2, incremento, mejoras=0, soluciones=0, nMejoras=0.1*data.n, acabado=0;
	int i, c;
	vector <int> cambios, cv;
	struct datosSolucionTSP sol2, mejorSol=sol, solActual=sol;
	cv=listaCandidatos(sol, p);
	float tActual;
	float valorActual=evaluarSolucion(sol);
	tActual=0.001*valorActual/(-log(0.3));

	do{
		do{
				//Bucle generación de vecinos
				cv=listaCandidatos(solActual, p);
				i=rand()%cv.size();
				for (int j=0; j < data.n; j++){
					if (j!=((cv[i]-1)%data.n) && j!=((cv[i]+1)%data.n) && j!=cv[i])
						cambios.push_back(j);
				}
				c=rand()%cambios.size();
				sol2=generarVecinos1(solActual, p, cv[i], cv, cambios[c]);
				valorActual=evaluarSolucion(solActual);
				soluciones++;
				incremento=valorActual-evaluarSolucion(sol2);
				if(incremento<0 || (rand()%100)/100 <= exp(-incremento*evaluarSolucion(sol)/tActual))
					solActual=sol2;
				if(evaluarSolucion(sol2)>evaluarSolucion(mejorSol)){
					mejorSol=sol2;
					mejoras++;
				}


		}while(soluciones<data.n*5 && mejoras<nMejoras && acabado==0 && soluciones<iterRelaTamano);

		tActual=tActual*gamma;

	}while(tActual<tFinal && soluciones<iterRelaTamano && evaluarSolucion(mejorSol)!= evaluarSolucion(solActual));

	return mejorSol;

}

vector <int> TSP::listaCandidatos(datosSolucionTSP sol, int p){

	vector <int> d, d2, cv;
	int totalBeta=0.5*data.n;
	//p=0 BLf; p=1 BLb; p=2 ES
	//Elección de candidatos
	for (int i=0; i<data.n; i++){
		d.push_back(data.d[i][i+1%data.n]);
	}
	d2=d;
	sort(d.begin(), d.end(), greater<int>());
	if (p==0 || p==2){
		for (int i=0; i<totalBeta; i++){
			for (int j=0; j<data.n; j++){
				if(d[i]==d2[j])
					cv.push_back(j);
			}
		}
	}else{
		for (int i=0; i<data.n; i++){
			for (int j=0; j<data.n; j++){
				if(d[i]==d2[j])
					cv.push_back(j);
			}
		}
	}

	return cv;
}

struct datosSolucionTSP TSP::generarVecinos(struct datosSolucionTSP sol, int p, int cont){return sol;}

}
