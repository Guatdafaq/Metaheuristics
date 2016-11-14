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

using namespace std;

namespace mh {

TSP::TSP() {
}

TSP::~TSP() {
}

int TSP::reservarMemoriaInstancia() {
	vector<int> aux;
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

}
