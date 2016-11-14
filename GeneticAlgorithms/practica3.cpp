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

#include "mh/CPH.h"
#include "mh/Problema.h"

using namespace mh;
using namespace std;

/*template <class PROBLEMA,typename datosSolucion>
int procesarDatos(char *nombre) {
	int error=EXIT_SUCCESS;
	PROBLEMA p = PROBLEMA();
	if((error=p.leerInstancia(nombre))!=1){
		cout << "Error al leer la instancia del problema" << endl;
		return error;
	}

	p.imprimirInstancia();
	float maximo = 0;
	float minimo = 0;
	for(int i=0; i<1000; i++){
		datosSolucion x = p.generarSolucionRandom();
		cout << "Solución generada (iteracion " << i << "): " << endl;
		p.imprimirSolucion(x);
		float valorObtenido = p.evaluarSolucion(x);
		if(i==0){
			maximo = minimo = valorObtenido;
		}
		else{
			if(valorObtenido>maximo)
				maximo = valorObtenido;
			if(valorObtenido<minimo)
				minimo = valorObtenido;
		}
		cout << "Función objetivo: " << valorObtenido << endl;
		p.liberarMemoriaSolucion(x);
	}
	cout << endl << endl << "==> Valores extremos generados: máximo=" << maximo << " mínimo=" << minimo << endl;

	return error;
}*/


int main(int argc, char **argv) {

	char* fvalue, *pvalue, *avalue;
	int fflag=0, sflag=0;
	int svalue;
	struct datosSolucionCPH * resultado = new struct datosSolucionCPH;
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
	    	//pflag = 1;
	    	break;

	    case 's':
	    	svalue = atoi (optarg);
	    	sflag = 1;
	    	break;

	    case 'a':
	    	avalue = optarg;
	      	//aflag = 1;
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

	// Tipo de problema

	CPH p = CPH();
	if((p.leerInstancia(fvalue))!=1){
		cout << "Error al leer la instancia del problema" << endl;
		return 1;
	}
	cout<< "Problema CPH. Instancia " << fvalue << "..."<< endl;
	if (strcmp(avalue, "AGe")==0)
		resultado=p.aplicarAlgoritmoGenetico(200, 0.8, 0.2, 500, 1);
	else if(strcmp(avalue, "AGg")==0)
		resultado=p.aplicarAlgoritmoGenetico(200, 0.8, 0.2, 50, 0);
	// ... resto de problemas
	// Por defecto, el MMDP
	cout << "Función objetivo final: " << resultado->aptitud << endl;

	return EXIT_SUCCESS;
}

