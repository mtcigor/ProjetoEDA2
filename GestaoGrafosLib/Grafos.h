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
	int idDestino; //Identifica��o do pr�ximo v�rtice que liga
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

#pragma region Assinatura Gest�o V�rtices
void DestroiVertice(Vertice* vertice);
void MostrarGrafo(Vertice* grafo);
Vertice* CriarVertice(int id);
bool ExisteVertice(Vertice* inicio, int id);
Vertice* GetVertice(Vertice* inicio, int id);
Vertice* InserirVertice(Vertice* atual, Vertice* novo, bool* resultado);
Vertice* EliminaVertice(Vertice* atual, int cod, bool* resultado);
#pragma endregion
#pragma region Assinatura Gest�o Arestas
void DestroiAresta(Aresta* aresta);
Aresta* NovaAresta(int idDestino);
Aresta* EliminarAresta(Aresta* lista, int cod, bool* resultado);
Aresta* ElimiminaAllArestas(Aresta* lista, bool* resultado);
Aresta* InsereAresta(Aresta* lista,int peso, int idDestino);
#pragma endregion
#pragma region Assinatura Gest�o Grafos
void MostrarGrafoLA(Grafo* gr);
Grafo* CriaGrafo(int total);
bool ExisteVerticeGrafo(Grafo* g, int idVertice);
Vertice* OndeEstaVerticeGrafo(Grafo* g, int idVertice);
Grafo* InsereVerticeGrafo(Grafo* g, Vertice* novo, int* resultado);
Grafo* InsereArestaGrafo(Grafo* g, int idOrigem, int idDestino,int peso, bool* resultado);
Grafo* EliminaAdjGrafo(Grafo* g, int origem, int destino, bool* resultado);
#pragma endregion




