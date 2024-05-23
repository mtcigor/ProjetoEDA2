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
/// Fun��o para libertar a mem�ria para a estrutura melhores caminhos
/// </summary>
/// <param name="melhoresCaminhos">Endere�o da estrutura melhoresCaminhos</param>
void LiberaMelhoresCaminhos(MelhoresCaminhos* melhoresCaminhos) {
    free(melhoresCaminhos->caminhos);
    free(melhoresCaminhos);
}

/// <summary>
/// Fun��o para libertar a mem�ria alocada para a estrutura de todos os caminhos
/// </summary>
/// <param name="todosCaminhos">Endere�o da estrutura todosCaminhos</param>
/// <param name="numCaminhos">N�mero de caminhos por cada elemento de todosCaminhos</param>
void LiberaTodosCaminhos(TodosCaminhos* todosCaminhos, int numCaminhos) {
    for (int i = 0; i < numCaminhos; i++) {
        for (int j = 0; j < todosCaminhos[i].numCaminhos; j++) {
            LiberaCaminhos(todosCaminhos[i].caminhos[j]);
        }
    }
    free(todosCaminhos);
}

/// <summary>
///  Fun��o para libertar a mem�ria alocada para a estrutura caminhos
/// </summary>
/// <param name="caminhos">Endere�o da estrutura caminhos</param>
void LiberaCaminhos(Caminho** caminhos) {
    free(caminhos);
}

/// <summary>
/// Fun��o para libertar a mem�ria alocada para o caminho
/// </summary>
/// <param name="caminho">Caminho a libertar</param>
void LiberaCaminho(Caminho* caminho) {
    free(caminho->vertices);
}

/// <summary>
/// Fun��o para inicializar um caminho
/// </summary>
/// <param name="caminho">Endere�o do caminho a inicializar</param>
/// <param name="maxTamanho">Tamanho m�ximo do caminho</param>
void InicializaCaminho(Caminho* caminho, int maxTamanho) {
    caminho->vertices = (int*)malloc(maxTamanho * sizeof(int));
    caminho->pesoTotal = 0;
    caminho->tamanho = 0;
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
    printf("\n Peso: %d\n", caminho->pesoTotal);
}
