/*****************************************************************//**
 * \file   Grafos.h
 * \brief  Ficheiro cabe�alho para gerir os grafos com lista de adjac�ncias
 * 
 * \author Igor a27977@alunos.ipca.pt
 * \date   May 2024
 *********************************************************************/
#pragma once

#include <stdbool.h>

/*
*	
*	CONSTRU��O DO GRAFO E PLANEAMENTO DOS CAMINHOS 
*  
*	Segue-se com um grafo dirigido em que as linhas e colunas sejam um v�rtice si s� 
*	por exemplo na matriz do enunciado a 1� coluna e a 1� linha ser� um v�rtice por si s� igual ao resto
*	em que cada valor da matriz representa a aresta entre dois v�rtices sendo que o n�mero em quest�o � o peso
*	por exemplo se quero ir do v�rtice 1 para o v�rtice 2 o custo � 53 e do v�rtice 2 para o v�rtice 1 o custo j� � de 497.
*	
*	Esta estrutura foi desenvolvida em lista de adjac�ncias para representar um grafo dirigido e que suporta um
*	n�mero vari�vel de v�rtices.
* 
*/

/// <summary>
/// Estrutura que define uma aresta
/// </summary>
typedef struct Aresta {
	int id; //Identifica��o do pr�ximo v�rtice que liga
	int peso; //O custo de um v�rtice para outro v�rtice
	struct Aresta* prox; //Pr�xima aresta que conecta ao v�rtice
}Aresta;

/// <summary>
/// Estrutura que define um v�rtice
/// </summary>
typedef struct Vertice {
	int id; //Identifica��o do v�rtice
	bool visitado; //Se j� foi visitado
	Aresta* proxAresta; //Arestas que conecta o v�rtice para outro
	struct Vertice* proxVertice; //Pr�ximo v�rtice
}Vertice;

/// <summary>
/// Estrutura que define um v�rtice
/// </summary>
typedef struct Grafo {
	Vertice* inicioGrafo; //O primeiro v�rtice do grafo
	int totVertices; //N�mero m�ximo de v�rtices
}Grafo;
