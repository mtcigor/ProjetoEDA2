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
        if (c == ';') colunasCorrente++;
        else if (c == '\n') {
            colunasCorrente++; // Contar a �ltima coluna antes do '\n'
            if (colunasCorrente > colunas) {
                colunas = colunasCorrente;
            }
            colunasCorrente = 0;
            (linhas)++;
            novaLinha = true;
        }
        else novaLinha = false;
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

/// <summary>
/// Guarda o grafo num ficheiro de texto com o separador ';'
/// </summary>
/// <param name="nomeFicheiro">Nome do ficheiro a guardar</param>
/// <param name="grafo">Grafo em quest�o a guardar</param>
/// <returns>Devolve um valor bool a indicar de guardou o ficheiro com sucesso ou n�o</returns>
bool GuardarGrafo(const char* nomeFicheiro, Grafo* grafo) {
	FILE* file = fopen(nomeFicheiro, "w");
	if (file == NULL) return false;

    int total = grafo->totVertices;
    Vertice* vertice = grafo->inicioGrafo;

    for (int i = 0; i < total; i++) { //Percorre os v�rtices
        Aresta* aresta = vertice->proxAresta;
        for (int j = 0; j < total; j++) { //Percorre as arestas
            if (j == i) fprintf(file, ";");
            fprintf(file, "%d", aresta->peso);
            if (aresta->prox != NULL) { //Se a pr�xima aresta n�o for nula
                fprintf(file, ";");
                aresta = aresta->prox;
            } 
            else {
                if (i + 1 == total) fprintf(file, ";"); //Se for o ult�mo v�rtice adiciona um ';'
                fprintf(file, "\n");
                break;
            } 
        }
        vertice = vertice->proxVertice;
    }
	fclose(file);
	return true;
}

/// <summary>
/// Fun��o que guarda um grafo num ficheiro bin�rio
/// </summary>
/// <param name="nomeFicheiro">Nome do ficheiro a guardar</param>
/// <param name="grafo">Grafo a guardar</param>
/// <returns>>Devolve um valor bool a indicar de guardou o ficheiro com sucesso ou n�o</returns>
bool GuardarGrafoBinario(const char* nomeFicheiro, Grafo* grafo) {
    FILE* file = fopen(nomeFicheiro, "wb");
    if (file == NULL) return false;

    // Escreve o n�mero total de v�rtices
    fwrite(&grafo->totVertices, sizeof(int), 1, file);

    Vertice* verticeAtual = grafo->inicioGrafo;
    while (verticeAtual != NULL) {

        // Conta e escreve o n�mero de arestas do v�rtice atual
        int numArestas = 0;
        Aresta* arestaAtual = verticeAtual->proxAresta;
        while (arestaAtual != NULL) {
            numArestas++;
            arestaAtual = arestaAtual->prox;
        }
        fwrite(&numArestas, sizeof(int), 1, file);

        // Escreve as arestas
        arestaAtual = verticeAtual->proxAresta;
        while (arestaAtual != NULL) {
            fwrite(&arestaAtual->idDestino, sizeof(int), 1, file);
            fwrite(&arestaAtual->peso, sizeof(int), 1, file);
            arestaAtual = arestaAtual->prox;
        }

        verticeAtual = verticeAtual->proxVertice;
    }

    fclose(file);
    return true;
}

/// <summary>
/// Fun��o para carregar um grafo de um ficheiro bin�rio
/// </summary>
/// <param name="nomeFicheiro">Nome do ficheiro a guardar</param>
/// <returns>Grafo gerado pelo ficheiro dado</returns>
Grafo* CarregarGrafoBinario(const char* nomeFicheiro) {
    FILE* file = fopen(nomeFicheiro, "rb");
    if (file == NULL) return NULL;

    int totVertices;
    fread(&totVertices, sizeof(int), 1, file);

    Grafo* grafo = CriaGrafo(totVertices);
    if (grafo == NULL) {
        fclose(file);
        return NULL;
    }
    for (int i = 0; i < totVertices; i++) {
        Vertice* vertice = CriarVertice(i);
		int resultadoInt;
		grafo = InsereVerticeGrafo(grafo, vertice, &resultadoInt);
		if (resultadoInt == 0) {
			fclose(file);
			return NULL; // Falha na inser��o do v�rtice
		}
    }
    for (int i = 0; i < totVertices; i++) {
        int numArestas;
        fread(&numArestas, sizeof(int), 1, file);

        for (int j = 0; j < numArestas; j++) {
            int idDestino, peso;
            fread(&idDestino, sizeof(int), 1, file);
            fread(&peso, sizeof(int), 1, file);

            bool resultadoBool;
            grafo = InsereArestaGrafo(grafo, i, idDestino, peso, &resultadoBool);
            if (!resultadoBool) {
                fclose(file);
                return NULL; // Falha na inser��o da aresta
            }
        }
    }

    fclose(file);
    return grafo;
}


