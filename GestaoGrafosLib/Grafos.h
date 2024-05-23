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
/// <summary>
/// Fun��o que destroi um v�rtice
/// </summary>
/// <param name="vertice">Endere�o do v�rtice</param>
void DestroiVertice(Vertice* vertice);

/// <summary>
/// Fun��o que mostra o grafo no output do utilizador
/// </summary>
/// <param name="iniciografo">Endere�o do primeiro v�rtice do grafo</param>
void MostrarGrafo(Vertice* grafo);

/// <summary>
/// Fun��o que cria um v�rtice (aloca mem�ria) e inicializa os valores como NULL
/// </summary>
/// <param name="id">ID do v�rtice a criar</param>
/// <returns>Endere�o do novo v�rtice</returns>
Vertice* CriarVertice(int id);

/// <summary>
/// Fun��o que verifica se o v�rtice existe
/// </summary>
/// <param name="inicio">Endere�o do primeiro v�rtice do grafo</param>
/// <param name="id">ID do v�rtice a procurar</param>
/// <returns>Valor bool</returns>
bool ExisteVertice(Vertice* inicio, int id);

/// <summary>
/// Fun��o que procura e devolve o mesmo v�rtice
/// </summary>
/// <param name="inicio">Endere�o do primeiro v�rtice do grafo</param>
/// <param name="id">ID do v�rtice a procurar</param>
/// <returns>Endere�o do v�rtice</returns>
Vertice* GetVertice(Vertice* inicio, int id);

/// <summary>
/// Fun��o que insere um v�rtice na lista de v�rtices
/// </summary>
/// <param name="atual">Endere�o de um v�rtice antes do novo v�rtice</param>
/// <param name="novo">Endere�o do novo v�rtice</param>
/// <param name="resultado">Valor bool para verificar se inseriu com sucesso</param>
/// <returns>Devolve o endere�o do novo v�rtice</returns>
Vertice* InserirVertice(Vertice* atual, Vertice* novo, bool* resultado);

/// <summary>
/// Fun��o que elimina um v�rtice da lista de v�rtices
/// </summary>
/// <param name="atual">V�rtice da lista antes do v�rtice a eliminar</param>
/// <param name="cod">ID do v�rtice a eliminar</param>
/// <param name="resultado">Valor bool para verificar se removeu com sucesso</param>
/// <returns>Devolve o v�rtice antes do v�rtice eliminado</returns>
Vertice* EliminaVertice(Vertice* atual, int cod, bool* resultado);
#pragma endregion
#pragma region Assinatura Gest�o Arestas
/// <summary>
/// Fun��o que destroi uma aresta
/// </summary>
/// <param name="aresta"></param>
void DestroiAresta(Aresta* aresta);

/// <summary>
/// Fun��o que cria uma nova aresta (aloca mem�ria) e inicializa os valores como NULL
/// </summary>
/// <param name="idDestino"></param>
/// <returns></returns>
Aresta* NovaAresta(int idDestino);

/// <summary>
/// Fun��o que elimina uma aresta da lista de arestas
/// </summary>
/// <param name="lista">In�cio da lista antes da aresta a remover</param>
/// <param name="cod">C�digo idDestino da aresta a eliminar</param>
/// <param name="resultado">Valor bool para verificar se removeu com sucesso</param>
/// <returns>Desvolve a aresta anterior a do que foi removida</returns>
Aresta* EliminarAresta(Aresta* lista, int cod, bool* resultado);

/// <summary>
/// Fun��o que elimina todas as arestas da lista de arestas (n�o apaga a lista em si)
/// </summary>
/// <param name="lista">Lista a eliminar</param>
/// <param name="resultado">Valor bool para verificar se removeu com sucesso</param>
/// <returns>Devolve a lista vazia</returns>
Aresta* ElimiminaAllArestas(Aresta* lista, bool* resultado);

/// <summary>
/// Fun��o que insere uma aresta na lista de arestas
/// </summary>
/// <param name="lista">Lista de arestas</param>
/// <param name="peso">Peso da aresta</param>
/// <param name="idDestino">V�rtice destino da aresta</param>
/// <returns>Devolve a aresta</returns>
Aresta* InsereAresta(Aresta* lista,int peso, int idDestino);
#pragma endregion
#pragma region Assinatura Gest�o Grafos
/// <summary>
/// Fun��o que mostra o grafos no output do utilizador
/// </summary>
/// <param name="gr">Endere�o do grafo</param>
void MostrarGrafoLA(Grafo* gr);

/// <summary>
/// Fun��o que cria um grafo (aloca mem�ria) e inicializa os valores como NULL
/// </summary>
/// <param name="total">Total de v�rtices no grafo</param>
/// <returns>Endere�o do grafo</returns>
Grafo* CriaGrafo(int total);

/// <summary>
/// Verifica se existe um v�rtice no grafo
/// </summary>
/// <param name="g">Endere�o do grafo</param>
/// <param name="idVertice">ID do v�rtice</param>
/// <returns>Devolve um valor bool</returns>
bool ExisteVerticeGrafo(Grafo* g, int idVertice);

/// <summary>
/// Fun��o que procura e devolve o v�rtice no grafo
/// </summary>
/// <param name="g">Endere�o do grafo</param>
/// <param name="idVertice">ID do v�rtice</param>
/// <returns>Endere�o do v�rtice</returns>
Vertice* OndeEstaVerticeGrafo(Grafo* g, int idVertice);

/// <summary>
/// Fun��o que insere um v�rtice no grafo
/// </summary>
/// <param name="g">Endere�o do grafo</param>
/// <param name="novo">Endere�o do v�rtice a inserir</param>
/// <param name="resultado">Valor inteiros para verificar se inseriu com sucesso sendo que:
///		 0 -> V�rtice inv�lido;
///		-1 -> Grafo est� vazio;
///		-2 -> V�rtice j� existe no grafo;
/// </param>
/// <returns>Devolve o grafo</returns>
Grafo* InsereVerticeGrafo(Grafo* g, Vertice* novo, int* resultado);

/// <summary>
/// Fun��o que insere uma aresta no grafo
/// </summary>
/// <param name="g">Endere�o do grafo</param>
/// <param name="idOrigem">ID de origem da aresta</param>
/// <param name="idDestino">ID de destino da aresta</param>
/// <param name="peso">Peso da aresta</param>
/// <param name="resultado">Valor bool com o resultado da fun��o</param>
/// <returns>Endere�o do grafo</returns>
Grafo* InsereArestaGrafo(Grafo* g, int idOrigem, int idDestino,int peso, bool* resultado);

/// <summary>
/// Fun��o que elimina uma aresta do grafo
/// </summary>
/// <param name="g">Endere�o do grafo</param>
/// <param name="origem">Origem da arestas</param>
/// <param name="destino">Destino da aresta</param>
/// <param name="resultado">Valor bool com o resultado da fun��o</param>
/// <returns>Endere�o do grafo</returns>
Grafo* EliminaArestaGrafo(Grafo* g, int origem, int destino, bool* resultado);
#pragma endregion