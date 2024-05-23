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


void EncontrarCaminhosDFS(Grafo* g, Vertice* verticeAtual, int idDestino, Caminho* caminhoAtual, Caminho** caminhos, int* numCaminhos, int maxTamanho);
Caminho** ObterTodosCaminhos(Grafo* grafo, int idOrigem, int idDestino, int* numCaminhos);

void InicializaCaminho(Caminho* caminho, int maxTamanho);
void LiberaCaminho(Caminho* caminho);
void AdicionaVerticeNoCaminho(Caminho* caminho, int vertice);
void ImprimeCaminho(Caminho* caminho);
