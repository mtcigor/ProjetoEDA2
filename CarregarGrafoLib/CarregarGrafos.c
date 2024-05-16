/*****************************************************************//**
 * \file   CarregarGrafos.c
 * \brief  
 * 
 * \author mtcig
 * \date   May 2024
 *********************************************************************/

#pragma warning (disable: 4996)

#include "Grafos.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/// <summary>
/// Contar as linhas e colunas de um ficheiro e verifica qual dos dois � o maior
/// </summary>
/// <param name="nomeFicheiro">Nome do ficheiro no diret�rio atual</param>
/// <returns>N�mero inteiro maior</returns>
int MaiorLinhasOuColunas(const char *nomeFicheiro) {
    FILE* file = fopen(nomeFicheiro, "r");
    if (file == NULL)  return -1;

    char c;
    int linhas = 0;
    int colunas = 0;
    int colunasCorrente = 0;
    bool novaLinha = true;

    while ((c = fgetc(file)) != EOF) {
        if (c == ';') {
            colunasCorrente++;
        }
        else if (c == '\n') {
            colunasCorrente++; // Contar a �ltima coluna antes do '\n'
            if (colunasCorrente > colunas) {
                colunas = colunasCorrente;
            }
            colunasCorrente = 0;
            (linhas)++;
            novaLinha = true;
        }
        else {
            novaLinha = false;
        }
    }

    // Contar a �ltima linha, se n�o terminar com '\n'
    if (!novaLinha) {
        colunasCorrente++;
        if (colunasCorrente > colunas) {
            colunas = colunasCorrente;
        }
        (linhas)++;
    }
    fclose(file);

    //Devolver o n�mero maior
    if (linhas > colunas) return linhas;
    else return colunas;

}

/// <summary>
/// Fun��o para carregar os v�rtices e arestas para a mem�ria de um ficheiro de texto com o separador ';'
/// </summary>
/// <param name="nomeFicheiro">Nome do ficheiro no diret�rio atual</param>
/// <returns>Grafo gerado pelo ficheiro dado</returns>
Grafo* CarregarGrafo(const char* nomeFicheiro) {
    //Obter o maior n�mero de colunas ou linhas
    int totalVertices = MaiorLinhasOuColunas(nomeFicheiro);
    if (totalVertices <= 0) return NULL;

    Grafo* grafo = CriaGrafo(totalVertices);
    if (grafo == NULL) return NULL;

    // Inserir v�rtices
    for (int i = 0; i < totalVertices; i++) {
        Vertice* novoVertice = CriarVertice(i);
        if (novoVertice == NULL) return NULL; // Falha na cria��o do v�rtice
        int resultadoInt;
        grafo = InsereVerticeGrafo(grafo, novoVertice, &resultadoInt);
        if (resultadoInt <= 0) return NULL; // Falha na inser��o do v�rtice
    }

    FILE* file = fopen(nomeFicheiro, "r");
    if (file == NULL) return NULL;

    for (int i = 0; i < totalVertices; i++) {
        for (int j = 0; j < totalVertices; j++) {
            int peso = 0;
            char buffer[10]; // Buffer para ler os n�meros do ficheiro

            if (fscanf(file, "%9[^;\n]", buffer) == 1) {
                peso = atoi(buffer); // Converte string para inteiro
            }
            fgetc(file); // Ler e passar � frente o separador ';' ou '\n'

            if (peso > 0) {
                bool resultadoBool;
                grafo = InsereArestaGrafo(grafo, i, j, peso, &resultadoBool);
                if (!resultadoBool) return NULL; // Falha na inser��o da aresta
            }
        }
    }

    fclose(file);
    return grafo;
}

