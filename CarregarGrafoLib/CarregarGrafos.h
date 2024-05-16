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