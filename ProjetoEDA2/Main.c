/*****************************************************************//**
 * \file   Main.c
 * \brief  
 * 
 * \author mtcig
 * \date   May 2024
 *********************************************************************/

#include "Grafos.h"
#include <stdio.h>
#include <stdlib.h>


int main() {
	Grafo *grafo = CriaGrafo(2);
	int* resultadoInt = 0;
	bool* resultadoBool = (bool*)malloc(sizeof(bool));
	*resultadoBool = false;

	Vertice* vertice = CriarVertice(0);
	grafo = InsereVerticeGrafo(grafo, vertice, &resultadoInt);

	Vertice* vertice2 = CriarVertice(1);
	grafo = InsereVerticeGrafo(grafo, vertice2, &resultadoInt);

	grafo = InsereArestaGrafo(grafo, 0, 1,53, resultadoBool);
	grafo = InsereArestaGrafo(grafo, 1, 0, 400, resultadoBool);
	return 0;
}
