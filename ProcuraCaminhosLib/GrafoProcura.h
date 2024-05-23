/*****************************************************************//**
 * \file   GrafoProcura.h
 * \brief  Cabe�alho com as fun��es para procurar caminhos num grafo e para manipula��o de caminhos
 * 
 * \author Igor a27977@alunos.ipca.pt
 * \date   May 2024
 *********************************************************************/

#pragma once
#include "Grafos.h"

/// <summary>
/// Estrutura que representa um caminho entre dois v�rtices
/// </summary>
typedef struct Caminho {
    int* vertices;
    int tamanho;
    int pesoTotal;
} Caminho;

/// <summary>
/// Estrutura que representa todos os caminhos de um grafo
/// </summary>
typedef struct TodosCaminhos{
    int verticeOrigem;
	Caminho** caminhos;
	int numCaminhos;
} TodosCaminhos;

/// <summary>
/// Estrutura que representa os melhores caminhos entre dois v�rtices
/// </summary>
typedef struct {
    Caminho** caminhos;
    int numMelhoresCaminhos;
} MelhoresCaminhos;


#pragma region Fun��es Procura de Caminhos
void EncontrarCaminhosDFS(Grafo* g, Vertice* verticeAtual, int idDestino, Caminho* caminhoAtual, Caminho** caminhos, int* numCaminhos, int maxTamanho);
Caminho** ObterTodosCaminhos(Grafo* grafo, int idOrigem, int idDestino, int* numCaminhos);
TodosCaminhos* ObterTodosCaminhosGrafo(Grafo* grafo, int* numCaminhos);
MelhoresCaminhos* MelhorCaminho(TodosCaminhos* todosCaminhos, int numCaminhos);
#pragma endregion

#pragma region Fun��es Manipula��o de Caminhos
void LiberaMelhoresCaminhos(MelhoresCaminhos* melhoresCaminhos);
void LiberaTodosCaminhos(TodosCaminhos* todosCaminhos, int numCaminhos);
void LiberaCaminhos(Caminho** caminhos);
void LiberaCaminho(Caminho* caminho);
void InicializaCaminho(Caminho* caminho, int maxTamanho);
void AdicionaVerticeNoCaminho(Caminho* caminho, int vertice);
void ImprimeCaminho(Caminho* caminho);
#pragma endregion