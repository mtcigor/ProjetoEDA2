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
	int idDestino; //Identificação do próximo vértice que liga
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

#pragma region Assinatura Gestão Vértices
/// <summary>
/// Função que destroi um vértice
/// </summary>
/// <param name="vertice">Endereço do vértice</param>
void DestroiVertice(Vertice* vertice);

/// <summary>
/// Função que mostra o grafo no output do utilizador
/// </summary>
/// <param name="iniciografo">Endereço do primeiro vértice do grafo</param>
void MostrarGrafo(Vertice* grafo);

/// <summary>
/// Função que cria um vértice (aloca memória) e inicializa os valores como NULL
/// </summary>
/// <param name="id">ID do vértice a criar</param>
/// <returns>Endereço do novo vértice</returns>
Vertice* CriarVertice(int id);

/// <summary>
/// Função que verifica se o vértice existe
/// </summary>
/// <param name="inicio">Endereço do primeiro vértice do grafo</param>
/// <param name="id">ID do vértice a procurar</param>
/// <returns>Valor bool</returns>
bool ExisteVertice(Vertice* inicio, int id);

/// <summary>
/// Função que procura e devolve o mesmo vértice
/// </summary>
/// <param name="inicio">Endereço do primeiro vértice do grafo</param>
/// <param name="id">ID do vértice a procurar</param>
/// <returns>Endereço do vértice</returns>
Vertice* GetVertice(Vertice* inicio, int id);

/// <summary>
/// Função que insere um vértice na lista de vértices
/// </summary>
/// <param name="atual">Endereço de um vértice antes do novo vértice</param>
/// <param name="novo">Endereço do novo vértice</param>
/// <param name="resultado">Valor bool para verificar se inseriu com sucesso</param>
/// <returns>Devolve o endereço do novo vértice</returns>
Vertice* InserirVertice(Vertice* atual, Vertice* novo, bool* resultado);

/// <summary>
/// Função que elimina um vértice da lista de vértices
/// </summary>
/// <param name="atual">Vértice da lista antes do vértice a eliminar</param>
/// <param name="cod">ID do vértice a eliminar</param>
/// <param name="resultado">Valor bool para verificar se removeu com sucesso</param>
/// <returns>Devolve o vértice antes do vértice eliminado</returns>
Vertice* EliminaVertice(Vertice* atual, int cod, bool* resultado);
#pragma endregion
#pragma region Assinatura Gestão Arestas
/// <summary>
/// Função que destroi uma aresta
/// </summary>
/// <param name="aresta"></param>
void DestroiAresta(Aresta* aresta);

/// <summary>
/// Função que cria uma nova aresta (aloca memória) e inicializa os valores como NULL
/// </summary>
/// <param name="idDestino"></param>
/// <returns></returns>
Aresta* NovaAresta(int idDestino);

/// <summary>
/// Função que elimina uma aresta da lista de arestas
/// </summary>
/// <param name="lista">Início da lista antes da aresta a remover</param>
/// <param name="cod">Código idDestino da aresta a eliminar</param>
/// <param name="resultado">Valor bool para verificar se removeu com sucesso</param>
/// <returns>Desvolve a aresta anterior a do que foi removida</returns>
Aresta* EliminarAresta(Aresta* lista, int cod, bool* resultado);

/// <summary>
/// Função que elimina todas as arestas da lista de arestas (não apaga a lista em si)
/// </summary>
/// <param name="lista">Lista a eliminar</param>
/// <param name="resultado">Valor bool para verificar se removeu com sucesso</param>
/// <returns>Devolve a lista vazia</returns>
Aresta* ElimiminaAllArestas(Aresta* lista, bool* resultado);

/// <summary>
/// Função que insere uma aresta na lista de arestas
/// </summary>
/// <param name="lista">Lista de arestas</param>
/// <param name="peso">Peso da aresta</param>
/// <param name="idDestino">Vértice destino da aresta</param>
/// <returns>Devolve a aresta</returns>
Aresta* InsereAresta(Aresta* lista,int peso, int idDestino);
#pragma endregion
#pragma region Assinatura Gestão Grafos
/// <summary>
/// Função que mostra o grafos no output do utilizador
/// </summary>
/// <param name="gr">Endereço do grafo</param>
void MostrarGrafoLA(Grafo* gr);

/// <summary>
/// Função que cria um grafo (aloca memória) e inicializa os valores como NULL
/// </summary>
/// <param name="total">Total de vértices no grafo</param>
/// <returns>Endereço do grafo</returns>
Grafo* CriaGrafo(int total);

/// <summary>
/// Verifica se existe um vértice no grafo
/// </summary>
/// <param name="g">Endereço do grafo</param>
/// <param name="idVertice">ID do vértice</param>
/// <returns>Devolve um valor bool</returns>
bool ExisteVerticeGrafo(Grafo* g, int idVertice);

/// <summary>
/// Função que procura e devolve o vértice no grafo
/// </summary>
/// <param name="g">Endereço do grafo</param>
/// <param name="idVertice">ID do vértice</param>
/// <returns>Endereço do vértice</returns>
Vertice* OndeEstaVerticeGrafo(Grafo* g, int idVertice);

/// <summary>
/// Função que insere um vértice no grafo
/// </summary>
/// <param name="g">Endereço do grafo</param>
/// <param name="novo">Endereço do vértice a inserir</param>
/// <param name="resultado">Valor inteiros para verificar se inseriu com sucesso sendo que:
///		 0 -> Vértice inválido;
///		-1 -> Grafo está vazio;
///		-2 -> Vértice já existe no grafo;
/// </param>
/// <returns>Devolve o grafo</returns>
Grafo* InsereVerticeGrafo(Grafo* g, Vertice* novo, int* resultado);

/// <summary>
/// Função que insere uma aresta no grafo
/// </summary>
/// <param name="g">Endereço do grafo</param>
/// <param name="idOrigem">ID de origem da aresta</param>
/// <param name="idDestino">ID de destino da aresta</param>
/// <param name="peso">Peso da aresta</param>
/// <param name="resultado">Valor bool com o resultado da função</param>
/// <returns>Endereço do grafo</returns>
Grafo* InsereArestaGrafo(Grafo* g, int idOrigem, int idDestino,int peso, bool* resultado);

/// <summary>
/// Função que elimina uma aresta do grafo
/// </summary>
/// <param name="g">Endereço do grafo</param>
/// <param name="origem">Origem da arestas</param>
/// <param name="destino">Destino da aresta</param>
/// <param name="resultado">Valor bool com o resultado da função</param>
/// <returns>Endereço do grafo</returns>
Grafo* EliminaArestaGrafo(Grafo* g, int origem, int destino, bool* resultado);
#pragma endregion