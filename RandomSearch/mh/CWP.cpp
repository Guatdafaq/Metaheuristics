 /*
 * CWP.cpp
 *
 *  Created on: 06/02/2013
 *      Author: pedroa
 */

#include "CWP.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>  // Para establecer la semilla srand() y generar números aleatorios rand()
#include <limits>

using namespace std;

namespace mh {

CWP::CWP() {
}

CWP::~CWP() {
}

int CWP::reservarMemoriaInstancia() {
	vector<bool> aux;
	aux.resize(data.n, 0);
	for (int i=0; i<data.n; i++){
		data.d.push_back(aux);
	}
	return 1;
}

void CWP::liberarMemoriaInstancia() {
	data.d.erase(data.d.begin(), data.d.end());
}

void CWP::liberarMemoriaSolucion(struct datosSolucionCWP &sol){
	sol.x.erase(sol.x.begin(), sol.x.end());
}

int CWP::leerInstancia(char *archivo) {

	char cadena[100];
	int n, m, i, j, aux;

	ifstream f(archivo);

	if(!f){
		cout<<"Error. No se ha abierto correctamente el archivo."<<endl;
		return 0;
	}else{
		f.getline(cadena, 100);
		sscanf(cadena, "%d %d %d", &n, &aux, &m);
		data.n=n;
		data.m=m;
		reservarMemoriaInstancia();
		while(!f.eof()){
			f.getline(cadena, 50);
			sscanf(cadena, "%d %d", &i, &j);
			data.d[i-1][j-1]=1;
		}
	}
	return 1;
}


float CWP::evaluarSolucion(struct datosSolucionCWP sol){
	float c=0;

	for (int i=0; i<data.n; i++){
		for(int j=i+1; j<data.n; j++){
			if(data.d[sol.x[i]][sol.x[j]])
				c++;
		}
		for (int j=0; j<i; j++){
			for (int k=i+1; k<data.n; k++){
				if(data.d[sol.x[j]][sol.x[k]])
					c++;
			}
		}
	}
	return c;
}

struct datosSolucionCWP  CWP::generarSolucionRandom() {
	struct datosSolucionCWP sol;
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

void CWP::imprimirSolucion(struct datosSolucionCWP sol) {
	for(int i=0; i<data.n; i++){
		cout << sol.x[i] << " ";
	}
}

void CWP::imprimirInstancia() {
	cout << "{";
	for (int i=0; i<data.n; i++){
		for (int j=0; j<data.n; j++){
			if(data.d[i][j]==1)
			cout << "(" << i << ", " << j << ")";
		}
	}
	cout << "}";
}

}
