
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

	data.n=0;
	data.c=0;
	data.p=0;
}

CPH::~CPH() {
	liberarMemoria();
}

int CPH::reservarMemoriaInstancia() {
	data.d= new struct nodo [data.n];
	
	return 1;
}

void CPH::liberarMemoriaInstancia() {
	delete [] data.d;
}

void CPH::liberarMemoriaSolucion(struct datosSolucionCPH * sol){
	delete [] sol->x;
	delete [] sol->c;
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


float CPH::evaluarSolucion(struct datosSolucionCPH *sol){
	float distancia=0;

	for (int i=0; i<data.p; i++){
		if (sol->c[i]<0)
			return 1000000.0;
	}
	for (int i=0; i<data.n; i++){
			if (sol->x[i]<data.p){
				for (int j=0; j< data.n; j++){
					if(sol->x[j]==sol->x[i]+data.p)
						distancia+=sqrt(pow(data.d[i].x-data.d[j].x,2) + pow(data.d[i].y-data.d[j].y, 2));
				}
			}
	}
	sol->valor=distancia;
	sol->eval=0;
	return distancia;

}

struct datosSolucionCPH * CPH::generarSolucionRandom() {
	struct datosSolucionCPH * sol;
	sol = new struct datosSolucionCPH;
	sol->x = new int [data.n];
	sol->c = new int[data.p];
    	int total = data.n;
    	//int contador=0, intentos=0;
    	int max=0, con=0;
   	
   	int * numerosPorElegir = new int [data.n], * numerosPorElegir2 = new int [data.n];

    for (int i=0; i<data.n; i++){
    	numerosPorElegir[i]=i;
    	numerosPorElegir2[i]=i;
    }

    

    // Inicializar la lista de elecciones posibles

    for(int i=0; i < data.p; i++){
  
    	int numeroElegido = rand() % (data.n-i);
    	// Recordar el numero elegido
    	sol->x[numerosPorElegir[numeroElegido]]=i+data.p;
    	sol->c[i]=data.c-data.d[numerosPorElegir[numeroElegido]].demanda;
    	// Ponemos en numeros por elegir, el ultimo que era valido, asi
    	// son todos validos hasta data.n-i-1
    	numerosPorElegir[numeroElegido]=numerosPorElegir[total-i-1];
    }

    //Coger las distancias
   for (int i=0; i< data.n; i++){
    	int numeroElegido = rand() % (data.n-i);
    	if (sol->x[numerosPorElegir2[numeroElegido]]<data.p){
    		for (int j=0; j < data.p; j++){
    				if (sol->c[j]>max){
    					max=sol->c[j];
    					con=j;
    				}
    		}
		//if (sol->c[con]-data.d[numeroElegido].demanda >= 0){
			sol->c[con]-=data.d[numeroElegido].demanda;
			sol->x[numeroElegido]=con;
			numerosPorElegir2[numeroElegido]=numerosPorElegir2[total-i-1];
			//contador++;
		/*}else{
			intentos++;
			if (intentos==10){
				intentos=0;
				sol->c[con]-=data.d[numeroElegido].demanda;
				sol->x[numeroElegido]=sol->x[con]-data.p;
				numerosPorElegir2[numeroElegido]=numerosPorElegir2[total-contador-1];
				contador++;
			}
		}*/
			//cout << contador << endl;
		max=0;
    	}

    }

    delete [] numerosPorElegir;
    delete [] numerosPorElegir2;
    sol->eval=0;

	return sol;
}

void CPH::imprimirSolucion(struct datosSolucionCPH * sol) {
	cout << "Concentradores: " << endl;
	for(int i=0; i<data.n; i++){
		cout << sol->x[i] << " ";
	}
}

void CPH::imprimirInstancia() {
	for (int i=0; i<data.n; i++){
		cout << data.d[i].x << " " << data.d[i].y << " " << data.d[i].demanda << endl;
	}
}

struct datosSolucionCPH * CPH::aplicarAlgoritmoGenetico(int tamanoPoblacion, float pCruce, float pMutacion, int nEval, bool estacionario){
	
	struct datosSolucionCPH ** pob = new datosSolucionCPH * [tamanoPoblacion];
	struct datosSolucionCPH ** pob2 = new datosSolucionCPH * [tamanoPoblacion+2];
	struct datosSolucionCPH ** selec = new datosSolucionCPH * [tamanoPoblacion];
	
	struct datosSolucionCPH * mejor = new struct datosSolucionCPH;
	struct datosSolucionCPH * mejor1 = new struct datosSolucionCPH;
	int eval=0, nGenSinMejorar=0;

	for (int i=0; i<tamanoPoblacion; i++){
		pob[i]=generarSolucionRandom();
		pob[i]->valor=evaluarSolucion(pob[i]);
		eval++;
	}
	
	for (int i=0; i<tamanoPoblacion+2; i++){
		pob2[i]=reservaMemoriaSolucion();
	}

	if(estacionario){
		do{
			mejor=mejorSolucionPoblacion(pob, tamanoPoblacion);
			cout << "hola est"<< endl;
			selec=seleccionPorRuleta(pob, tamanoPoblacion, 2);
			
			if((rand()%100)<=pCruce){
				operadorCruce(selec[0], selec[1]);
			}
			
			for (int i=0; i<2; i++){
				if((rand()%100)<=pMutacion){
					operadorMutacion(selec[i]);
				}
			}

			for (int i=0; i<2; i++){
				if(selec[i]->eval){
					selec[i]->valor=evaluarSolucion(selec[i]);
					eval++;
				}
			}
			
			for (int i=0; i < tamanoPoblacion; i++){
				
				pob2[i]->x=pob[i]->x;

				pob2[i]->c=pob[i]->c;
				
				pob2[i]->valor=pob[i]->valor;
				
				pob2[i]->eval=pob[i]-eval;
				
			}
			for (int i=0; i < 2; i++){
				
				for (int j=0; j < data.n ; j++){
					pob2[tamanoPoblacion+i]->x[j]=selec[i]->x[j];
				}		
				for (int j=0; j < data.p ; j++){
					pob2[tamanoPoblacion+i]->c[j]=selec[i]->c[j];
				}
				
				pob2[tamanoPoblacion+i]->valor=selec[i]->valor;
				pob2[tamanoPoblacion+i]->eval=selec[i]->eval;
			}
			
			pob=seleccionPorTorneo(pob2, 2, tamanoPoblacion+2, tamanoPoblacion-1);
			

			mejor1=mejorSolucionPoblacion(pob, tamanoPoblacion);

			cout << "hola" << endl;
 			if (mejor1->valor < mejor->valor){
				nGenSinMejorar=0;
			}else{
				nGenSinMejorar++;
			}

			if(nGenSinMejorar>500){
				nGenSinMejorar=0;
				for (int i=0; i<tamanoPoblacion-1; i++){
					pob[i]=generarSolucionRandom();
					pob[i]->valor=evaluarSolucion(pob[i]);
					eval++;

				}
			}
			for(int i=0;i<data.n;i++)
			{
				pob[tamanoPoblacion-1]->x[i]=mejor->x[i];
			}
			pob[tamanoPoblacion-1]->valor=mejor->valor;

			/*mejor=generarSolucionRandom();
			evaluarSolucion(mejor);
			eval++;*/
			cout << eval << endl;

		}while(eval<nEval*data.n);

		mejor=mejorSolucionPoblacion(pob, tamanoPoblacion);
		return mejor;

	}else{
		do{	/*
			for (int i=0; i < tamanoPoblacion; i++){
				if (pob[i].valor<m){
					m=pob[i].valor;
					mejor=pob[i];
				}
			}

			selec=seleccionPorRuleta(pob, tamanoPoblacion, tamanoPoblacion-1);

			for (int i=0; i < tamanoPoblacion-1; i++){
				//if (rand()%100 <= pCruce){
					operadorCruce(selec[i], selec[rand()%(tamanoPoblacion-1)]);
				//}
			}
			/*
			for (int i=0; i < tamanoPoblacion-1; i++){
				if (rand()%100 <= pMutacion){
					operadorMutacion(selec[i]);
				}
			}

			for (int i=0; i < tamanoPoblacion-1; i++){
				if(selec[i].eval){
					evaluarSolucion(selec[i]);
					eval++;
				}
			}

			for (int i=0; i < tamanoPoblacion-1; i++){
				if (selec[i].valor<m){
					m=selec[i].valor;
					mejor=selec[i];
					cambio=1;
				}
			}

			if (cambio){
				cambio=0;
				nGenSinMejorar=0;
			}else{
				nGenSinMejorar++;
			}

			if(nGenSinMejorar>50){
				for (int i=0; i<tamanoPoblacion-1; i++){
					selec[i]=generarSolucionRandom();
					eval++;
					evaluarSolucion(selec[i]);
				}
			}

			pob=selec;
			pob->push_back(mejor);
			*/
			cout << eval << endl;
		}while(eval<nEval*data.n);
		/*
		for (int i=0; i < tamanoPoblacion; i++){
			if (pob[i].valor<m){
				m=pob[i].valor;
				mejor=pob[i];
			}
		}
		*/
		return mejor;

	}
	return mejor;
}
void CPH::operadorMutacion(datosSolucionCPH * ind){
	int i=rand()%data.n;
	int c=rand()%data.n;
	int aux;

	aux=ind->x[c];
	ind->x[c]=ind->x[i];
	ind->x[i]=aux;

	ind->eval=1;

}
void CPH::operadorCruce(datosSolucionCPH * ind1, datosSolucionCPH * ind2){
	int aux, r;
	for (int i=0; i < data.n; i++){
		if (ind1->x[i] < data.p && ind2->x[i] < data.p){
			r=(rand()%100);
			if (r <= 75){
				ind1->c[ind1->x[i]]+=data.d[i].demanda;
				ind2->c[ind2->x[i]]+=data.d[i].demanda;
				aux=ind1->x[i];
				ind1->x[i]=ind2->x[i];
				ind2->x[i]=aux;
				ind1->c[ind1->x[i]]-=data.d[i].demanda;
				ind2->c[ind2->x[i]]-=data.d[i].demanda;
				ind1->eval=1;
				ind2->eval=1;

			}
		}
	}
}
struct datosSolucionCPH ** CPH::seleccionPorTorneo(struct datosSolucionCPH ** pob, int tamanoTorneo, int tamanoPoblacion, int numeroSeleccion){
	struct datosSolucionCPH ** inds = new datosSolucionCPH *[tamanoTorneo], ** selec = new datosSolucionCPH *[numeroSeleccion];
	int r;
	float m=100000.0;
	struct datosSolucionCPH * mejor = new struct datosSolucionCPH;
	for (int j=0; j<numeroSeleccion; j++){

		for (int i=0; i< tamanoTorneo; i++){
			r=rand()%tamanoPoblacion;
			inds[i]=pob[r];
		}
		for (int i=0; i< tamanoTorneo; i++){
			if (inds[i]->valor<m)
				mejor=inds[i];
				m=inds[i]->valor;
		}

		selec[j]=mejor;
	}
	delete [] inds;
	return selec;
}
struct datosSolucionCPH ** CPH::seleccionPorRuleta(struct datosSolucionCPH ** pob, int tamanoPoblacion, int numeroSeleccion){
	
	float ruleta[tamanoPoblacion];
	
	struct datosSolucionCPH * valido[numeroSeleccion];
	float total=0.0, F=0.0;
	int r;
	
	
	for (int i=0; i< tamanoPoblacion; i++){
		total+=(pob[i]->valor);
	}
	
	for (int i=0; i< tamanoPoblacion; i++){
			F+=1/pob[i]->valor;
			ruleta[i]=F/total;
	}
	
	for (int i=0; i< numeroSeleccion; i++){
		r=rand()/((float)RAND_MAX);
		for (int j=0; j < tamanoPoblacion; j++){
			if (ruleta[j]>=r){
				//valido[i]=pob[j];

				valido[i] = reservaMemoriaSolucion();	
				for(int k=0; k<data.n; k++){
					valido[i]->x[k]=pob[j]->x[k];
				}
				for (int j=0; j<data.p; j++){
					valido[i]->c[j]=pob[j]->c[j];
				}
				valido[i]->valor=pob[j]->valor;
				valido[i]->eval=pob[j]->eval;
			}
		}
	}

	return valido;


}
struct datosSolucionCPH * CPH::mejorSolucionPoblacion(struct datosSolucionCPH ** pob, int tamanoPoblacion){
	struct datosSolucionCPH * mejor;
	mejor=reservaMemoriaSolucion();
	int aux=0;
	float comp=100000.0;

	for(int i=0; i<tamanoPoblacion;i++)	{
		if(pob[i]->valor<comp){
			comp=pob[i]->valor;
			aux=i;
		}
	}

	
	for(int k=0; k<data.n; k++){
		mejor->x[k]=pob[aux]->x[k];
	}
	for (int j=0; j<data.p; j++){
		mejor->c[j]=pob[aux]->c[j];
	}
	mejor->valor=pob[aux]->valor;
	mejor->eval=pob[aux]->eval;

	return mejor;
}

struct datosSolucionCPH * CPH::reservaMemoriaSolucion(){
	struct datosSolucionCPH *sol=new struct datosSolucionCPH;
	sol->x = new int [data.n];
	sol->c = new int [data.p];

	return sol;
}

}



