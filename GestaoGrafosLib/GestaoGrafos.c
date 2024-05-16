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
/// 
/// </summary>
/// <param name="vertice"></param>
void DestroiVertice(Vertice* vertice) {
	free(vertice);
}

/// <summary>
/// 
/// </summary>
/// <param name="iniciografo"></param>
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
/// 
/// </summary>
/// <param name="id"></param>
/// <returns></returns>
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
/// 
/// </summary>
/// <param name="inicio"></param>
/// <param name="id"></param>
/// <returns></returns>
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
/// 
/// </summary>
/// <param name="inicio"></param>
/// <param name="id"></param>
/// <returns></returns>
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
/// 
/// </summary>
/// <param name="atual"></param>
/// <param name="novo"></param>
/// <param name="resultado"></param>
/// <returns></returns>
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
/// 
/// </summary>
/// <param name="atual"></param>
/// <param name="cod"></param>
/// <param name="resultado"></param>
/// <returns></returns>
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
/// 
/// </summary>
/// <param name="aresta"></param>
void DestroiAresta(Aresta* aresta)
{
	free(aresta);
}

/// <summary>
/// 
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
/// 
/// </summary>
/// <param name="lista"></param>
/// <param name="cod"></param>
/// <param name="resultado"></param>
/// <returns></returns>
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
/// 
/// </summary>
/// <param name="lista"></param>
/// <param name="resultado"></param>
/// <returns></returns>
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
/// 
/// </summary>
/// <param name="lista"></param>
/// <param name="peso"></param>
/// <param name="idDestino"></param>
/// <returns></returns>
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
/// Mostra os grafos
/// </summary>
/// <param name="gr"></param>
void MostrarGrafoLA(Grafo* gr) {
	MostrarGrafo(gr->inicioGrafo);
}

/// <summary>
/// 
/// </summary>
/// <param name="total"></param>
/// <returns></returns>
Grafo* CriaGrafo(int total) {
	if (total <= 0) return NULL;
	Grafo* grafo = (Grafo*)malloc(sizeof(Grafo*));
	if (grafo == NULL) return NULL;
	grafo->totVertices = total;
	grafo->inicioGrafo = NULL;
}

/// <summary>
/// 
/// </summary>
/// <param name="g"></param>
/// <param name="idVertice"></param>
/// <returns></returns>
bool ExisteVerticeGrafo(Grafo* g, int idVertice) {
	if (g == NULL) return false;
	return (ExisteVertice(g->inicioGrafo, idVertice));
}

/// <summary>
/// 
/// </summary>
/// <param name="g"></param>
/// <param name="idVertice"></param>
/// <returns></returns>
Vertice* OndeEstaVerticeGrafo(Grafo* g, int idVertice) {
	if (g == NULL) return NULL;
	return (GetVertice(g->inicioGrafo, idVertice));
}
/// <summary>
/// 
/// </summary>
/// <param name="g"></param>
/// <param name="novo"></param>
/// <param name="resultado"></param>
/// <returns></returns>
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
	//verificar se V já existe no grafo...
	if (ExisteVerticeGrafo(g, novo->id)) { //vertice desconhecido
		*resultado = -2;
		return g;
	}
	g->inicioGrafo = InserirVertice(g->inicioGrafo, novo, resultado);
	return g;
}
/// <summary>
/// 
/// </summary>
/// <param name="g"></param>
/// <param name="idOrigem"></param>
/// <param name="idDestino"></param>
/// <param name="peso"></param>
/// <param name="resultado"></param>
/// <returns></returns>
Grafo* InsereArestaGrafo(Grafo* g, int idOrigem, int idDestino, int peso, bool* resultado) {

	*resultado = false;
	//Validações
	if (g == NULL) return NULL;
	//Verificar se vertices existem
	Vertice* originVertice = OndeEstaVerticeGrafo(g, idOrigem);
	if (originVertice == NULL) return g;
	Vertice* destinyVertice = OndeEstaVerticeGrafo(g, idDestino);
	if (!destinyVertice) return g;

	originVertice->proxAresta = InsereAresta(originVertice->proxAresta, peso, idDestino);

	*resultado = true;
	return g;
}

/// <summary>
/// 
/// </summary>
/// <param name="g"></param>
/// <param name="origem"></param>
/// <param name="destino"></param>
/// <param name="resultado"></param>
/// <returns></returns>
Grafo* EliminaAdjGrafo(Grafo* g, int origem, int destino, bool* resultado) {

	*resultado = false;

	//validações
	if (g == NULL) return NULL;
	//Verificar se vertices existem
	Vertice* originVertice = OndeEstaVerticeGrafo(g, origem);
	if (originVertice == NULL) return g;
	Vertice* destinyVertice = OndeEstaVerticeGrafo(g, destino);
	if (!destinyVertice) return g;

	originVertice->proxAresta = EliminarAresta(originVertice->proxAresta, destino, resultado);
	return g;
}
#pragma endregion

