/*****************************************************************//**
 * \file   CaminhoAuxiliar.c
 * \brief  Ficheiro com funções para manipulação de caminhos
 * 
 * \author Igor a27977@alunos.ipca.pt
 * \date   May 2024
 *********************************************************************/

#include "GrafoProcura.h"
#include <stdlib.h>
#include <stdio.h>

/// <summary>
/// Função para inicializar um caminho
/// </summary>
/// <param name="caminho">Endereço do caminho a inicializar</param>
/// <param name="maxTamanho">Tamanho máximo do caminho</param>
void InicializaCaminho(Caminho* caminho, int maxTamanho) {
    caminho->vertices = (int*)malloc(maxTamanho * sizeof(int));
    caminho->tamanho = 0;
}

/// <summary>
/// Função para libertar a memória alocada para o caminho
/// </summary>
/// <param name="caminho">Caminho a libertar</param>
void LiberaCaminho(Caminho* caminho) {
    free(caminho->vertices);
}

/// <summary>
/// Função para adicionar um vértice ao caminho
/// </summary>
/// <param name="caminho">Caminho a adicionar o vértice</param>
/// <param name="vertice">ID do vértice</param>
void AdicionaVerticeNoCaminho(Caminho* caminho, int vertice) {
    caminho->vertices[caminho->tamanho++] = vertice;
}

/// <summary>
/// Função que imprime o caminho no output
/// </summary>
/// <param name="caminho">Caminho a imprimir</param>
void ImprimeCaminho(Caminho* caminho) {
    for (int i = 0; i < caminho->tamanho; i++) {
        printf("%d ", caminho->vertices[i]);
    }
    printf("\n");
}
