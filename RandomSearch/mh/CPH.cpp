
/*
 * CPH.cpp
 *
 *  Created on: 06/02/2013
 *      Author: pedroa
 */

#include "CPH.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>  // Para establecer la semilla srand() y generar números aleatorios rand()
#include <limits>
#include <cmath>

using namespace std;

namespace mh {

CPH::CPH() {
}

CPH::~CPH() {
}

int CPH::reservarMemoriaInstancia() {
	nodo n;
	data.d.resize(data.n, n);
	data.sumad.resize(data.n, 0);
	return 1;
}

void CPH::liberarMemoriaInstancia() {
	data.d.erase(data.d.begin(), data.d.end());
}

void CPH::liberarMemoriaSolucion(struct datosSolucionCPH &sol){
	sol.x.erase(sol.x.begin(), sol.x.end());
	sol.y.erase(sol.y.begin(), sol.y.end());
}

int CPH::leerInstancia(char *archivo) {

	char cadena[30];
	int n, p, c, i, x, y, demanda;

	ifstream f(archivo);

	if(!f){
		cout<<"Error. No se ha abierto correctamente el archivo."<<endl;
		return 0;
	}else{
		f.getline(cadena, 50);
		sscanf(cadena, "%d %d %d", &n, &p, &c);
		data.n=n;
		data.p=p;
		data.c=c;
		reservarMemoriaInstancia();
		while(!f.eof()){
			f.getline(cadena, 50);
			sscanf(cadena, "%d %d %d %d", &i, &x, &y, &demanda);
			data.d[i-1].x=x;
			data.d[i-1].y=y;
			data.d[i-1].demanda=demanda;
		}
	}
	return 1;
}


float CPH::evaluarSolucion(struct datosSolucionCPH sol){
	float distancia=0;

	for (int i=0; i<data.n; i++){
		for (int j=0; j<data.n; j++){
			if (sol.y[j]!=1)
				return 1000000.0;
			if (data.sumad[j]>data.c)
				return 1000000.0;
			if (sol.x[i][j]==1)
				distancia+=sqrt(pow(data.d[i].x-data.d[j].x,2) + pow(data.d[i].y-data.d[j].y, 2));
		}
	}

	return distancia;
}

struct datosSolucionCPH  CPH::generarSolucionRandom() {
	struct datosSolucionCPH sol;
    int total = data.n;
    int contador=0;
    sol.y.resize(total, 0);
    vector<bool> aux;
    	aux.resize(data.n, 0);
    	for (int i=0; i<data.n; i++){
    		sol.x.push_back(aux);
    	}
    vector<int> numerosPorElegir, numerosPorElegir2 ;
    // Inicializar la lista de elecciones posibles
    for(int i = 0; i < total; i++){
            numerosPorElegir.push_back(i);
    		numerosPorElegir2.push_back(i);
    }

    for(int i=0; i < data.p; i++){
    	int numeroElegido = rand() % (total-i);
        // Recordar el numero elegido
        sol.y[numerosPorElegir[numeroElegido]]=1;
        int numeroElegido1 = rand() % (data.p);
        sol.x[numerosPorElegir[numeroElegido]][numerosPorElegir2[numeroElegido1]]=1;
        data.sumad[numerosPorElegir2[numeroElegido1]]+=data.d[numerosPorElegir[numeroElegido]].demanda;
        // Ponemos en numeros por elegir, el ultimo que era valido, asi
        // son todos validos hasta data.n-i-1
        numerosPorElegir[numeroElegido]=numerosPorElegir[total-i-1];
        numerosPorElegir2[numeroElegido1]=numerosPorElegir2[total-i-1];
    }
    for(int i=0; i < data.n; i++){
       	int numeroElegido = rand() % (total-i);
           // Recordar el numero elegido

           int numeroElegido1 = rand() % (data.p);
           for (int j=0; j<data.n; j++){
        	   if (sol.y[j])
        		   contador++;
        	   if (contador==numeroElegido1){
        		   sol.x[numerosPorElegir[numeroElegido]][numerosPorElegir2[numeroElegido1]]=1;
        		   data.sumad[numerosPorElegir2[numeroElegido1]]+=data.d[numerosPorElegir[numeroElegido]].demanda;
        	   }
           }

           // Ponemos en numeros por elegir, el ultimo que era valido, asi
           // son todos validos hasta data.n-i-1
           numerosPorElegir[numeroElegido]=numerosPorElegir[total-i-1];
           contador=0;
    }


	return sol;
}

void CPH::imprimirSolucion(struct datosSolucionCPH sol) {
	cout << "Concentradores: " << endl;
	for(int i=0; i<data.n; i++){
		cout << sol.y[i] << " ";
	}
}

void CPH::imprimirInstancia() {
	for (int i=0; i<data.n; i++){
		cout << data.d[i].x << " " << data.d[i].y << " " << data.d[i].demanda << endl;
	}
}

}
