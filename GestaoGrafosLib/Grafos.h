/*****************************************************************//**
 * \file   Grafos.h
 * \brief  Ficheiro cabeçalho para gerir os grafos com lista de adjacências
 * 
 * \author Igor a27977@alunos.ipca.pt
 * \date   May 2024
 *********************************************************************/
#pragma once

#include <stdbool.h>

/*
*	
*	CONSTRUÇÃO DO GRAFO E PLANEAMENTO DOS CAMINHOS 
*  
*	Segue-se com um grafo dirigido em que as linhas e colunas sejam um vértice si só 
*	por exemplo na matriz do enunciado a 1º coluna e a 1º linha será um vértice por si só igual ao resto
*	em que cada valor da matriz representa a aresta entre dois vértices sendo que o número em questão é o peso
*	por exemplo se quero ir do vértice 1 para o vértice 2 o custo é 53 e do vértice 2 para o vértice 1 o custo já é de 497.
*	
*	Esta estrutura foi desenvolvida em lista de adjacências para representar um grafo dirigido e que suporta um
*	número variável de vértices.
* 
*/

/// <summary>
/// Estrutura que define uma aresta
/// </summary>
typedef struct Aresta {
	int id; //Identificação do próximo vértice que liga
	int peso; //O custo de um vértice para outro vértice
	struct Aresta* prox; //Próxima aresta que conecta ao vértice
}Aresta;

/// <summary>
/// Estrutura que define um vértice
/// </summary>
typedef struct Vertice {
	int id; //Identificação do vértice
	bool visitado; //Se já foi visitado
	Aresta* proxAresta; //Arestas que conecta o vértice para outro
	struct Vertice* proxVertice; //Próximo vértice
}Vertice;

/// <summary>
/// Estrutura que define um vértice
/// </summary>
typedef struct Grafo {
	Vertice* inicioGrafo; //O primeiro vértice do grafo
	int totVertices; //Número máximo de vértices
}Grafo;
