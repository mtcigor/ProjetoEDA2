/*****************************************************************//**
 * \file   CaminhoAuxiliar.c
 * \brief  Ficheiro com fun��es para manipula��o de caminhos
 * 
 * \author Igor a27977@alunos.ipca.pt
 * \date   May 2024
 *********************************************************************/

#include "GrafoProcura.h"
#include <stdlib.h>
#include <stdio.h>

/// <summary>
/// Fun��o para inicializar um caminho
/// </summary>
/// <param name="caminho">Endere�o do caminho a inicializar</param>
/// <param name="maxTamanho">Tamanho m�ximo do caminho</param>
void InicializaCaminho(Caminho* caminho, int maxTamanho) {
    caminho->vertices = (int*)malloc(maxTamanho * sizeof(int));
    caminho->tamanho = 0;
}

/// <summary>
/// Fun��o para libertar a mem�ria alocada para o caminho
/// </summary>
/// <param name="caminho">Caminho a libertar</param>
void LiberaCaminho(Caminho* caminho) {
    free(caminho->vertices);
}

/// <summary>
/// Fun��o para adicionar um v�rtice ao caminho
/// </summary>
/// <param name="caminho">Caminho a adicionar o v�rtice</param>
/// <param name="vertice">ID do v�rtice</param>
void AdicionaVerticeNoCaminho(Caminho* caminho, int vertice) {
    caminho->vertices[caminho->tamanho++] = vertice;
}

/// <summary>
/// Fun��o que imprime o caminho no output
/// </summary>
/// <param name="caminho">Caminho a imprimir</param>
void ImprimeCaminho(Caminho* caminho) {
    for (int i = 0; i < caminho->tamanho; i++) {
        printf("%d ", caminho->vertices[i]);
    }
    printf("\n");
}
