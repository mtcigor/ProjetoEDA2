/*****************************************************************//**
 * \file   GestaoGrafos.c
 * \brief  Ficheiro com as fun��es para gerir os grafos de listas de adjac�ncias
 * 
 * \author Igor a27977@alunos.ipca.pt
 * \date   May 2024
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Grafos.h"


#pragma region Gest�o V�rtices
 /// <summary>
/// Fun��o que destroi um v�rtice
/// </summary>
/// <param name="vertice">Endere�o do v�rtice</param>
void DestroiVertice(Vertice* vertice) {
	free(vertice);
}

/// <summary>
/// Fun��o que mostra o grafo no output do utilizador
/// </summary>
/// <param name="iniciografo">Endere�o do primeiro v�rtice do grafo</param>
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
/// Fun��o que cria um v�rtice (aloca mem�ria) e inicializa os valores como NULL
/// </summary>
/// <param name="id">ID do v�rtice a criar</param>
/// <returns>Endere�o do novo v�rtice</returns>
Vertice* CriarVertice(int id) {
	//Reserva mem�ria para o v�rtice
	Vertice* temp = (Vertice*)malloc(sizeof(Vertice));
	if (temp == NULL) return NULL;
	//Define os valores do novo v�rtice como nulo
	if (id <= -1) return NULL;
	temp->id = id;
	temp->visitado = false;
	temp->proxAresta = NULL;
	temp->proxVertice = NULL;
	return temp;

}

/// <summary>
/// Fun��o que verifica se o v�rtice existe
/// </summary>
/// <param name="inicio">Endere�o do primeiro v�rtice do grafo</param>
/// <param name="id">ID do v�rtice a procurar</param>
/// <returns>Valor bool</returns>
bool ExisteVertice(Vertice* inicio, int id) {
	if (inicio == NULL) return false;
	Vertice* aux = inicio;
	//Loop para passar por todos os v�rtices at� chegar a um apontador null
	while (aux) {
		if (aux->id == id) return true;
		aux = aux->proxVertice;
	}
	return false;
}

/// <summary>
/// Fun��o que procura e devolve o mesmo v�rtice
/// </summary>
/// <param name="inicio">Endere�o do primeiro v�rtice do grafo</param>
/// <param name="id">ID do v�rtice a procurar</param>
/// <returns>Endere�o do v�rtice</returns>
Vertice* GetVertice(Vertice* inicio, int id) {
	if (inicio == NULL) return NULL;
	Vertice* aux = inicio;
	//Loop para passar por todos os v�rtices at� chegar a um apontador null
	while (aux) {
		if (aux->id == id) return aux;
		aux = aux->proxVertice;
	}
	return NULL;
}

/// <summary>
/// Fun��o que insere um v�rtice na lista de v�rtices
/// </summary>
/// <param name="atual">Endere�o de um v�rtice antes do novo v�rtice</param>
/// <param name="novo">Endere�o do novo v�rtice</param>
/// <param name="resultado">Valor bool para verificar se inseriu com sucesso</param>
/// <returns>Devolve o endere�o do novo v�rtice</returns>
Vertice* InserirVertice(Vertice* atual, Vertice* novo, bool* resultado) {
	*resultado = false;
	//Se a lista de v�rtices est� vazia
	if (atual == NULL) {
		*resultado = true;
		atual = novo;
		return atual;
	}

	//Verifica se o v�rtice j� existe
	if (ExisteVertice(atual, novo->id)) {
		return atual;
	}

	//Procurar para inserir o v�rtice
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
/// Fun��o que elimina um v�rtice da lista de v�rtices
/// </summary>
/// <param name="atual">V�rtice da lista antes do v�rtice a eliminar</param>
/// <param name="cod">ID do v�rtice a eliminar</param>
/// <param name="resultado">Valor bool para verificar se removeu com sucesso</param>
/// <returns>Devolve o v�rtice antes do v�rtice eliminado</returns>
Vertice* EliminaVertice(Vertice* atual, int cod, bool* resultado) {
	*resultado = false;
	if (atual == NULL) return NULL;

	Vertice* aux = atual;
	Vertice* antes = NULL;
	while (aux->id != cod) {
		antes = aux;
		aux = aux->proxVertice;
	}
	if (!aux) return atual; //significa que n�o existe o v�rtices

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

#pragma region Gest�o Arestas

/// <summary>
/// Fun��o que destroi uma aresta
/// </summary>
/// <param name="aresta"></param>
void DestroiAresta(Aresta* aresta)
{
	free(aresta);
}

/// <summary>
/// Fun��o que cria uma nova aresta (aloca mem�ria) e inicializa os valores como NULL
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
/// Fun��o que elimina uma aresta da lista de arestas
/// </summary>
/// <param name="lista">In�cio da lista antes da aresta a remover</param>
/// <param name="cod">C�digo idDestino da aresta a eliminar</param>
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
	if (!aux) return lista;	//Ver se a aresta n�o existe
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
/// Fun��o que elimina todas as arestas da lista de arestas (n�o apaga a lista em si)
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
/// Fun��o que insere uma aresta na lista de arestas
/// </summary>
/// <param name="lista">Lista de arestas</param>
/// <param name="peso">Peso da aresta</param>
/// <param name="idDestino">V�rtice destino da aresta</param>
/// <returns>Devolve a aresta</returns>
Aresta* InsereAresta(Aresta* lista,int peso, int idDestino) {
	Aresta* novaAresta;
	if ((novaAresta = NovaAresta(idDestino)) == NULL)
	{
		return lista;	//se n�o conseguiu criar nova adjacencia
	}

	//se lista de adjacencia estava vazia
	if (lista == NULL) {
		lista = novaAresta; //insere a nova adjacencia no inicio
	}
	else
	{
		//por op��o, inserir no fim da LA
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

#pragma region Gest�o Grafos

/// <summary>
/// Fun��o que mostra o grafos no output do utilizador
/// </summary>
/// <param name="gr">Endere�o do grafo</param>
void MostrarGrafoLA(Grafo* gr) {
	MostrarGrafo(gr->inicioGrafo);
}

/// <summary>
/// Fun��o que cria um grafo (aloca mem�ria) e inicializa os valores como NULL
/// </summary>
/// <param name="total">Total de v�rtices no grafo</param>
/// <returns>Endere�o do grafo</returns>
Grafo* CriaGrafo(int total) {
	if (total <= 0) return NULL;
	Grafo* grafo = (Grafo*)malloc(sizeof(Grafo*));
	if (grafo == NULL) return NULL;
	grafo->totVertices = total;
	grafo->inicioGrafo = NULL;
}

/// <summary>
/// Verifica se existe um v�rtice no grafo
/// </summary>
/// <param name="g">Endere�o do grafo</param>
/// <param name="idVertice">ID do v�rtice</param>
/// <returns>Devolve um valor bool</returns>
bool ExisteVerticeGrafo(Grafo* g, int idVertice) {
	if (g == NULL) return false;
	return (ExisteVertice(g->inicioGrafo, idVertice));
}

/// <summary>
/// Fun��o que procura e devolve o v�rtice no grafo
/// </summary>
/// <param name="g">Endere�o do grafo</param>
/// <param name="idVertice">ID do v�rtice</param>
/// <returns>Endere�o do v�rtice</returns>
Vertice* OndeEstaVerticeGrafo(Grafo* g, int idVertice) {
	if (g == NULL) return NULL;
	return (GetVertice(g->inicioGrafo, idVertice));
}
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
Grafo* InsereVerticeGrafo(Grafo* g, Vertice* novo, int* resultado) {
	*resultado = 1;
	//valida��es
	if (novo == NULL) { //vertice invalido
		*resultado = 0;
		return g;
	}
	if (g == NULL) { // grafo vazio
		*resultado = -1;
		return NULL;
	}
	//verificar se V j� existe no grafo
	if (ExisteVerticeGrafo(g, novo->id)) { //vertice desconhecido
		*resultado = -2;
		return g;
	}
	g->inicioGrafo = InserirVertice(g->inicioGrafo, novo, resultado);
	return g;
}
/// <summary>
/// Fun��o que insere uma aresta no grafo
/// </summary>
/// <param name="g">Endere�o do grafo</param>
/// <param name="idOrigem">ID de origem da aresta</param>
/// <param name="idDestino">ID de destino da aresta</param>
/// <param name="peso">Peso da aresta</param>
/// <param name="resultado">Valor bool com o resultado da fun��o</param>
/// <returns>Endere�o do grafo</returns>
Grafo* InsereArestaGrafo(Grafo* g, int idOrigem, int idDestino, int peso, bool* resultado) {

	*resultado = false;
	//Valida��es
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
/// Fun��o que elimina uma aresta do grafo
/// </summary>
/// <param name="g">Endere�o do grafo</param>
/// <param name="origem">Origem da arestas</param>
/// <param name="destino">Destino da aresta</param>
/// <param name="resultado">Valor bool com o resultado da fun��o</param>
/// <returns>Endere�o do grafo</returns>
Grafo* EliminaArestaGrafo(Grafo* g, int origem, int destino, bool* resultado) {

	*resultado = false;

	//valida��es
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

