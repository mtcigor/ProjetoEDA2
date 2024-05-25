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
	verticeAtual->visitado = true; //Vértice atual da função é visitado
	AdicionaVerticeNoCaminho(caminhoAtual, verticeAtual->id);

	//Caso o vértice atual seja o vértice de destino
	if (verticeAtual->id == idDestino) {
		//Inicializa um novo caminho para guardar o caminho atual no array de caminhos
		Caminho* novoCaminho = (Caminho*)malloc(sizeof(Caminho));
		InicializaCaminho(novoCaminho, maxTamanho);

		for (int i = 0; i < caminhoAtual->tamanho; i++) {
			AdicionaVerticeNoCaminho(novoCaminho, caminhoAtual->vertices[i]);
		}
		novoCaminho->pesoTotal = caminhoAtual->pesoTotal;
		caminhos[(*numCaminhos)++] = novoCaminho; //Adiciona o caminho ao array de caminhos
	}
	else {
		//Percorre as arestas do vértice atual
		Aresta* arestaAtual = verticeAtual->proxAresta;
		while (arestaAtual != NULL) {
			Vertice* proxVertice = OndeEstaVerticeGrafo(g, arestaAtual->idDestino);
			if (proxVertice != NULL && !proxVertice->visitado) { //Caso o destino da aresta não tenha sido visitado
				caminhoAtual->pesoTotal += arestaAtual->peso;
				EncontrarCaminhosDFS(g, proxVertice, idDestino, caminhoAtual, caminhos, numCaminhos, maxTamanho);
			}
			arestaAtual = arestaAtual->prox;
		}
	}

	//Desmarca o vértice atual
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
	Vertice* verticeOrigem = OndeEstaVerticeGrafo(grafo, idOrigem);
    if (verticeOrigem == NULL) return NULL;

    *numCaminhos = 0;
    int maxTamanho = grafo->totVertices;
	//Caminho auxiliar para guardar o caminho entre dois vértices antes de adicionar no array de caminhos
    Caminho* caminhoAtual = (Caminho*)malloc(sizeof(Caminho));
    InicializaCaminho(caminhoAtual, maxTamanho);

	//Array dinâmica para guardar todos os caminhos possíveis entre dois vértices
    Caminho** caminhos = (Caminho**)malloc(grafo->totVertices * sizeof(Caminho*));
    EncontrarCaminhosDFS(grafo, verticeOrigem, idDestino, caminhoAtual, caminhos, numCaminhos, maxTamanho);

	//Libertar memória alocada para o caminho auxiliar
    LiberaCaminho(caminhoAtual);
    free(caminhoAtual);

    return caminhos;
}

/// <summary>
/// Função para obter todos os caminhos entre todos os pares de vértices
/// </summary>
/// <param name="grafo">Grafo para obter todos os caminhos</param>
/// <param name="numCaminhos">Números de caminhos a procurar entre dois vértices</param>
/// <returns>Array dinámica com todos os caminhos possíveis de todos os vértices na origem e destino</returns>
TodosCaminhos* ObterTodosCaminhosGrafo(Grafo* grafo, int* numCaminhos) {
	TodosCaminhos* todosCaminhos = (TodosCaminhos*)malloc(grafo->totVertices * sizeof(TodosCaminhos));
	if (todosCaminhos == NULL) return NULL;

	for (int i = 0; i < grafo->totVertices; i++) {
		todosCaminhos[i].verticeOrigem = i;
		todosCaminhos[i].numCaminhos = 0;
		todosCaminhos[i].caminhos = NULL;

		for (int k = 0; k < grafo->totVertices; k++) {
			if (i == k) continue;
			int numCaminhosTemp;
			Caminho** caminhos = ObterTodosCaminhos(grafo, i, k, &numCaminhosTemp);
			if (caminhos != NULL) {
				Caminho** caminhoPointer = (Caminho**)realloc(todosCaminhos[i].caminhos, (todosCaminhos[i].numCaminhos + numCaminhosTemp) * sizeof(Caminho*));
				if (caminhoPointer == NULL) {
					// Se realloc falhar, libere a memória alocada e retorne NULL
					for (int j = 0; j <= i; j++) {
						LiberaCaminhos(todosCaminhos[j].caminhos, todosCaminhos[j].numCaminhos);
					}
					free(todosCaminhos);
					return NULL;
				}
				todosCaminhos[i].caminhos = caminhoPointer;
				for (int j = 0; j < numCaminhosTemp; j++) {
					todosCaminhos[i].caminhos[todosCaminhos[i].numCaminhos + j] = caminhos[j];
				}
				todosCaminhos[i].numCaminhos += numCaminhosTemp;
			}
		}
	}

	*numCaminhos = grafo->totVertices;
	return todosCaminhos;
}

/// <summary>
/// Função para encontrar o caminho com maior Peso entre todos os caminhos encontrados
/// </summary>
/// <param name="todosCaminhos">Estrutura que contêm todos os caminhos encontrados</param>
/// <param name="numCaminhos">Número de caminhos entre dois vértices</param>
/// <returns>Caminho com maior peso</returns>
MelhoresCaminhos* MelhorCaminho(TodosCaminhos* todosCaminhos, int numCaminhos) {
	//Aloca memória para a estrutura de melhores caminhos
	MelhoresCaminhos* melhoresCaminhos = (MelhoresCaminhos*)malloc(sizeof(MelhoresCaminhos));
	melhoresCaminhos->caminhos = (Caminho**)malloc(numCaminhos * sizeof(Caminho*));
	melhoresCaminhos->numMelhoresCaminhos = 0;

	//Inicializa o melhor caminho com o primeiro caminho encontrado
	Caminho* melhorCaminho = todosCaminhos[0].caminhos[0];
	int pesoMaximo = melhorCaminho->pesoTotal;
	melhoresCaminhos->caminhos[0] = melhorCaminho;
	melhoresCaminhos->numMelhoresCaminhos = 1;

	//Procura o caminho com maior peso todos os vértices destinos
	for (int i = 0; i < numCaminhos; i++) { 
		for (int j = 0; j < todosCaminhos[i].numCaminhos; j++) { 
			Caminho* caminhoAtual = todosCaminhos[i].caminhos[j];
			if (caminhoAtual->pesoTotal > pesoMaximo) { //Se o peso do caminho atual for maior que o peso máximo
				pesoMaximo = caminhoAtual->pesoTotal;
				melhoresCaminhos->numMelhoresCaminhos = 0;
				melhoresCaminhos->caminhos[melhoresCaminhos->numMelhoresCaminhos++] = caminhoAtual;
			}
			else if (caminhoAtual->pesoTotal == pesoMaximo) { //Caso o peso do caminho atual seja igual ao peso máximo
				melhoresCaminhos->caminhos[melhoresCaminhos->numMelhoresCaminhos++] = caminhoAtual;
			}
		}
	}

	return melhoresCaminhos;
}
