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

}

