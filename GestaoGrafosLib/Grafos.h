/*****************************************************************//**
 * \file   Grafos.h
 * \brief  
 * 
 * \author mtcig
 * \date   May 2024
 *********************************************************************/
#pragma once

#include <stdio.h>
#include <stdbool.h>

#define MAX 10

typedef struct Vertice {
	char label;
	bool visited;       /*!< Controlar travessia do Grafo */
}Vertice;

typedef struct Grafo
{
	Vertice* vertices;  //ser� array de vertices
	int** adj;          //ser� matriz de adjacencias
}Grafo;


//Fun��es do grafo
void ShowArestas(int** adj, int nVertices);
void ShowGraph(Vertice* lst, int** adj, int numVertices);
int AddVertice(Vertice* lstVertices, int numVertices, char label);
bool AddAresta(int** adj, int v1, int v2);
int** CriaInicializaMatrizAdjacencias(int numVertices);
Grafo* CriaGrafo(int numVertices, bool* res);
void ProcessaVertice(Vertice* v);