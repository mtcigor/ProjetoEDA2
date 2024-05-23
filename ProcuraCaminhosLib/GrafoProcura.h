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
/// <summary>
/// Fun��o que implementa uma busca em profundidade (DFS) para encontrar todos os caminhos entre dois v�rtices
/// </summary>
/// <param name="g">Grafo que est� a ser usado</param>
/// <param name="verticeAtual">V�rtice ponto de partida</param>
/// <param name="idDestino">V�rtice ponto de chegada</param>
/// <param name="caminhoAtual">Caminho a ser usado para guardar os v�rtices</param>
/// <param name="caminhos">Array com os caminhos poss�veis entre os dois v�rtices</param>
/// <param name="numCaminhos">N�mero de caminhos existentes</param>
/// <param name="maxTamanho">M�ximo de v�rtices por caminho</param>
void EncontrarCaminhosDFS(Grafo* g, Vertice* verticeAtual, int idDestino, Caminho* caminhoAtual, Caminho** caminhos, int* numCaminhos, int maxTamanho);

/// <summary>
/// Fun��o prepara para chamar 'EncontrarCaminhosDFS' e devolve todos os caminhos encontrados entre dois v�rtices
/// </summary>
/// <param name="grafo">Grafo a ser procurado</param>
/// <param name="idOrigem">id do v�rtice origem</param>
/// <param name="idDestino">id do v�rtice destino</param>
/// <param name="numCaminhos">N�meros de caminhos a procurar</param>
/// <returns>Array din�mica com todos os caminhos poss�veis entre os dois v�rtices</returns>
Caminho** ObterTodosCaminhos(Grafo* grafo, int idOrigem, int idDestino, int* numCaminhos);

/// <summary>
/// Fun��o para obter todos os caminhos entre todos os pares de v�rtices
/// </summary>
/// <param name="grafo">Grafo para obter todos os caminhos</param>
/// <param name="numCaminhos">N�meros de caminhos a procurar entre dois v�rtices</param>
/// <returns>Array din�mica com todos os caminhos poss�veis de todos os v�rtices na origem e destino</returns>
TodosCaminhos* ObterTodosCaminhosGrafo(Grafo* grafo, int* numCaminhos);

/// <summary>
/// Fun��o para encontrar o caminho com maior Peso entre todos os caminhos encontrados
/// </summary>
/// <param name="todosCaminhos">Estrutura que cont�m todos os caminhos encontrados</param>
/// <param name="numCaminhos">N�mero de caminhos entre dois v�rtices</param>
/// <returns>Caminho com maior peso</returns>
MelhoresCaminhos* MelhorCaminho(TodosCaminhos* todosCaminhos, int numCaminhos);
#pragma endregion

#pragma region Fun��es Manipula��o de Caminhos
/// <summary>
/// Fun��o para libertar a mem�ria para a estrutura melhores caminhos
/// </summary>
/// <param name="melhoresCaminhos">Endere�o da estrutura melhoresCaminhos</param>
void LiberaMelhoresCaminhos(MelhoresCaminhos* melhoresCaminhos);

/// <summary>
/// Fun��o para libertar a mem�ria alocada para a estrutura de todos os caminhos
/// </summary>
/// <param name="todosCaminhos">Endere�o da estrutura todosCaminhos</param>
/// <param name="numCaminhos">N�mero de caminhos por cada elemento de todosCaminhos</param>
void LiberaTodosCaminhos(TodosCaminhos* todosCaminhos, int numCaminhos);

/// <summary>
///  Fun��o para libertar a mem�ria alocada para a estrutura caminhos
/// </summary>
/// <param name="caminhos">Endere�o da estrutura caminhos</param>
void LiberaCaminhos(Caminho** caminhos);

/// <summary>
/// Fun��o para libertar a mem�ria alocada para o caminho
/// </summary>
/// <param name="caminho">Caminho a libertar</param>
void LiberaCaminho(Caminho* caminho);

/// <summary>
/// Fun��o para inicializar um caminho
/// </summary>
/// <param name="caminho">Endere�o do caminho a inicializar</param>
/// <param name="maxTamanho">Tamanho m�ximo do caminho</param>
void InicializaCaminho(Caminho* caminho, int maxTamanho);

/// <summary>
/// Fun��o para adicionar um v�rtice ao caminho
/// </summary>
/// <param name="caminho">Caminho a adicionar o v�rtice</param>
/// <param name="vertice">ID do v�rtice</param>
void AdicionaVerticeNoCaminho(Caminho* caminho, int vertice);

/// <summary>
/// Fun��o que imprime o caminho no output
/// </summary>
/// <param name="caminho">Caminho a imprimir</param>
void ImprimeCaminho(Caminho* caminho);
#pragma endregion