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
int medio(int *tabla, int ip, int iu,int *pos);
int Mediana (int* tabla, int ip, int iu, int* pos);
int medio_avg(int *tabla, int ip, int iu, int *pos);

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

int medio(int *tabla, int ip, int iu,int *pos){

	*pos = ip;

	return 0;
}

int medio_avg(int *tabla, int ip, int iu, int *pos){
	*pos = (ip + iu) / 2;

	return 0;
}


int Mediana (int* tabla, int ip, int iu, int* pos){
	int im, ob;

	ob++;
	if (tabla[ip] <= tabla[im]){
		ob++;
		if(tabla[iu] <= tabla[im]){
			ob++;
			if(tabla[ip] <= tabla[iu]){
				*pos = iu;
			}
			else *pos = ip;
		}
		else *pos = im;
	}

	else {
		ob++;
		if(tabla[im] <= tabla[iu]){
			ob++;
			if(tabla[iu] <= tabla[ip]){
				*pos = iu;
			}
			else  *pos = ip;
		}
		else *pos = im;
	}

	return ob;
}

int partir(int* tabla, int ip, int iu, int *pos, pfunc_ordena metodo){

	int k;
	int i;
	int ob = 0;

	*pos = ip;

	k = tabla[*pos];

	swap(&tabla[ip], &tabla[*pos]);

	*pos = ip;

	for(i = ip + 1; i <= iu; i++ ){

		ob++;

		if(tabla[i] < k){
			(*pos)++;
			swap(&tabla[i], &tabla[*pos]);
		}
	}

	swap(&tabla[ip], &tabla[*pos]);

	return ob;

}



int quicksort(int* tabla, int ip, int iu){

	int pos = 0;
	int ob = 0;

	if(ip > iu) return ERR;

	else if(ip == iu) return ob;

	else{

		ob += partir(tabla, ip, iu, &pos, Mediana);

		if( ip < pos - 1)
			quicksort(tabla, ip, pos - 1);

		if( pos + 1 < iu)
			quicksort(tabla, pos + 1, iu);
	}
	return ob;
}
