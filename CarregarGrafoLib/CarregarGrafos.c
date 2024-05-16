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
/// Contar as linhas e colunas de um ficheiro e verifica qual dos dois é o maior
/// </summary>
/// <param name="nomeFicheiro">Nome do ficheiro no diretório atual</param>
/// <returns>Número inteiro maior</returns>
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
            colunasCorrente++; // Contar a última coluna antes do '\n'
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

    // Contar a última linha, se não terminar com '\n'
    if (!novaLinha) {
        colunasCorrente++;
        if (colunasCorrente > colunas) {
            colunas = colunasCorrente;
        }
        (linhas)++;
    }
    fclose(file);

    //Devolver o número maior
    if (linhas > colunas) return linhas;
    else return colunas;

}

/// <summary>
/// Função para carregar os vértices e arestas para a memória de um ficheiro de texto com o separador ';'
/// </summary>
/// <param name="nomeFicheiro">Nome do ficheiro no diretório atual</param>
/// <returns>Grafo gerado pelo ficheiro dado</returns>
Grafo* CarregarGrafo(const char* nomeFicheiro) {
    //Obter o maior número de colunas ou linhas
    int totalVertices = MaiorLinhasOuColunas(nomeFicheiro);
    if (totalVertices <= 0) return NULL;

    Grafo* grafo = CriaGrafo(totalVertices);
    if (grafo == NULL) return NULL;

    // Inserir vértices
    for (int i = 0; i < totalVertices; i++) {
        Vertice* novoVertice = CriarVertice(i);
        if (novoVertice == NULL) return NULL; // Falha na criação do vértice
        int resultadoInt;
        grafo = InsereVerticeGrafo(grafo, novoVertice, &resultadoInt);
        if (resultadoInt <= 0) return NULL; // Falha na inserção do vértice
    }

    FILE* file = fopen(nomeFicheiro, "r");
    if (file == NULL) return NULL;

    for (int i = 0; i < totalVertices; i++) {
        for (int j = 0; j < totalVertices; j++) {
            int peso = 0;
            char buffer[10]; // Buffer para ler os números do ficheiro

            if (fscanf(file, "%9[^;\n]", buffer) == 1) {
                peso = atoi(buffer); // Converte string para inteiro
            }
            fgetc(file); // Ler e passar á frente o separador ';' ou '\n'

            if (peso > 0) {
                bool resultadoBool;
                grafo = InsereArestaGrafo(grafo, i, j, peso, &resultadoBool);
                if (!resultadoBool) return NULL; // Falha na inserção da aresta
            }
        }
    }

    fclose(file);
    return grafo;
}

