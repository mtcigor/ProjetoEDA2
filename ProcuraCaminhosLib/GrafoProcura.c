/*****************************************************************//**
 * \file   GrafoProcura.c
 * \brief  Ficheiro com as funções para procurar caminhos num grafo de lista de adjacências
 * 
 * \author Igor a27977@alunos.ipca.pt
 * \date   May 2024
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Grafos.h"
#include "GrafoProcura.h"

/// <summary>
/// Função que implementa uma busca em profundidade (DFS) para encontrar todos os caminhos entre dois vértices
/// </summary>
/// <param name="g">Grafo que está a ser usado</param>
/// <param name="verticeAtual">Vértice ponto de partida</param>
/// <param name="idDestino">Vértice ponto de chegada</param>
/// <param name="caminhoAtual">Caminho a ser usado para guardar os vértices</param>
/// <param name="caminhos">Array com os caminhos possíveis entre os dois vértices</param>
/// <param name="numCaminhos">Número de caminhos existentes</param>
/// <param name="maxTamanho">Máximo de vértices por caminho</param>
void EncontrarCaminhosDFS(Grafo* g, Vertice* verticeAtual, int idDestino, Caminho* caminhoAtual, Caminho** caminhos, int* numCaminhos, int maxTamanho) {
	verticeAtual->visitado = true;
	AdicionaVerticeNoCaminho(caminhoAtual, verticeAtual->id);

	if (verticeAtual->id == idDestino) {
		Caminho* novoCaminho = (Caminho*)malloc(sizeof(Caminho));
		InicializaCaminho(novoCaminho, maxTamanho);

		for (int i = 0; i < caminhoAtual->tamanho; i++) {
			AdicionaVerticeNoCaminho(novoCaminho, caminhoAtual->vertices[i]);
		}
		novoCaminho->pesoTotal = caminhoAtual->pesoTotal;
		caminhos[(*numCaminhos)++] = novoCaminho;
	}
	else {
		Aresta* arestaAtual = verticeAtual->proxAresta;
		while (arestaAtual != NULL) {
			Vertice* proxVertice = OndeEstaVerticeGrafo(g, arestaAtual->idDestino);
			if (proxVertice != NULL && !proxVertice->visitado) {
				caminhoAtual->pesoTotal += arestaAtual->peso;
				EncontrarCaminhosDFS(g, proxVertice, idDestino, caminhoAtual, caminhos, numCaminhos, maxTamanho);
			}
			arestaAtual = arestaAtual->prox;
		}
	}

	verticeAtual->visitado = false;
	caminhoAtual->tamanho--;
	caminhoAtual->pesoTotal = 0;
}

/// <summary>
/// Função prepara para chamar 'EncontrarCaminhosDFS' e devolve todos os caminhos encontrados entre dois vértices
/// </summary>
/// <param name="grafo">Grafo a ser procurado</param>
/// <param name="idOrigem">id do vértice origem</param>
/// <param name="idDestino">id do vértice destino</param>
/// <param name="numCaminhos">Números de caminhos a procurar</param>
/// <returns>Array dinámica com todos os caminhos possíveis entre os dois vértices</returns>
Caminho** ObterTodosCaminhos(Grafo* grafo, int idOrigem, int idDestino, int* numCaminhos) {
	Vertice* verticeOrigem = GetVertice(grafo->inicioGrafo, idOrigem);
	if (verticeOrigem == NULL) return NULL;

	*numCaminhos = 0;
	int maxTamanho = grafo->totVertices;
	Caminho* caminhoAtual = (Caminho*)malloc(sizeof(Caminho));
	InicializaCaminho(caminhoAtual, maxTamanho);

	Caminho** caminhos = (Caminho**)malloc(grafo->totVertices * sizeof(Caminho*));
	EncontrarCaminhosDFS(grafo, verticeOrigem, idDestino, caminhoAtual, caminhos, numCaminhos, maxTamanho);

	LiberaCaminho(caminhoAtual);
	free(caminhoAtual);

	return caminhos;
}