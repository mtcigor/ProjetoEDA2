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
/// Função para libertar a memória para a estrutura melhores caminhos
/// </summary>
/// <param name="melhoresCaminhos">Endereço da estrutura melhoresCaminhos</param>
void LiberaMelhoresCaminhos(MelhoresCaminhos* melhoresCaminhos) {
    free(melhoresCaminhos->caminhos);
    free(melhoresCaminhos);
}

/// <summary>
/// Função para libertar a memória alocada para a estrutura de todos os caminhos
/// </summary>
/// <param name="todosCaminhos">Endereço da estrutura todosCaminhos</param>
/// <param name="numCaminhos">Número de caminhos por cada elemento de todosCaminhos</param>
void LiberaTodosCaminhos(TodosCaminhos* todosCaminhos, int numCaminhos) {
    for (int i = 0; i < numCaminhos; i++) {
        for (int j = 0; j < todosCaminhos[i].numCaminhos; j++) {
            LiberaCaminhos(todosCaminhos[i].caminhos[j]);
        }
    }
    free(todosCaminhos);
}

/// <summary>
///  Função para libertar a memória alocada para a estrutura caminhos
/// </summary>
/// <param name="caminhos">Endereço da estrutura caminhos</param>
void LiberaCaminhos(Caminho** caminhos) {
    free(caminhos);
}

/// <summary>
/// Função para libertar a memória alocada para o caminho
/// </summary>
/// <param name="caminho">Caminho a libertar</param>
void LiberaCaminho(Caminho* caminho) {
    free(caminho->vertices);
}

/// <summary>
/// Função para inicializar um caminho
/// </summary>
/// <param name="caminho">Endereço do caminho a inicializar</param>
/// <param name="maxTamanho">Tamanho máximo do caminho</param>
void InicializaCaminho(Caminho* caminho, int maxTamanho) {
    caminho->vertices = (int*)malloc(maxTamanho * sizeof(int));
    caminho->pesoTotal = 0;
    caminho->tamanho = 0;
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
    printf("\n Peso: %d\n", caminho->pesoTotal);
}
