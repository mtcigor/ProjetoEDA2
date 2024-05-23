/*****************************************************************//**
 * \file   GestaoGrafos.c
 * \brief  Ficheiro com as funções para gerir os grafos de listas de adjacências
 * 
 * \author Igor a27977@alunos.ipca.pt
 * \date   May 2024
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Grafos.h"


#pragma region Gestão Vértices
 /// <summary>
/// Função que destroi um vértice
/// </summary>
/// <param name="vertice">Endereço do vértice</param>
void DestroiVertice(Vertice* vertice) {
	free(vertice);
}

/// <summary>
/// Função que mostra o grafo no output do utilizador
/// </summary>
/// <param name="iniciografo">Endereço do primeiro vértice do grafo</param>
void MostrarGrafo(Vertice* iniciografo) {
	Vertice* atual = iniciografo;
	while (atual != NULL) {
		printf("%d:\n ", atual->id);
		Aresta* atualAresta = atual->proxAresta;
		while (atualAresta != NULL)
		{
			printf("\t");
			printf("aresta: %d\n", atualAresta->idDestino);
			atualAresta = atualAresta->prox;
		}
		atual = atual->proxVertice;
	}
}

/// <summary>
/// Função que cria um vértice (aloca memória) e inicializa os valores como NULL
/// </summary>
/// <param name="id">ID do vértice a criar</param>
/// <returns>Endereço do novo vértice</returns>
Vertice* CriarVertice(int id) {
	//Reserva memória para o vértice
	Vertice* temp = (Vertice*)malloc(sizeof(Vertice));
	if (temp == NULL) return NULL;
	//Define os valores do novo vértice como nulo
	if (id <= -1) return NULL;
	temp->id = id;
	temp->visitado = false;
	temp->proxAresta = NULL;
	temp->proxVertice = NULL;
	return temp;

}

/// <summary>
/// Função que verifica se o vértice existe
/// </summary>
/// <param name="inicio">Endereço do primeiro vértice do grafo</param>
/// <param name="id">ID do vértice a procurar</param>
/// <returns>Valor bool</returns>
bool ExisteVertice(Vertice* inicio, int id) {
	if (inicio == NULL) return false;
	Vertice* aux = inicio;
	//Loop para passar por todos os vértices até chegar a um apontador null
	while (aux) {
		if (aux->id == id) return true;
		aux = aux->proxVertice;
	}
	return false;
}

/// <summary>
/// Função que procura e devolve o mesmo vértice
/// </summary>
/// <param name="inicio">Endereço do primeiro vértice do grafo</param>
/// <param name="id">ID do vértice a procurar</param>
/// <returns>Endereço do vértice</returns>
Vertice* GetVertice(Vertice* inicio, int id) {
	if (inicio == NULL) return NULL;
	Vertice* aux = inicio;
	//Loop para passar por todos os vértices até chegar a um apontador null
	while (aux) {
		if (aux->id == id) return aux;
		aux = aux->proxVertice;
	}
	return NULL;
}

/// <summary>
/// Função que insere um vértice na lista de vértices
/// </summary>
/// <param name="atual">Endereço de um vértice antes do novo vértice</param>
/// <param name="novo">Endereço do novo vértice</param>
/// <param name="resultado">Valor bool para verificar se inseriu com sucesso</param>
/// <returns>Devolve o endereço do novo vértice</returns>
Vertice* InserirVertice(Vertice* atual, Vertice* novo, bool* resultado) {
	*resultado = false;
	//Se a lista de vértices está vazia
	if (atual == NULL) {
		*resultado = true;
		atual = novo;
		return atual;
	}

	//Verifica se o vértice já existe
	if (ExisteVertice(atual, novo->id)) {
		return atual;
	}

	//Procurar para inserir o vértice
	Vertice* antes = NULL;
	Vertice* aux = atual;
	while (aux != NULL && aux->id < novo->id) {
		antes = aux;
		aux = aux->proxVertice;
	}

	*resultado = true;
	if (antes == NULL) {
		novo->proxVertice = atual;
		atual = novo;
	}
	else {
		novo->proxVertice = aux;
		antes->proxVertice = novo;
	}
	return atual;

}

/// <summary>
/// Função que elimina um vértice da lista de vértices
/// </summary>
/// <param name="atual">Vértice da lista antes do vértice a eliminar</param>
/// <param name="cod">ID do vértice a eliminar</param>
/// <param name="resultado">Valor bool para verificar se removeu com sucesso</param>
/// <returns>Devolve o vértice antes do vértice eliminado</returns>
Vertice* EliminaVertice(Vertice* atual, int cod, bool* resultado) {
	*resultado = false;
	if (atual == NULL) return NULL;

	Vertice* aux = atual;
	Vertice* antes = NULL;
	while (aux->id != cod) {
		antes = aux;
		aux = aux->proxVertice;
	}
	if (!aux) return atual; //significa que não existe o vértices

	if (antes == NULL) {
		//apaga todas adjacencias do vertice a eliminar
		aux->proxAresta = ElimiminaAllArestas(aux->proxAresta, resultado);
		if (*resultado == false) return atual;
		atual = aux->proxVertice;
	}
	else {
		//apaga vertice
		antes->proxVertice = aux->proxVertice;
	}
	DestroiVertice(aux);
	*resultado = true;
	return atual;
}
#pragma endregion

#pragma region Gestão Arestas

/// <summary>
/// Função que destroi uma aresta
/// </summary>
/// <param name="aresta"></param>
void DestroiAresta(Aresta* aresta)
{
	free(aresta);
}

/// <summary>
/// Função que cria uma nova aresta (aloca memória) e inicializa os valores como NULL
/// </summary>
/// <param name="idDestino"></param>
/// <returns></returns>
Aresta* NovaAresta(int idDestino)
{
	Aresta* aresta;

	aresta = (Aresta*)malloc(sizeof(Aresta));
	if (aresta == NULL)
	{
		return NULL;
	}
	aresta->idDestino = idDestino;
	aresta->prox = NULL;
	return aresta;
}

/// <summary>
/// Função que elimina uma aresta da lista de arestas
/// </summary>
/// <param name="lista">Início da lista antes da aresta a remover</param>
/// <param name="cod">Código idDestino da aresta a eliminar</param>
/// <param name="resultado">Valor bool para verificar se removeu com sucesso</param>
/// <returns>Desvolve a aresta anterior a do que foi removida</returns>
Aresta* EliminarAresta(Aresta* lista, int cod, bool* resultado) {
	*resultado = false;
	if (lista == NULL) return NULL;
	Aresta* aux = lista;
	Aresta* antes = NULL;
	while (aux && aux->idDestino != cod) {
		antes = aux;
		aux = aux->prox;
	}
	if (!aux) return lista;	//Ver se a aresta não existe
	if (antes == NULL)
	{
		lista = aux->prox;
	}
	else {
		antes->prox = aux->prox;
	}
	DestroiAresta(aux);
	*resultado = true;
	return lista;
}

/// <summary>
/// Função que elimina todas as arestas da lista de arestas (não apaga a lista em si)
/// </summary>
/// <param name="lista">Lista a eliminar</param>
/// <param name="resultado">Valor bool para verificar se removeu com sucesso</param>
/// <returns>Devolve a lista vazia</returns>
Aresta* ElimiminaAllArestas(Aresta* lista, bool* resultado) {
	*resultado = false;
	if (lista == NULL) return NULL;

	//percorre lista de adjacencia
	Aresta* aux = lista;
	while (aux) {
		if (aux)
			lista = aux->prox;
		DestroiAresta(aux);
		aux = lista;
	}
	lista = NULL;
	*resultado = true;
	return lista;
}

/// <summary>
/// Função que insere uma aresta na lista de arestas
/// </summary>
/// <param name="lista">Lista de arestas</param>
/// <param name="peso">Peso da aresta</param>
/// <param name="idDestino">Vértice destino da aresta</param>
/// <returns>Devolve a aresta</returns>
Aresta* InsereAresta(Aresta* lista,int peso, int idDestino) {
	Aresta* novaAresta;
	if ((novaAresta = NovaAresta(idDestino)) == NULL)
	{
		return lista;	//se não conseguiu criar nova adjacencia
	}

	//se lista de adjacencia estava vazia
	if (lista == NULL) {
		lista = novaAresta; //insere a nova adjacencia no inicio
	}
	else
	{
		//por opção, inserir no fim da LA
		Aresta* aux = lista;
		while (aux->prox != NULL)
		{
			aux = aux->prox;
		}
		aux->prox = novaAresta;
	}
	novaAresta->peso = peso;
	return lista;
}
#pragma endregion

#pragma region Gestão Grafos

/// <summary>
/// Função que mostra o grafos no output do utilizador
/// </summary>
/// <param name="gr">Endereço do grafo</param>
void MostrarGrafoLA(Grafo* gr) {
	MostrarGrafo(gr->inicioGrafo);
}

/// <summary>
/// Função que cria um grafo (aloca memória) e inicializa os valores como NULL
/// </summary>
/// <param name="total">Total de vértices no grafo</param>
/// <returns>Endereço do grafo</returns>
Grafo* CriaGrafo(int total) {
	if (total <= 0) return NULL;
	Grafo* grafo = (Grafo*)malloc(sizeof(Grafo*));
	if (grafo == NULL) return NULL;
	grafo->totVertices = total;
	grafo->inicioGrafo = NULL;
}

/// <summary>
/// Verifica se existe um vértice no grafo
/// </summary>
/// <param name="g">Endereço do grafo</param>
/// <param name="idVertice">ID do vértice</param>
/// <returns>Devolve um valor bool</returns>
bool ExisteVerticeGrafo(Grafo* g, int idVertice) {
	if (g == NULL) return false;
	return (ExisteVertice(g->inicioGrafo, idVertice));
}

/// <summary>
/// Função que procura e devolve o vértice no grafo
/// </summary>
/// <param name="g">Endereço do grafo</param>
/// <param name="idVertice">ID do vértice</param>
/// <returns>Endereço do vértice</returns>
Vertice* OndeEstaVerticeGrafo(Grafo* g, int idVertice) {
	if (g == NULL) return NULL;
	return (GetVertice(g->inicioGrafo, idVertice));
}
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
Grafo* InsereVerticeGrafo(Grafo* g, Vertice* novo, int* resultado) {
	*resultado = 1;
	//validações
	if (novo == NULL) { //vertice invalido
		*resultado = 0;
		return g;
	}
	if (g == NULL) { // grafo vazio
		*resultado = -1;
		return NULL;
	}
	//verificar se V já existe no grafo
	if (ExisteVerticeGrafo(g, novo->id)) { //vertice desconhecido
		*resultado = -2;
		return g;
	}
	g->inicioGrafo = InserirVertice(g->inicioGrafo, novo, resultado);
	return g;
}
/// <summary>
/// Função que insere uma aresta no grafo
/// </summary>
/// <param name="g">Endereço do grafo</param>
/// <param name="idOrigem">ID de origem da aresta</param>
/// <param name="idDestino">ID de destino da aresta</param>
/// <param name="peso">Peso da aresta</param>
/// <param name="resultado">Valor bool com o resultado da função</param>
/// <returns>Endereço do grafo</returns>
Grafo* InsereArestaGrafo(Grafo* g, int idOrigem, int idDestino, int peso, bool* resultado) {

	*resultado = false;
	//Validações
	if (g == NULL) return NULL;
	//Verificar se vertices existem
	Vertice* origemVertice = OndeEstaVerticeGrafo(g, idOrigem);
	if (origemVertice == NULL) return g;
	Vertice* destinoVertice = OndeEstaVerticeGrafo(g, idDestino);
	if (!destinoVertice) return g;

	origemVertice->proxAresta = InsereAresta(origemVertice->proxAresta, peso, idDestino);

	*resultado = true;
	return g;
}

/// <summary>
/// Função que elimina uma aresta do grafo
/// </summary>
/// <param name="g">Endereço do grafo</param>
/// <param name="origem">Origem da arestas</param>
/// <param name="destino">Destino da aresta</param>
/// <param name="resultado">Valor bool com o resultado da função</param>
/// <returns>Endereço do grafo</returns>
Grafo* EliminaArestaGrafo(Grafo* g, int origem, int destino, bool* resultado) {

	*resultado = false;

	//validações
	if (g == NULL) return NULL;
	//Verificar se vertices existem
	Vertice* origemVertice = OndeEstaVerticeGrafo(g, origem);
	if (origemVertice == NULL) return g;
	Vertice* destinoVertice = OndeEstaVerticeGrafo(g, destino);
	if (!destinoVertice) return g;

	origemVertice->proxAresta = EliminarAresta(origemVertice->proxAresta, destino, resultado);
	return g;
}
#pragma endregion

