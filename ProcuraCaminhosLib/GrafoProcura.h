/*****************************************************************//**
 * \file   GrafoProcura.h
 * \brief  Cabeçalho com as funções para procurar caminhos num grafo e para manipulação de caminhos
 * 
 * \author Igor a27977@alunos.ipca.pt
 * \date   May 2024
 *********************************************************************/

#pragma once
#include "Grafos.h"

/// <summary>
/// Estrutura que representa um caminho entre dois vértices
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
/// Estrutura que representa os melhores caminhos entre dois vértices
/// </summary>
typedef struct {
    Caminho** caminhos;
    int numMelhoresCaminhos;
} MelhoresCaminhos;


#pragma region Funções Procura de Caminhos
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
void EncontrarCaminhosDFS(Grafo* g, Vertice* verticeAtual, int idDestino, Caminho* caminhoAtual, Caminho** caminhos, int* numCaminhos, int maxTamanho);

/// <summary>
/// Função prepara para chamar 'EncontrarCaminhosDFS' e devolve todos os caminhos encontrados entre dois vértices
/// </summary>
/// <param name="grafo">Grafo a ser procurado</param>
/// <param name="idOrigem">id do vértice origem</param>
/// <param name="idDestino">id do vértice destino</param>
/// <param name="numCaminhos">Números de caminhos a procurar</param>
/// <returns>Array dinámica com todos os caminhos possíveis entre os dois vértices</returns>
Caminho** ObterTodosCaminhos(Grafo* grafo, int idOrigem, int idDestino, int* numCaminhos);

/// <summary>
/// Função para obter todos os caminhos entre todos os pares de vértices
/// </summary>
/// <param name="grafo">Grafo para obter todos os caminhos</param>
/// <param name="numCaminhos">Números de caminhos a procurar entre dois vértices</param>
/// <returns>Array dinámica com todos os caminhos possíveis de todos os vértices na origem e destino</returns>
TodosCaminhos* ObterTodosCaminhosGrafo(Grafo* grafo, int* numCaminhos);

/// <summary>
/// Função para encontrar o caminho com maior Peso entre todos os caminhos encontrados
/// </summary>
/// <param name="todosCaminhos">Estrutura que contêm todos os caminhos encontrados</param>
/// <param name="numCaminhos">Número de caminhos entre dois vértices</param>
/// <returns>Caminho com maior peso</returns>
MelhoresCaminhos* MelhorCaminho(TodosCaminhos* todosCaminhos, int numCaminhos);
#pragma endregion

#pragma region Funções Manipulação de Caminhos
/// <summary>
/// Função para libertar a memória para a estrutura melhores caminhos
/// </summary>
/// <param name="melhoresCaminhos">Endereço da estrutura melhoresCaminhos</param>
void LiberaMelhoresCaminhos(MelhoresCaminhos* melhoresCaminhos);

/// <summary>
/// Função para libertar a memória alocada para a estrutura de todos os caminhos
/// </summary>
/// <param name="todosCaminhos">Endereço da estrutura todosCaminhos</param>
/// <param name="numCaminhos">Número de caminhos por cada elemento de todosCaminhos</param>
void LiberaTodosCaminhos(TodosCaminhos* todosCaminhos, int numCaminhos);

/// <summary>
///  Função para libertar a memória alocada para a estrutura caminhos
/// </summary>
/// <param name="caminhos">Endereço da estrutura caminhos</param>
void LiberaCaminhos(Caminho** caminhos);

/// <summary>
/// Função para libertar a memória alocada para o caminho
/// </summary>
/// <param name="caminho">Caminho a libertar</param>
void LiberaCaminho(Caminho* caminho);

/// <summary>
/// Função para inicializar um caminho
/// </summary>
/// <param name="caminho">Endereço do caminho a inicializar</param>
/// <param name="maxTamanho">Tamanho máximo do caminho</param>
void InicializaCaminho(Caminho* caminho, int maxTamanho);

/// <summary>
/// Função para adicionar um vértice ao caminho
/// </summary>
/// <param name="caminho">Caminho a adicionar o vértice</param>
/// <param name="vertice">ID do vértice</param>
void AdicionaVerticeNoCaminho(Caminho* caminho, int vertice);

/// <summary>
/// Função que imprime o caminho no output
/// </summary>
/// <param name="caminho">Caminho a imprimir</param>
void ImprimeCaminho(Caminho* caminho);
#pragma endregion