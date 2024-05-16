/*****************************************************************//**
 * \file   Main.c
 * \brief  Ficheiro principal para executar o Projeto
 * 
 * \author Igor a27977@alunos.ipca.pt
 * \date   May 2024
 *********************************************************************/

#include "Grafos.h"
#include "CarregarGrafos.h"

#include <stdio.h>
#include <stdlib.h>


int main() {
	/*Grafo *grafo = CriaGrafo(2);
	Vertice* vertice = CriarVertice(0);
	grafo = InsereVerticeGrafo(grafo, vertice, &resultadoInt);

	Vertice* vertice2 = CriarVertice(1);
	grafo = InsereVerticeGrafo(grafo, vertice2, &resultadoInt);

	grafo = InsereArestaGrafo(grafo, 0, 1, 53, resultadoBool);
	grafo = InsereArestaGrafo(grafo, 1, 0, 400, resultadoBool);
	MostrarGrafo(grafo->inicioGrafo);
	bool aux = ExisteVerticeGrafo(grafo, 1);
	Vertice* verticeAux = OndeEstaVerticeGrafo(grafo, 1);
	grafo = EliminaAdjGrafo(grafo, 1, 0, resultadoBool);
	grafo = InsereArestaGrafo(grafo, 1, 0, 497, resultadoBool);
	grafo = InsereArestaGrafo(grafo, 0, 1, 383, resultadoBool);
	grafo = InsereArestaGrafo(grafo, 1, 0, 7, resultadoBool);*/
	
	int* resultadoInt = 0;

	bool* resultadoBool = (bool*)malloc(sizeof(bool));
	if (resultadoBool == NULL) return 1;
	*resultadoBool = false;

	Grafo* grafo2 = CarregarGrafo("grafo.txt");
	MostrarGrafoLA(grafo2);

	return 0;
}
