/*****************************************************************//**
 * \file   CarregarGrafos.h
 * \brief  Cabeçalho com as funções para carregar e manipular grafos com ficheiros
 * 
 * \author Igor a27977@alunos.ipca.pt
 * \date   May 2024
 *********************************************************************/
#pragma once

#include "Grafos.h"

 /// <summary>
 /// Contar as linhas e colunas de um ficheiro e verifica qual dos dois é o maior
 /// </summary>
 /// <param name="nomeFicheiro">Nome do ficheiro no diretório atual</param>
 /// <returns>Número inteiro maior</returns>
int MaiorLinhasOuColunas(const char* nomeFicheiro);

/// <summary>
/// Função para carregar os vértices e arestas para a memória de um ficheiro de texto com o separador ';'
/// </summary>
/// <param name="nomeFicheiro">Nome do ficheiro no diretório atual</param>
/// <returns>Grafo gerado pelo ficheiro dado</returns>
Grafo* CarregarGrafo(const char* nomeFicheiro);

/// <summary>
/// Função para carregar um grafo de um ficheiro binário
/// </summary>
/// <param name="nomeFicheiro">Nome do ficheiro a guardar</param>
/// <returns>Grafo gerado pelo ficheiro dado</returns>
Grafo* CarregarGrafoBinario(const char* nomeFicheiro);

/// <summary>
/// Guarda o grafo num ficheiro de texto com o separador ';'
/// </summary>
/// <param name="nomeFicheiro">Nome do ficheiro a guardar</param>
/// <param name="grafo">Grafo em questão a guardar</param>
/// <returns>Devolve um valor bool a indicar de guardou o ficheiro com sucesso ou não</returns>
bool GuardarGrafo(const char* nomeFicheiro, Grafo* grafo);

/// <summary>
/// Função que guarda um grafo num ficheiro binário
/// </summary>
/// <param name="nomeFicheiro">Nome do ficheiro a guardar</param>
/// <param name="grafo">Grafo a guardar</param>
/// <returns>>Devolve um valor bool a indicar de guardou o ficheiro com sucesso ou não</returns>
bool GuardarGrafoBinario(const char* nomeFicheiro, Grafo* grafo);