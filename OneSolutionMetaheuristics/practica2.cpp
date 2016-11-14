//============================================================================
// Name        : practica1.cpp
// Author      : Pedro A. Gutiérrez
// Version     :
// Copyright   : Universidad de Córdoba
// Description : Primera práctica asignatura Metaheurísticas
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <ctime>    // Para cojer la hora time()
#include <cstdlib>  // Para establecer la semilla srand() y generar números aleatorios rand()
#include <string.h>
#include <cmath>
#include "mh/MMDP.h"
#include "mh/TSP.h"
#include "mh/Problema.h"

using namespace mh;
using namespace std;

int main(int argc, char **argv) {

	char* fvalue, *pvalue,* avalue;
	int fflag=0, sflag=0, pflag=0, aflag=0;
	int svalue;
	// Procesar línea de comandos...

	int opcion;
	while ((opcion = getopt (argc, argv, "f:p:s:a:")) != -1){
		switch (opcion){

	    case 'f':
	    	fvalue = optarg;
	    	fflag = 1;
	    	break;

	    case 'p':
	    	pvalue = optarg;
	    	pflag = 1;
	    	break;

	    case 's':
	    	svalue = atoi (optarg);
	    	sflag = 1;
	    	break;

	    case 'a':
	   	   	avalue = optarg;
	   	   	aflag = 1;
	       	break;

		if (isprint (optopt))
			cerr << "Error: Opción desconocida \'" << optopt
		    << "\'" << std::endl;
		else
			cerr << "Error: Caracter de opcion desconocido \'x" << std::hex << optopt
		    << "\'" << std::endl;
		exit (EXIT_FAILURE);

		// en cualquier otro caso lo consideramos error grave y salimos
	    default:
	    	cerr << "Error: línea de comandos errónea." << std::endl;
		exit(EXIT_FAILURE);
	    }  // case

	}// while

	int firstImprovement;

	//Comprobación de que se recibe un fichero
	if(fflag!=1){
		cout << "No se ha especificado ningún archivo, el programa se cerrará." << endl;
		exit(-1);
	}

	// Semilla de los números aleatorios especificado por un argumento

	if(sflag){
		srand(svalue);
	}
	// Semilla no especificada, usar la hora
	else{
		srand(time(NULL));
	}

	if (aflag && strcmp(avalue, "BLf"))
		firstImprovement=1;
	if (aflag && strcmp(avalue, "BLb"))
		firstImprovement=0;
	float tFinal = exp(-4.0);
	float gamma;
	// Tipo de problema
	if(pflag && strcmp(pvalue,"MMDP") == 0){
		cout<< "Problema MMDP. Instancia " << fvalue << "..."<< endl;
		MMDP p = MMDP();
		p.leerInstancia(fvalue);
		struct datosSolucionMMDP sol = p.generarSolucionRandom();
		gamma=0.8;
		if (aflag && strcmp(avalue, "BLf") == 0){
			firstImprovement=1;
			cout << "Algoritmo: BLf ..." << endl;
			cout << "Solución generada aleatoriamente: " << endl;
			cout << "****************************************" << endl;
			cout << "Viaje a realizar: " << endl;
			p.imprimirSolucion(sol);
			cout << endl << "****************************************" << endl;
			cout << "Función objetivo inicial: " << p.evaluarSolucion(sol) << endl << endl;
			cout << "Aplicando Algoritmo Blf ..." << endl;
			struct datosSolucionMMDP solM = p.aplicarBusquedaLocal(sol, firstImprovement, 50*p.getN());
			cout << endl << "Solución optimizada: " << endl;
			cout << "****************************************" << endl;
			cout << "Viaje a realizar: " << endl;
			p.imprimirSolucion(solM);
			cout << endl << "****************************************" << endl;
			cout << "Función objetivo final: " << p.evaluarSolucion(solM) << endl << endl;
		}
		if (aflag && strcmp(avalue, "BLb") == 0){
			firstImprovement=0;
			cout << "Algoritmo: BLb ..." << endl;
			cout << "Solución generada aleatoriamente: " << endl;
			cout << "****************************************" << endl;
			cout << "Viaje a realizar: " << endl;
			p.imprimirSolucion(sol);
			cout << endl << "****************************************" << endl;
			cout << "Función objetivo inicial: " << p.evaluarSolucion(sol) << endl << endl;
			cout << "Aplicando Algoritmo Blb ..." << endl;
			struct datosSolucionMMDP solM = p.aplicarBusquedaLocal(sol, firstImprovement, 50*p.getN());
			cout << endl << "Solución optimizada: " << endl;
			cout << "****************************************" << endl;
			cout << "Viaje a realizar: " << endl;
			p.imprimirSolucion(solM);
			cout << endl << "****************************************" << endl;
			cout << "Función objetivo final: " << p.evaluarSolucion(solM) << endl << endl;
		}
		if (aflag && strcmp(avalue, "ES") == 0){
			cout << "Algoritmo: ES ..." << endl;
			cout << "Solución generada aleatoriamente: " << endl;
			cout << "****************************************" << endl;
			cout << "Viaje a realizar: " << endl;
			p.imprimirSolucion(sol);
			cout << endl << "****************************************" << endl;
			cout << "Función objetivo inicial: " << p.evaluarSolucion(sol) << endl << endl;
			cout << "Aplicando Algoritmo ES ..." << endl;
			struct datosSolucionMMDP solM = p.aplicarEnfriamientoSimulado(sol, tFinal, gamma, 50*p.getN());
			cout << endl << "Solución optimizada: " << endl;
			cout << "****************************************" << endl;
			cout << "Viaje a realizar: " << endl;
			p.imprimirSolucion(solM);
			cout << endl << "****************************************" << endl;
			cout << "Función objetivo final: " << p.evaluarSolucion(solM) << endl << endl;

		}
	}else if(pflag && strcmp(pvalue,"TSP") == 0){
		cout<< "Problema TSP. Instancia " << fvalue << "..."<< endl;
				TSP p = TSP();
				p.leerInstancia(fvalue);
				struct datosSolucionTSP sol = p.generarSolucionRandom();
				gamma=0.99;
				if (aflag && strcmp(avalue, "BLf") == 0){
					firstImprovement=1;
					cout << "Algoritmo: BLf ..." << endl;
					cout << "Solución generada aleatoriamente: " << endl;
					cout << "****************************************" << endl;
					cout << "Viaje a realizar: " << endl;
					//p.imprimirSolucion(sol);
					cout << endl << "****************************************" << endl;
					cout << "Función objetivo inicial: " << p.evaluarSolucion(sol) << endl << endl;
					cout << "Aplicando Algoritmo Blf ..." << endl;
					struct datosSolucionTSP solM = p.aplicarBusquedaLocal(sol, firstImprovement, 1000*p.getN());
					cout << endl << "Solución optimizada: " << endl;
					cout << "****************************************" << endl;
					cout << "Viaje a realizar: " << endl;
					//p.imprimirSolucion(solM);
					cout << endl << "****************************************" << endl;
					cout << "Función objetivo final: " << p.evaluarSolucion(solM) << endl << endl;
				}
				if (aflag && strcmp(avalue, "BLb") == 0){
					firstImprovement=0;
					cout << "Algoritmo: BLb ..." << endl;
					cout << "Solución generada aleatoriamente: " << endl;
					cout << "****************************************" << endl;
					cout << "Viaje a realizar: " << endl;
					//p.imprimirSolucion(sol);
					cout << endl << "****************************************" << endl;
					cout << "Función objetivo inicial: " << p.evaluarSolucion(sol) << endl << endl;
					cout << "Aplicando Algoritmo Blb ..." << endl;
					struct datosSolucionTSP solM = p.aplicarBusquedaLocal(sol, firstImprovement, 1000*p.getN());
					cout << endl << "Solución optimizada: " << endl;
					cout << "****************************************" << endl;
					cout << "Viaje a realizar: " << endl;
					//p.imprimirSolucion(solM);
					cout << endl << "****************************************" << endl;
					cout << "Función objetivo final: " << p.evaluarSolucion(solM) << endl << endl;
				}
				if (aflag && strcmp(avalue, "ES") == 0){
					cout << "Algoritmo: ES ..." << endl;
					cout << "Solución generada aleatoriamente: " << endl;
					cout << "****************************************" << endl;
					cout << "Viaje a realizar: " << endl;
					p.imprimirSolucion(sol);

					cout << endl << "****************************************" << endl;

					cout << "Función objetivo inicial: " << p.evaluarSolucion(sol) << endl << endl;
					cout << "Aplicando Algoritmo ES ..." << endl;
					struct datosSolucionTSP solM = p.aplicarEnfriamientoSimulado(sol, tFinal, gamma, 1000*p.getN());
					cout << endl << "Solución optimizada: " << endl;
					cout << "****************************************" << endl;
					cout << "Viaje a realizar: " << endl;
					//p.imprimirSolucion(solM);
					cout << endl << "****************************************" << endl;
					cout << "Función objetivo final: " << p.evaluarSolucion(solM) << endl << endl;

				}

	}
	// ... resto de problemas
	// Por defecto, el MMDP
	else{
		cout<< "Problema MMDP. Instancia " << fvalue << "..."<< endl;

	}

	return EXIT_SUCCESS;
}

