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