/*****************************************************************//**
 * \file   Main.c
 * \brief  Ficheiro principal para executar o Projeto
 * 
 * \author Igor a27977@alunos.ipca.pt
 * \date   May 2024
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "Grafos.h"
#include "CarregarGrafos.h"
#include "GrafoProcura.h"

int main() {
	
	int* resultadoInt = 0;

	bool* resultadoBool = (bool*)malloc(sizeof(bool));
	if (resultadoBool == NULL) return 1;
	*resultadoBool = false;

	Grafo* grafo2 = CarregarGrafo("grafo.txt");
	MostrarGrafoLA(grafo2);

	GuardarGrafo("teste.txt", grafo2);

	GuardarGrafoBinario("teste.bin", grafo2);
	Grafo* grafoBin = CarregarGrafoBinario("teste.bin");

	/*int numCaminhos;
	Caminho** caminhos = ObterTodosCaminhos(grafo2, 2, 0, &numCaminhos);

	printf("\nCaminhos encontrados:\n");
	for (int i = 0; i < numCaminhos; i++) {
		ImprimeCaminho(caminhos[i]);
	}*/

	int numCaminhos;
	TodosCaminhos* todosCaminhos = ObterTodosCaminhosGrafo(grafoBin, &numCaminhos);

	printf("Todos os caminhos encontrados:\n");
	for (int i = 0; i < numCaminhos; i++) {
		printf("\nOrigem: %d\n", todosCaminhos[i].verticeOrigem);
		for (int j = 0; j < todosCaminhos[i].numCaminhos; j++) {
			printf("Caminho %d: ", j + 1);
			ImprimeCaminho(todosCaminhos[i].caminhos[j]);
		}
	}

	MelhoresCaminhos* melhoresCaminhos = MelhorCaminho(todosCaminhos, numCaminhos);
	printf("\nMelhores caminhos encontrados:\n");
	for (int i = 0; i < melhoresCaminhos->numMelhoresCaminhos; i++) {
		ImprimeCaminho(melhoresCaminhos->caminhos[i]);
	}

	LiberaMelhoresCaminhos(melhoresCaminhos);
	LiberaTodosCaminhos(todosCaminhos, numCaminhos);

	return 0;
}
