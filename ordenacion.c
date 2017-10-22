/**
 *
 * Descripcion: Implementacion de funciones de ordenacion
 *
 * Fichero: ordenacion.c
 * Autores: Victoria Pelayo e Ignacio Rabuñal
 * Version: 1.1
 * Fecha: 12-10-2017
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "ordenacion.h"
#include "permutaciones.h"

int merge(int* tabla, int ip, int iu, int imedio);

/***************************************************/
/* Funcion: BubbleSort Fecha: 12-10-2017           */
/* Autores: Victoria Pelayo e Igacio Rabuñal       */
/*                                                 */
/* Ordena números de menor a mayor de una tabla    */
/* dada entre la posicion ip e iu                  */
/*                                                 */
/* Entrada:                                        */
/* int* tabla: tabla que se va a ordenar           */
/* int ip: posición desde donde se va a ordenar    */
/* int iu: posición hasta donde se va a ordenar    */
/* Salida:                                         */
/* int: numero de veces que se ha realizado la ob  */
/***************************************************/
int BubbleSort(int* tabla, int ip, int iu){

	int ob = 0;
	int i;
	int flag = 1;

	i = iu;

	if (tabla == NULL) return ERR;

	while (flag == 1 && i >= ip + 1) {
		int j;

		flag = 0;

		for (j = ip; j <= i - 1; j++){
			ob++;

			if (tabla[j] > tabla[j+1]){

				swap(&tabla[j], &tabla[j + 1]);

				flag = 1;
			}
		}

		i--;
	}

	return ob;
}


/***************************************************/
/* Funcion: mergesort  Fecha: 22-10-2017           */
/* Autores: Victoria Pelayo e Igacio Rabuñal       */
/*                                                 */
/* Ordena números de menor a mayor de una tabla    */
/* dada entre la posicion ip e iu. Para ello va a  */
/* llamar a otra funcion.Es un algoritmo recursivo */
/*                                                 */
/* Entrada:                                        */
/* int* tabla: tabla que se va a ordenar           */
/* int ip: posición desde donde se va a ordenar    */
/* int iu: posición hasta donde se va a ordenar    */
/* Salida:                                         */
/* count:numero de veces que se ha realizado la ob */
/***************************************************/
int mergesort(int* tabla, int ip, int iu){

	int M = (iu + ip)/2;
	int count = 0;

	if (ip == iu) return count;

	count += mergesort(tabla, ip, M);
	count += mergesort(tabla, M + 1, iu);
	count += merge (tabla, ip, iu, M);

	return count;
}


/***************************************************/
/* Funcion: merge Fecha: 22-10-2017           */
/* Autores: Victoria Pelayo e Igacio Rabuñal       */
/*                                                 */
/* Ordena números de menor a mayor de una tabla    */
/* dada entre la posicion ip e iu                  */
/*                                                 */
/* Entrada:                                        */
/* int* tabla: tabla que se va a ordenar           */
/* int ip: posición desde donde se va a ordenar    */
/* int iu: posición hasta donde se va a ordenar    */
/* int imedio: posicion media de la tabla, a ambos */
/* lados ya esta respectivamente ordenada.         */
/* Salida:                                         */
/* count: numero de veces que se ha realizado la ob*/
/***************************************************/
int merge(int* tabla, int ip, int iu, int imedio){

	int *aux = NULL;
	int i = ip;
	int k = 0;
	int j = imedio +1;
	int count = 0;

	aux = (int*)malloc(sizeof(aux[0]) * (iu - ip + 1));

	if(aux == NULL) return ERR;

	while (i <= imedio && j<= iu){
	
		count++;

		if (tabla[i] < tabla[j]){
			aux[k] = tabla[i];
			i++;
		}
		else{
			aux[k] = tabla[j];
			j++;
		}
		k++;
	}

	if(i > imedio){
		while(j <= iu){
			aux[k] = tabla[j];
			k++;
			j++;
		}
	}

	else if(j > iu){
		while( i <= imedio){
			aux[k] = tabla[i];
			k++;
			i++;
		}
	}

	tabla+=ip;

	for(i = 0; i < k; i++){
		tabla[i] = aux[i];
	}

	tabla-=ip;

	free(aux);

	return OK;
}
