/*****************************************************************//**
 * \file   CarregarGrafos.h
 * \brief  Cabe�alho com as fun��es para carregar e manipular grafos com ficheiros
 * 
 * \author Igor a27977@alunos.ipca.pt
 * \date   May 2024
 *********************************************************************/
#pragma once

#include "Grafos.h"

 /// <summary>
 /// Contar as linhas e colunas de um ficheiro e verifica qual dos dois � o maior
 /// </summary>
 /// <param name="nomeFicheiro">Nome do ficheiro no diret�rio atual</param>
 /// <returns>N�mero inteiro maior</returns>
int MaiorLinhasOuColunas(const char* nomeFicheiro);

/// <summary>
/// Fun��o para carregar os v�rtices e arestas para a mem�ria de um ficheiro de texto com o separador ';'
/// </summary>
/// <param name="nomeFicheiro">Nome do ficheiro no diret�rio atual</param>
/// <returns>Grafo gerado pelo ficheiro dado</returns>
Grafo* CarregarGrafo(const char* nomeFicheiro);

/// <summary>
/// Fun��o para carregar um grafo de um ficheiro bin�rio
/// </summary>
/// <param name="nomeFicheiro">Nome do ficheiro a guardar</param>
/// <returns>Grafo gerado pelo ficheiro dado</returns>
Grafo* CarregarGrafoBinario(const char* nomeFicheiro);

/// <summary>
/// Guarda o grafo num ficheiro de texto com o separador ';'
/// </summary>
/// <param name="nomeFicheiro">Nome do ficheiro a guardar</param>
/// <param name="grafo">Grafo em quest�o a guardar</param>
/// <returns>Devolve um valor bool a indicar de guardou o ficheiro com sucesso ou n�o</returns>
bool GuardarGrafo(const char* nomeFicheiro, Grafo* grafo);

/// <summary>
/// Fun��o que guarda um grafo num ficheiro bin�rio
/// </summary>
/// <param name="nomeFicheiro">Nome do ficheiro a guardar</param>
/// <param name="grafo">Grafo a guardar</param>
/// <returns>>Devolve um valor bool a indicar de guardou o ficheiro com sucesso ou n�o</returns>
bool GuardarGrafoBinario(const char* nomeFicheiro, Grafo* grafo);